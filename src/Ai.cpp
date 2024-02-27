#include "Ai.h"
#include "pocketsphinx.h"
#include "pocketsphinx/endpointer.h"
#include <cstdio>
#include <cstring>
#include <malloc.h>

AI::AI() : global_done(0) { Initialize(); }

AI::~AI() {}

void AI::Initialize() {
  espeak_Initialize(output, buflength, path, options);
  memset(&voice, 0, sizeof(espeak_VOICE)); // Zero out the voice first
  voice.languages = langNativeString;
  voice.name = "US";
  voice.variant = 1;
  voice.gender = 1;
  espeak_SetVoiceByProperties(&voice);

  //
  config = ps_config_init(NULL);
  ps_default_search_args(config);
  if ((decoder = ps_init(config)) == NULL)
    E_FATAL("PocketSphinx decoder init failed\n");
  if ((ep = ps_endpointer_init(0, 0.0, PS_VAD_LOOSE, 0, 0)) == NULL)
    E_FATAL("PocketSphinx endpointer init failed\n");
  sox = popen_sox(ps_endpointer_sample_rate(ep));
  frame_size = ps_endpointer_frame_size(ep);
  if ((frame = (short *)malloc(frame_size * sizeof(frame[0]))) == NULL)
    E_FATAL_SYSTEM("Failed to allocate frame");
  if (signal(SIGINT, catch_sig) == SIG_ERR)
    E_FATAL_SYSTEM("Failed to set SIGINT handler");
}

void AI::Say(const char *text) {
  printf("Saying  '%s'...\n", text);
  espeak_Synth(text, buflength, position, position_type, end_position, flags,
               identifier, user_data);
  printf("Done\n");
}

void AI::listen() {
  while (!global_done) {
    const int16 *speech;
    int prev_in_speech = ps_endpointer_in_speech(ep);
    size_t len, end_samples;
    if ((len = fread(frame, sizeof(frame[0]), frame_size, sox)) != frame_size) {
      if (len > 0) {
        speech = ps_endpointer_end_stream(ep, frame, frame_size, &end_samples);
      } else
        break;
    } else {
      speech = ps_endpointer_process(ep, frame);
    }
    if (speech != NULL) {
      const char *hyp;
      if (!prev_in_speech) {
        fprintf(stderr, "Speech start at %.2f\n",
                ps_endpointer_speech_start(ep));
        ps_start_utt(decoder);
      }
      if (ps_process_raw(decoder, speech, frame_size, FALSE, FALSE) < 0)
        E_FATAL("ps_process_raw() failed\n");
      if ((hyp = ps_get_hyp(decoder, NULL)) != NULL) {
        fprintf(stderr, "PARTIAL RESULT: %s\n", hyp);
        Say(hyp);
      }
      if (!ps_endpointer_in_speech(ep)) {
        fprintf(stderr, "Speech end at %.2f\n", ps_endpointer_speech_end(ep));
        ps_end_utt(decoder);
        if ((hyp = ps_get_hyp(decoder, NULL)) != NULL)
          printf("%s\n", hyp);
      }
    }
  }
}

void AI::catch_sig(int signum) {
  (void)signum;
  // global_done = 1;
}

FILE *AI::popen_sox(int sample_rate) {
  char *soxcmd;
  int len;
  FILE *sox;
#define SOXCMD "sox -q -r %d -c 1 -b 16 -e signed-integer -d -t raw -"
  len = snprintf(NULL, 0, SOXCMD, sample_rate);
  if ((soxcmd = (char *)malloc(len + 1)) == NULL)
    E_FATAL_SYSTEM("Failed to allocate string");
  if (snprintf(soxcmd, len + 1, SOXCMD, sample_rate) != len)
    E_FATAL_SYSTEM("snprintf() failed");
  if ((sox = popen(soxcmd, "r")) == NULL)
    E_FATAL_SYSTEM("Failed to popen(%s)", soxcmd);
  free(soxcmd);

  return sox;
}

void AI::Shutdown() {
  free(frame);
  if (pclose(sox) < 0)
    E_ERROR_SYSTEM("Failed to pclose(sox)");
  ps_endpointer_free(ep);
  ps_free(decoder);
  ps_config_free(config);
}
