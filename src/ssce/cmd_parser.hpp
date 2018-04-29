#ifndef SSCE_CMDPARSER_HPP
#define SSCE_CMDPARSER_HPP
#include <cstddef>
#include <stdint.h>
namespace ssce {
/*
 * This collects all the non-option arguments.
 */
#define SSCE_DEFAULT_NAME ""

/*
 * Callback function for SSCE_TYPE_CALLBACK.
 * Must return the number of read arguments on success.
 * On failure must return a negative number.
 */
typedef int (*CmdCallback)(const char* name, int argc, char** argv);

/*
 * Types of argument types that can be read.
 */
enum OPTION_TYPES {
  SSCE_TYPE_NONE=0,
  SSCE_TYPE_STRING,
  SSCE_TYPE_INT32,
  SSCE_TYPE_INT64,
  SSCE_TYPE_FLOAT,
  SSCE_TYPE_DOUBLE,
  SSCE_TYPE_CALLBACK
};

/*
 * Command line option entries.
 * full_name(required): full name of option(without the '--').
 * short_name(optional): Short name for the option.(without the '-').
 * type: one of OPTION_TYPES.
 * data: pointer to where the data should be stored or a callback function.
 *       The type of the pointer depends on what 'type' is set to.
 * description: help string to be displayed at the help screen.
 */
struct CmdOption {
  const char* full_name;
  char short_name;
  OPTION_TYPES type;
  void* data;
  const char* description;
};

/*
 * Parses command line options based on a set of CmdOptions.
 * Parameter 'o' must be an array where last element is {NULL}.
 */
void parseCmdArgs(const CmdOption* o, int argc, char** argv);
}
#endif /*SSCE_CMDPARSER_HPP*/
