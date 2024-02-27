#pragma once
#include <cstddef>
#include <cstdio>
#include <espeak-ng/speak_lib.h>
#include <pocketsphinx.h>
#include <signal.h>

class AI {
public:
  AI();
  ~AI();
  void Initialize();
  void Say(const char *text);
  static void catch_sig(int signum);
  static FILE *popen_sox(int sample_rate);
  void listen();
  void Shutdown();

private:
  espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
  char *path = NULL;
  void *user_data;
  unsigned int *identifier;
  int buflength = 500, options = 0;
  unsigned int position = 0, end_position = 0, flags = espeakCHARS_AUTO;
  espeak_POSITION_TYPE position_type = POS_WORD;
  espeak_VOICE voice;
  const char *langNativeString = "en"; // Set voice by properties
  int global_done = 0;

  // pocketsphinx
  ps_decoder_t *decoder;
  ps_config_t *config;
  ps_endpointer_t *ep;
  FILE *sox;
  short *frame;
  size_t frame_size;
};
