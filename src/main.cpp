#include "Ai.h"
#include <cstdio>
// #include <tensorflow/c/c_api.h>

int main(int argc, char *argv[]) {
  // printf("Hello from the other side %s\n", TF_Version());
  char text[] = {"Hello world!"};
  AI TobiasAI;
  // TobiasAI.Say(argv[1]);
  // TobiasAI.Say(argv[2]);

  int close = 0;
  TobiasAI.Say(text);
  TobiasAI.listen();

  TobiasAI.Shutdown();
  return 0;
}
