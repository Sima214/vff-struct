#include "avl_logic.hpp"
#include "avl_implementation.hpp"

#include <structures/keyvalue.hpp>

#include <iostream>
#include <algorithm>

bool AvlLogic::readData(std::ifstream& input) {
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    this->addLink(a, b);
    this->addLink(b, a);
  }
  return true;
}

bool AvlLogic::addLink(int x, int y) {
  KeyValue< int, Avl<int>* > dummy(x, (Avl<int>*) NULL);
  KeyValue< int, Avl<int>* > subtree;
  if(tree.retrieve(dummy, subtree)) {
    //Node is already in there.
    subtree.value->insert(y);
  }
  else {
    //Allocate new node.
    Avl<int>* subtree_value = new Avl<int>;
    subtree_value->insert(y);
    subtree.key = x;
    subtree.value = subtree_value;
    tree.insert(subtree);
  }
  return true;
}

bool AvlLogic::delLink(int x, int y) {
  KeyValue< int, Avl<int>* > dummy(x, (Avl<int>*) NULL);
  KeyValue< int, Avl<int>* > subtree;
  if(tree.retrieve(dummy, subtree)) {
    subtree.value->del(y);
    // std::cout<<"Length: "<<subtree.value->getLength()<<std::endl;
    if(subtree.value->getLength() == 0) {
      // std::cout<<"Deleting..."<<std::endl;
      tree.del(dummy);
      delete subtree.value;
    }
  }
  return true;
}

int AvlLogic::getNeighbors(int node, int* &neighbors) {
  KeyValue< int, Avl<int>* > dummy(node, (Avl<int>*) NULL);
  KeyValue< int, Avl<int>* > subtree;
  if(tree.retrieve(dummy, subtree)) {
    //Node exists.
    size_t len = subtree.value->getLength();
    neighbors = new int[len];
    subtree.value->sort(neighbors);
    return len;
  }
  else {
    //No node.
    return 0;
  }
}

int AvlLogic::getNodes(int* &nodes){
  size_t len = tree.getLength();
  KeyValue< int, Avl<int>* >* base_array = new KeyValue< int, Avl<int>* >[len];
  nodes = new int[len];
  tree.sort(base_array);
  for(size_t i=0; i<len; i++) {
    KeyValue< int, Avl<int>* >* current = base_array + i;
    nodes[i] = current->key;
  }
  delete[] base_array;
  return len;
}