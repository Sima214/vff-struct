#ifndef AVLIMP_STRUCT_HPP
#define AVLIMP_STRUCT_HPP

#include <dispatch/icommandable.hpp>

template <class T> struct __AVLNode {
  __AVLNode<T>* parent;
  __AVLNode<T>* left;
  __AVLNode<T>* right;
  T value;
  char meta;
};

/*
 * Generic AVL class
 */
template<class T> class Avl {
  public:
    /*
     * No-op constructor.
     */
    Avl() {
      root = NULL;
    };
    bool find(T);
    bool insert(T);
    bool del(T);
  private:
    __AVLNode<T>* root;
    __AVLNode<T>* __find(T key, __AVLNode<T>** parent);
    void __balance(__AVLNode<T>* child, bool lefty);
};
#endif /*AVLIMP_STRUCT_HPP*/