#ifndef HASH_LOGIC_HPP
#define HASH_LOGIC_HPP

#include <dispatch/icommandable.hpp>
#include <structures/keyvalue.hpp>

/*
 * Hash graph from hash sets
 */
class HashLogic: public dispatch::ICommandable {
  public:
    HashLogic() {};
    ~HashLogic() {};
    bool readData(std::ifstream& input);
    bool addLink(int x, int y);
    bool delLink(int x, int y);
    int getNeighbors(int node, int* &neighbors);
    int getNodes(int* &nodes);
  private:

};
#endif /*HASH_LOGIC_HPP*/