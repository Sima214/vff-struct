#include "avl_implementation.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>

/*
 * Utilities.
 */
template<class T> static int height(__AVLNode<T>* node) {
  return node? node->height: -1;
}

template<class T> static int weight(__AVLNode<T>* node) {
  return height(node->right) - height(node->left);
}

template<class T> static int calcNodeHeight(__AVLNode<T>* node) {
  if(node == NULL) {
    return 0;
  }
  else {
    return std::max(calcNodeHeight(node->left), calcNodeHeight(node->right)) + 1;
  }
}

/*
 * Main avl implementation.
 */
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

template<class T> bool Avl<T>::find(T key) {
  __AVLNode<T>* p;
  __AVLNode<T>* found = this->__find(key, &p);
  return found != NULL;
}

template<class T> void Avl<T>::__balanceInsert(__AVLNode<T>* start) {
  __AVLNode<T>* n = start;
  while((n=n->parent) != NULL) {
    //Update all the heights upwards!
    n->height = std::max(height(n->right), height(n->left)) + 1;
    //If a problem is detected, then rotate.
    int w = weight(n);
    if(w == -2){
      //Node is left heavy.
    }
    else if(w == 2) {
      //Node is right heavy.
    }
  }
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
  node->height = 0;
  //Special case when the tree is empty.
  if(end == NULL) {
    this->root = node;
    return true;
  }
  //Create correct link on the parent.
  node->parent = end;
  if(key < end->value) {
    end->left = node;
  }
  else if(key > end->value) {
    end->right = node;
  }
  //Fix AVL property.
  this->__balanceInsert(node);
  return true;
}

/*
 * For better debugging.
 */
template<class T> bool Avl<T>::validate() {
  return this->__validate(this->root);
}

template<class T> bool Avl<T>::__validate(__AVLNode<T>* node) {
  if(node == NULL){
    return true;
  }
  else {
    if(node->left && node->left->value>node->value) {
      std::cout<<"Invalid tree: "<<node->left->value<<"must not be at the left of"<<node->value<<std::endl;
      //Check the rest of the subtree.
      this->__validate(node->left);
      this->__validate(node->right);
      return false;
    }
    else if((node->right && node->right->value<node->value)) {
      std::cout<<"Invalid tree: "<<node->right->value<<"must not be at the right of"<<node->value<<std::endl;
      //Check the rest of the subtree.
      this->__validate(node->left);
      this->__validate(node->right);
      return false;
    }
    int lh = calcNodeHeight(node->left);
    int rh = calcNodeHeight(node->right);
    int balance = rh - lh;
    if(balance>1 || balance<-1) {
      std::cout<<"Tree is unbalanced("<<balance<<":"<<weight(node)<<")"<<std::endl;
      //Check the rest of the subtree.
      this->__validate(node->left);
      this->__validate(node->right);
      return false;
    }
    else if(balance != weight(node)) {
      std::cout<<"Expected: "<<balance<<", got: "<<weight(node)<<std::endl;
      //Check the rest of the subtree.
      this->__validate(node->left);
      this->__validate(node->right);
      return false;
    }
    else {
      return this->__validate(node->left) && this->__validate(node->right);
    }
  }
}

template class Avl<int>;