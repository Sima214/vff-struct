#include "avl_implementation.hpp"

#include <iostream>

template<class T> __AVLNode<T>* Avl<T>::__find(T k, __AVLNode<T>** p) {
  __AVLNode<T>* c = this->root;
  while(c != NULL) {
    if(c->value == k) {
      return c;
    }
    else if(k < c->value) {
      *p = c;
      c = c->left;
    }
    else if(k > c->value) {
      *p = c;
      c = c->right;
    }
  }
  return c;
}

template<class T> void Avl<T>::__balance(__AVLNode<T>* start, bool lefty) {
  //Current code.
  __AVLNode<T>* node = start->parent;
  //The previous nodes.
  __AVLNode<T>* child = start;
  char grandChildSide = 0;
  while(node != NULL) {
    //Was the left subtree of the current node that grew?
    bool node_lefty = node->left == child;
    if(node->meta == 0) {
      node->meta = node_lefty? -1: +1;
    }
    else if((node_lefty && node->meta==+1) || (!node_lefty && node->meta==-1)) {
      node->meta = 0;
    }
    else {
      if(grandChildSide == 0) {
        std::cout << "Low depth" << std::endl;
      }
      //Rebalancing.
      if(node_lefty && (grandChildSide==0 || grandChildSide==1)) {
        std::cout << "LL" << std::endl;
      }
      else if(!node_lefty && (grandChildSide==0 || grandChildSide==2)) {
        std::cout << "RR" << std::endl;
      }
      else if(node_lefty && grandChildSide==2) {
        std::cout << "LR" << std::endl;
      }
      else if(!node_lefty && grandChildSide==1) {
        std::cout << "RL" << std::endl;
      }
      return;
    }
    //Prepare for next node.
    child = node;
    node = node->parent;
    grandChildSide = node_lefty? 1: 2;
  }
}

template<class T> bool Avl<T>::find(T key) {
  __AVLNode<T>* p;
  __AVLNode<T>* found = this->__find(key, &p);
  return found != NULL;
}

template<class T> bool Avl<T>::insert(T key) {
  //Try to find the node.
  __AVLNode<T>* end = NULL;
  __AVLNode<T>* exists = this->__find(key, &end);
  //Check if key already exists.
  if(exists != NULL) {
    return false;
  }
  //Allocate new node.
  __AVLNode<T>* node = new __AVLNode<T>;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->value = key;
  node->meta = 0x0;
  //Special case when the tree is empty.
  if(end == NULL) {
    this->root = node;
    return true;
  }
  //Create correct link on the parent.
  node->parent = end;
  if(key < end->value) {
    end->left = node;
    this->__balance(node, true);
  }
  else if(key > end->value) {
    end->right = node;
    this->__balance(node, false);
  }
  return true;
}

template class Avl<int>;