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
    //virtual bool dumpData(std::ofstream& output) = 0;
    /*
     * Adds the specified link.
     * If the link already exists,
     * then this does nothing.
     * Returns true if no error occurred.
     */
    virtual bool addLink(int x, int y) = 0;
    /*
     * Removes the specified link.
     * If the link does not exist,
     * then this does nothing.
     * Returns true if no error occurred.
     */
    virtual bool delLink(int x, int y) = 0;
    /*
     * Finds and returns the neighbors
     * of the specified 'node'.
     * If 'directions' is true, then
     * this function takes into account the
     * directionality of the links.
     * Returns the number of neighbors
     * or -1 on error.
     * The neighbors should be stored on
     * a dynamically allocated int array,
     * the point of which must be passed to 'neighbors'.
     */
    virtual int getNeighbors(int node, int* neighbors[]) = 0;
    /*
     * Stores all the nodes in the graph
     * in a newly allocated array.
     * Returns the number of nodes
     * or -1 on error.
     */
    virtual int getNodes(int* nodes[]) = 0;
};
}
#endif /*DISPATCH_ICMD_HPP*/