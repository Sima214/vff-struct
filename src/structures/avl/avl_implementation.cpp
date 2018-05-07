#include "avl_implementation.hpp"

template<class T> bool Avl<T>::find(T key) {
  __AVLNode<T>* p;
  __AVLNode<T>* found = this->__find(key, &p);
  return found != NULL;
}

template<class T> __AVLNode<T>* Avl<T>::__find(T k, __AVLNode<T>** p) {
  __AVLNode<T>* c = this->root;
  while(c != NULL) {
    if(c->value == k) {
      return c;
    }
    else if(c->value < k) {
      *p = c;
      c = c->left;
    }
    else if(c->value > k) {
      *p = c;
      c = c->right;
    }
  }
  return c;
}

template class Avl<int>;