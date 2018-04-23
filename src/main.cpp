#include <ssce/CmdParser.hpp>

#include <cstdlib>

#define UNUSED __attribute__((unused))
static bool timeCommands = false;
static int timerCallback(UNUSED const char* name, UNUSED int argc, UNUSED char** argv){
  timeCommands = true;
  return 0;
}

int main(int argc, char* argv[]) {
  int mode = 0;
  char* input = NULL;
  char* commands = NULL;
  char* output = NULL;
  //Parse arguments.
  const ssce::CmdOption OPTIONS[] = {{"time", 't', ssce::SSCE_TYPE_CALLBACK, (void*) timerCallback, "Capture and report timing information. By default this is set to false."},
            {"input", 'i', ssce::SSCE_TYPE_STRING, &input, "Change the input file. By default this is 'input.txt'."},
            {"commands", 'c', ssce::SSCE_TYPE_STRING, &commands, "Change the command file. By default this is 'commands.txt'."},
            {"output", 'o', ssce::SSCE_TYPE_STRING, &output, "Change the output file. By default this is 'output.txt'."},
            {SSCE_DEFAULT_NAME, 0, ssce::SSCE_TYPE_INT32, &mode, "[TYPE]\nTo select the data structure type enter a number.\n1 for arrays, 2 for AVL, 3 for hash tables."},
            {NULL, 0, ssce::SSCE_TYPE_NONE, NULL, NULL}};
  ssce::parseCmdArgs(OPTIONS, argc, argv);
  //Load dispatcher.
  //TODO: implementation.
  //Clean-up.
  free(input);
  free(commands);
  free(output);
  return 0;
}