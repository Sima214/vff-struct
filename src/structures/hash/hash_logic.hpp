#ifndef HASH_LOGIC_HPP
#define HASH_LOGIC_HPP

#include <dispatch/icommandable.hpp>
#include <structures/keyvalue.hpp>
#include <structures/hash/hash_set.hpp>

/*
 * Hash graph from hash sets
 */
class HashLogic: public dispatch::ICommandable {
  public:
    HashLogic(): set(256) {};
    ~HashLogic() {};
    bool readData(std::ifstream& input);
    bool addLink(int x, int y);
    bool delLink(int x, int y);
    int getNeighbors(int node, int* &neighbors);
    int getNodes(int* &nodes);
  private:
    HashSet< KeyValue < int, HashSet<int>* > > set;
};
#endif /*HASH_LOGIC_HPP*/