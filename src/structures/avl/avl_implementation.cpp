#include "avl_implementation.hpp"

#include <iostream>
#include <cstdlib>

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

template<class T> void Avl<T>::__rotateLL(__AVLNode<T>* a) {
  __AVLNode<T>* parent = a->parent;
  __AVLNode<T>* b = a->left;
  __AVLNode<T>* br = b->right;
  //Update upper part of the tree.
  if(parent != NULL) {
    if(parent->left == a) {
      parent->left = b;
    }
    else if(parent->right == a) {
      parent->right = b;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  //Make b the new root.
  b->parent = parent;
  a->parent = b;
  b->right = a;
  //Finalize rotation.
  if(br != NULL) {
    br->parent = a;
  }
  a->left = br;
  //Update weights.
  a->meta = 0;
  b->meta = 0;
}

template<class T> void Avl<T>::__rotateRR(__AVLNode<T>* a) {
  __AVLNode<T>* parent = a->parent;
  __AVLNode<T>* b = a->right;
  __AVLNode<T>* bl = b->left;
  //Update upper part of the tree.
  if(parent != NULL) {
    if(parent->left == a) {
      parent->left = b;
    }
    else if(parent->right == a) {
      parent->right = b;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  //Make b the new root.
  b->parent = parent;
  a->parent = b;
  b->left = a;
  //Finalize rotation.
  if(bl != NULL) {
    bl->parent = a;
  }
  a->right = bl;
  //Update weights.
  a->meta = 0;
  b->meta = 0;
}

template<class T> void Avl<T>::__rotateLR(__AVLNode<T>* a) {
  __AVLNode<T>* b = a->left;
  __AVLNode<T>* c = b->right;
  __AVLNode<T>* cl = c->left;
  __AVLNode<T>* cr = c->right;
  __AVLNode<T>* parent = a->parent;
  //Update upper part of the tree.
  if(parent != NULL) {
    if(parent->left == a) {
      parent->left = c;
    }
    else if(parent->right == a) {
      parent->right = c;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  //C is the new root.
  c->parent = parent;
  c->left = b;
  c->right = a;
  b->parent = c;
  a->parent = c;
  //Complete rotations.
  b->right = cl;
  if(cl != NULL) {
    cl->parent = b;
  }
  a->left = cr;
  if(cr != NULL) {
    cr->parent = a;
  }
  //Update weights.
  if(c->meta == 0) {
    a->meta = 0;
    b->meta = 0;
  }
  else if(c->meta == 1) {
    a->meta = 0;
    b->meta = -1;
  }
  else if(c->meta == -1) {
    a->meta = +1;
    b->meta = 0;
  }
  c->meta = 0;
}

template<class T> void Avl<T>::__rotateRL(__AVLNode<T>* a) {
  __AVLNode<T>* b = a->right;
  __AVLNode<T>* c = b->left;
  __AVLNode<T>* cl = c->left;
  __AVLNode<T>* cr = c->right;
  __AVLNode<T>* parent = a->parent;
  //Update upper part of the tree.
  if(parent != NULL) {
    if(parent->left == a) {
      parent->left = c;
    }
    else if(parent->right == a) {
      parent->right = c;
    }
    else {
      //Corrupted tree.
      abort();
    }
  }
  //C is the new root.
  c->parent = parent;
  c->left = a;
  c->right = b;
  b->parent = c;
  a->parent = c;
  //Complete rotations.
  a->right = cl;
  if(cl != NULL) {
    cl->parent = a;
  }
  b->left = cr;
  if(cr != NULL) {
    cr->parent = b;
  }
  //Update weights.
  if(c->meta == 0) {
    a->meta = 0;
    b->meta = 0;
  }
  else if(c->meta == 1) {
    a->meta = -1;
    b->meta = 0;
  }
  else if(c->meta == -1) {
    a->meta = 0;
    b->meta = +1;
  }
  c->meta = 0;
}

template<class T> void Avl<T>::__balance(__AVLNode<T>* start) {
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
      //Rebalancing.
      if(node_lefty && (grandChildSide==0 || grandChildSide==1)) {
        this->__rotateLL(node);
      }
      else if(!node_lefty && (grandChildSide==0 || grandChildSide==2)) {
        this->__rotateRR(node);
      }
      else if(node_lefty && grandChildSide==2) {
        this->__rotateLR(node);
      }
      else if(!node_lefty && grandChildSide==1) {
        this->__rotateRL(node);
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
    this->__balance(node);
  }
  else if(key > end->value) {
    end->right = node;
    this->__balance(node);
  }
  return true;
}

template class Avl<int>;