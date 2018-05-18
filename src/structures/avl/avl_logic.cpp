#include "avl_logic.hpp"
#include "avl_implementation.hpp"

#include <structures/keyvalue.hpp>

#include <iostream>
#include <algorithm>

template<class T> static inline int height(__AVLNode<T>* node) {
  return node? node->height: -1;
}
template<class T> static inline int weight(__AVLNode<T>* node) {
  return height(node->right) - height(node->left);
}
template<typename T> static int recalcHeight(__AVLNode<T>* node) {
  if(node == NULL) return -1;
  return std::max(recalcHeight(node->right), recalcHeight(node->left)) + 1;
}
template<typename T> static bool validation(__AVLNode<T>* node) {
  if(node == NULL) {
    return true;
  }
  if(recalcHeight(node) != node->height) {
    std::cout<<"Corrupted heights!"<<std::endl;
    abort();
  }
  if(node->right && node->right->value <= node->value) {
    std::cout<<"Right node corrupted!"<<std::endl;
    abort();
  }
  if(node->left && node->left->value >= node->value) {
    std::cout<<"Left node corrupted!"<<std::endl;
    abort();
  }
  int w = weight(node);
  if(w >= 2 || w<=-2) {
    std::cout<<"Tree is not AVL!"<<std::endl;
    abort();
  }
  return validation(node->left) && validation(node->right);
}

bool AvlLogic::readData(std::ifstream& input) {
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    this->addLink(a, b);
    this->addLink(b, a);
  }
  validation(tree.root);
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
    validation(subtree.value->root);
    // std::cout<<"Length: "<<subtree.value->getLength()<<std::endl;
    if(subtree.value->getLength() == 0) {
      // std::cout<<"Deleting..."<<std::endl;
      tree.del(dummy);
      validation(tree.root);
      delete subtree.value;
    }
  }
  return true;
}

int AvlLogic::getNeighbors(int node, int* neighbors[]) {
  KeyValue< int, Avl<int>* > dummy(node, (Avl<int>*) NULL);
  KeyValue< int, Avl<int>* > subtree;
  if(tree.retrieve(dummy, subtree)) {
    //Node exists.
    size_t len = subtree.value->getLength();
    int* array = new int[len];
    *neighbors = array;
    subtree.value->sort(array);
    return len;
  }
  else {
    //No node.
    return 0;
  }
}