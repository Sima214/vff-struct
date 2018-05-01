#ifndef DISPATCH_ICMD_HPP
#define DISPATCH_ICMD_HPP

#include <fstream>

namespace dispatch {
/*
 * Interface which accepts the commands.
 */
class ICommandable {
  public:
    virtual ~ICommandable() {};
    /*
     * Construct structure by reading
     * data file from an input file.
     * Returns true on success.
     */
    virtual bool readData(std::ifstream& input) = 0;
    /*
     * Dumps structure data
     * to an output file.
     * Returns true on success.
     */
    virtual bool dumpData(std::ofstream& output) = 0;

};
}
#endif /*DISPATCH_ICMD_HPP*/