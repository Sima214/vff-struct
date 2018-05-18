#include "avl_implementation.hpp"

#include <structures/dequeue.hpp>
#include <structures/keyvalue.hpp>

#include <iostream>
#include <cstdlib>
#include <algorithm>

/*
 * Utilities.
 */
template<class T> static inline int height(__AVLNode<T>* node) {
  return node? node->height: -1;
}

template<class T> static inline int weight(__AVLNode<T>* node) {
  return height(node->right) - height(node->left);
}

template<class T> void Avl<T>::rotateRight(__AVLNode<T>* a) {
  //Let b be the left child of a.
  __AVLNode<T>* b = a->left;
  //Let c be the right child of b.
  __AVLNode<T>* c = b->right;
  //Make b the new root.
  __AVLNode<T>* p = a->parent;
  b->parent = p;
  if(p != NULL) {
    if(p->left == a) {
      p->left = b;
    }
    else if(p->right == a) {
      p->right = b;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  else {
    //a is the actual root of the whole tree.
    this->root = b;
  }
  a->parent = b;
  b->right = a;
  //Send child to the other side.
  if(c) {
    c->parent = a;
  }
  a->left = c;
  //Update heights.
  a->height = std::max(height(a->right), height(a->left)) + 1;
  b->height = std::max(height(b->right), height(b->left)) + 1;
}

template<class T> void Avl<T>::rotateLeft(__AVLNode<T>* a) {
  //Let b be the right child of a.
  __AVLNode<T>* b = a->right;
  //Let c be the left child of b.
  __AVLNode<T>* c = b->left;
  //Make b the new root.
  __AVLNode<T>* p = a->parent;
  b->parent = p;
  if(p != NULL) {
    if(p->left == a) {
      p->left = b;
    }
    else if(p->right == a) {
      p->right = b;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  else {
    //a is the actual root of the whole tree.
    this->root = b;
  }
  a->parent = b;
  b->left = a;
  //Send child to the other side.
  if(c) {
    c->parent = a;
  }
  a->right = c;
  //Update heights.
  a->height = std::max(height(a->right), height(a->left)) + 1;
  b->height = std::max(height(b->right), height(b->left)) + 1;
}

/*
 * Main avl implementation.
 */
template<class T> Avl<T>::~Avl() {
  // std::cout<<"Avl destructor called"<<std::endl;
  __AVLNode<T>* node = this->root;
  Dequeue<__AVLNode<T>*> stack;
  while(stack.getLength()!=0 || node!= NULL) {
    if(node != NULL) {
      stack.pushStart(node);
      node = node->left;
    }
    else {
      node = stack.popStart();
      __AVLNode<T>* tmp = node->right;
      delete node;
      node = tmp;
    }
  }
}

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

template<class T> bool Avl<T>::retrieve(T key, T& dest){
  __AVLNode<T>* p;
  __AVLNode<T>* found = this->__find(key, &p);
  if(found != NULL) {
    dest = found->value;
    return true;
  }
  else {
    return false;
  }
}

template<class T> void Avl<T>::__balance(__AVLNode<T>* start, bool deleted) {
  __AVLNode<T>* n = start;
  if(n == NULL) {
    return;
  }
  //The history of turns taken while walking upwards.
  //0 is left turn, 1 is right turn.
  int history = 0;
  do {
    //Update all the heights upwards!
    n->height = std::max(height(n->right), height(n->left)) + 1;
    //If a problem is detected, then rotate.
    int w = weight(n);
    if(w == -2){
      //Node is left heavy.
      if(deleted) {
        //Check the weight of the child.
        __AVLNode<T>* left = n->left;
        int w2 = weight(left);
        if(w2 <= 0) {
          //Left - Left heavy.
          rotateRight(n);
        }
        else {
          //Left - Right heavy.
          rotateLeft(n->left);
          rotateRight(n);
        }
      }
      else {
        if((history&0x3) == 0x0) {
          //LL(single)
          rotateRight(n);
        }
        else if((history&0x3) == 0x2) {
          //LR(double)
          rotateLeft(n->left);
          rotateRight(n);
        }
      }
    }
    else if(w == 2) {
      //Node is right heavy.
      if(deleted) {
        __AVLNode<T>* right = n->right;
        int w2 = weight(right);
        if(w2 >= 0) {
          //Right - Right heavy.
          rotateLeft(n);
        }
        else {
          //Right - Left heavy.
          rotateRight(n->right);
          rotateLeft(n);
        }
      }
      else {
        if((history&0x3) == 0x3) {
          //RR(single)    
          rotateLeft(n);
        }
        else if((history&0x3) == 0x1) {
          //RL(double)      
          rotateRight(n->right);
          rotateLeft(n);
        }
      }
    }
    if(n->parent) {
      history = (history<<1) | !!((n->parent->right)==n);
    }
  } while((n=n->parent) != NULL);
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
    this->length++;
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
  this->length++;
  //Fix AVL property.
  this->__balance(node, false);
  return true;
}

template<class T> bool Avl<T>::sort(T* k) {
  size_t i = 0;
  __AVLNode<T>* node = this->root;
  Dequeue<__AVLNode<T>*> stack;
  while(stack.getLength()!=0 || node!= NULL) {
    if(node != NULL) {
      stack.pushStart(node);
      node = node->left;
    }
    else {
      node = stack.popStart();
      k[i++] = node->value;
      node = node->right;
    }
  }
  return true;
}

template<class T> bool Avl<T>::del(T key) {
  //Try to find the node.
  __AVLNode<T>* end = NULL;
  __AVLNode<T>* node = this->__find(key, &end);
  //Cannot delete a node if it doesn't exist.
  if(node == NULL) {
    return false;
  }
  if(node->left && node->right) {
    //Two child case.
    __AVLNode<T>* successor = node->right;
    while(successor->left) {
      successor = successor->left;
    }
    std::cout<<"D|L|R|S: "<<node->value<<"|"<<node->left->value<<"|"<<node->right->value<<"|"<<successor->value<<std::endl;
    node->value = successor->value;
    return this->__delete(successor);
  }
  else {
    return this->__delete(node);
  }
}

template<class T> bool Avl<T>::__delete(__AVLNode<T>* node) {
  if(node->left) {
    __AVLNode<T>* left = node->left;
    node->value = left->value;
    node->left = NULL;
    delete left;
    this->__balance(node, true);
  }
  else if(node->right) {
    __AVLNode<T>* right = node->right;
    node->value = right->value;
    node->right = NULL;
    delete node->right;
    this->__balance(node, true);
  }
  else {
    //Root special node case.
    if(node->parent == NULL) {
      this->root = NULL;
      delete node;
      this->length--;
      return true;
    }
    //Leaf node case.
    if(node->parent->right == node) {
      node->parent->right = NULL;
    }
    else {
      node->parent->left = NULL;
    }
    this->__balance(node->parent, true);
    delete node;
  }
  this->length--;
  return true;
}

template class Avl<int>;
template class Avl< KeyValue < int, Avl<int>* > >;