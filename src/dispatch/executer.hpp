#ifndef DISPATCH_EXEC_HPP
#define DISPATCH_EXEC_HPP

#include "icommandable.hpp"

#include <fstream>

namespace dispatch {
class Executer {
  public:
    /*
     * Sets up the executer.
     * Commands in file 'commands' are executed ICommandable 'o',
     * while input and output are passed appropriately.
     */
    Executer(const char* input, const char* output, const char* commands, ICommandable* o);
    ~Executer();
    /*
     * Executes commands based on the configuration.
     * Should only be run once per Executer instance.
     */
    void run(bool timing);
  private:
    std::ifstream in;
    std::ofstream out;
    std::ifstream cmd;
    ICommandable* obj;
};
}
#endif /*DISPATCH_EXEC_HPP*/