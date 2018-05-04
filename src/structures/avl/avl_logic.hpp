#ifndef AVLLOG_STRUCT_HPP
#define AVLLOG_STRUCT_HPP

#include <dispatch/icommandable.hpp>

/*
 * Combines two AVL structures to provide
 * appropriate interface for storing links.
 */
class AvlLogic: public dispatch::ICommandable {
  public:
    ~AvlLogic() {};
    bool readData(std::ifstream& input);
    bool dumpData(std::ofstream& output);
    bool addLink(int x, int y);
    bool delLink(int x, int y);
    int getNeighbors(int node, bool directions, int* neighbors[]);
};
#endif /*AVLLOG_STRUCT_HPP*/