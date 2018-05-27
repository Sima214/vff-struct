#include "veclog.hpp"

#include <structures/keyvalue.hpp>
#include <structures/array/utils.hpp>

#include <vector>

bool VecLogic::readData(std::ifstream& input)
{
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    this->addLink(a, b);
    this->addLink(b, a);
  }
  return true;
}

bool VecLogic::addLink(int x, int y)
{
  //Find node.
  KeyValue<int, std::vector<int>*> node(x, NULL);
  size_t index = binarySearch< KeyValue<int, std::vector<int>*> >(tree, node);
  if(index == -1) {
    //Allocate new node.
    std::vector<int>* subnode = new std::vector<int>;
    node.value = subnode;
  }
  else {
    //Retrieve node.
    node = tree[index];
  }
}

bool VecLogic::delLink(int x, int y)
{

}

int VecLogic::getNeighbors(int node, int* &neighbors)
{

}

int VecLogic::getNodes(int* &nodes)
{

}