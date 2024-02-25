#include <espeak-ng/speak_lib.h>
#include <iostream>

espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
char *path = NULL;
void *user_data;
unsigned int *identifier;

int main(int argc, char *argv[]) {
  char voicename[] = {"English"}; // Set voice by its name
  char text[] = {"Hello Nesmy!"};
  int buflength = 500, options = 0;
  unsigned int position = 0, position_type = 0, end_position = 0,
               flags = espeakCHARS_AUTO;
  espeak_Initialize(output, buflength, path, options);
  espeak_SetVoiceByName(voicename);
  printf("Saying  '%s'...\n", text);
  espeak_Synth(text, buflength, position, espeak_POSITION_TYPE::POS_WORD,
               end_position, flags, identifier, user_data);
  printf("Done\n");
  return 0;
}
