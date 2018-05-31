#include "hash_logic.hpp"

bool HashLogic::readData(std::ifstream& input) {
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    this->addLink(a, b);
    this->addLink(b, a);
  }
  return true;
}

bool HashLogic::addLink(int x, int y) {
  KeyValue<int, HashSet<int>*> node(x, NULL);
  bool node_present = set.find(node);
  if(!node_present) {
    node.value = new HashSet<int>(8);
    set.add(node);
  }
  HashSet<int>* subnode = node.value;
  subnode->add(y);
  return true;
}

bool HashLogic::delLink(int x, int y) {
  KeyValue<int, HashSet<int>*> node(x, NULL);
  if(set.find(node)) {
    node.value->rem(y);
    if(node.value->getLength() == 0) {
      delete node.value;
      set.rem(node);
    }
  }
  return true;
}

int HashLogic::getNeighbors(int n, int* &neighbors) {
  KeyValue<int, HashSet<int>*> node(n, NULL);
  if(set.find(node)) {
    if(node.value->sort(neighbors)) {
      return node.value->getLength();
    }
    else {
      abort();
    }
  }
  else {
    return 0;
  }
}

int HashLogic::getNodes(int* &nodes) {
  KeyValue<int, HashSet<int>*>* dump = NULL;
  if(set.sort(dump)) {
    size_t l = set.getLength();
    nodes = new int[l];
    for(size_t i=0; i<l; i++){
      nodes[i] = dump[i].key;
    }
    delete[] dump;
    return l;
  }
  else {
    abort();
  }
}