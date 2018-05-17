#ifndef AVLLOG_STRUCT_HPP
#define AVLLOG_STRUCT_HPP

#include <structures/avl/avl_implementation.hpp>
#include <dispatch/icommandable.hpp>
#include <structures/keyvalue.hpp>

/*
 * Combines two AVL structures to provide
 * appropriate interface for storing links.
 */
class AvlLogic: public dispatch::ICommandable {
  public:
    AvlLogic(): tree() {};
    ~AvlLogic() {};
    bool readData(std::ifstream& input);
    bool addLink(int x, int y);
    bool delLink(int x, int y);
    int getNeighbors(int node, int* neighbors[]);
  private:
    //DO NOT PASS THIS AROUND(references are OK).
    Avl< KeyValue < int, Avl<int>* > > tree;
};
#endif /*AVLLOG_STRUCT_HPP*/