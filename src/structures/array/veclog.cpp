#include "veclog.hpp"

#include <structures/keyvalue.hpp>
#include <structures/array/utils.hpp>

#include <algorithm>
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
    std::vector<int>* subnode = new std::vector<int>(1, y);
    node.value = subnode;
    //Insert node.
    size_t ii = findInsertPoint< KeyValue<int, std::vector<int>*> >(tree, node);
    tree.insert(tree.begin()+ii, node);
  }
  else {
    //Retrieve node.
    node = tree[index];
    std::vector<int>* subnode = node.value;
    //Add the new connection.
    size_t ii = findInsertPoint<int>(*subnode, y);
    if(ii != -1) {
      subnode->insert(subnode->begin()+ii, y);
    }
  }
  return true;
}

bool VecLogic::delLink(int x, int y)
{
  //Find node.
  KeyValue<int, std::vector<int>*> node(x, NULL);
  size_t index = binarySearch< KeyValue<int, std::vector<int>*> >(tree, node);
  if(index != -1) {
    //Retrieve node.
    node = tree[index];
    std::vector<int>* subnode = node.value;
    size_t subindex = binarySearch<int>(*subnode, y);
    if(subindex != -1) {
      subnode->erase(subnode->begin() + subindex);
      if(subnode->size() == 0) {
        delete subnode;
        tree.erase(tree.begin() + index);
      }
    }
  }
  return true;
}

int VecLogic::getNeighbors(int n, int* &neighbors)
{
  //Find node.
  KeyValue<int, std::vector<int>*> node(n, NULL);
  size_t index = binarySearch< KeyValue<int, std::vector<int>*> >(tree, node);
  if(index != -1){
    //Retrieve node.
    node = tree[index];
    std::vector<int>* subnode = node.value;
    size_t ret = subnode->size();
    if(ret == 0) {
      return 0;
    }
    else {
      neighbors = new int[ret];
      std::copy(subnode->begin(), subnode->end(), neighbors);
      return ret;
    }
  }
  return 0;
}

int VecLogic::getNodes(int* &nodes)
{
  size_t ret = tree.size();
  if(ret != 0) {
    nodes = new int[ret];
    for(size_t i=0; i<ret; i++) {
      nodes[i] = tree[i].key;
    }
    return ret;
  }
  return 0;
}