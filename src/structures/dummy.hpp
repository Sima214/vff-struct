#ifndef DUMMY_STRUCT_HPP
#define DUMMY_STRUCT_HPP

#include <dispatch/icommandable.hpp>

namespace structures {
//TODO: temporary-for testing only.
class Dummy: public dispatch::ICommandable{
  public:
    ~Dummy() {};
    bool readData(std::ifstream& input){return true;};
    bool dumpData(std::ofstream& output){return true;};
    bool addLink(int x, int y){return true;};
    bool delLink(int x, int y){return true;};
    int getNeighbors(int node, bool directions, int* neighbors[]){return 0;};
};
}
#endif /*DUMMY_STRUCT_HPP*/