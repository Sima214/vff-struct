#ifndef VEC_LOGIC_HPP
#define VEC_LOGIC_HPP

#include <dispatch/icommandable.hpp>
#include <structures/keyvalue.hpp>

#include <vector>

class VecLogic: public dispatch::ICommandable {
  public:
    VecLogic(): tree() {};
    ~VecLogic() {};
    bool readData(std::ifstream& input);
    bool addLink(int x, int y);
    bool delLink(int x, int y);
    int getNeighbors(int node, int* &neighbors);
    int getNodes(int* &nodes);
  private:
    std::vector< KeyValue < int, std::vector<int>* > > tree;
};
#endif /*VEC_LOGIC_HPP*/