#ifndef AVLIMP_STRUCT_HPP
#define AVLIMP_STRUCT_HPP

#include <cstddef>
#include <iostream>

template <class T> struct __AVLNode {
  __AVLNode<T>* parent;
  __AVLNode<T>* left;
  __AVLNode<T>* right;
  T value;
  int height;
};

/*
 * Generic AVL class
 */
template<class T> class Avl {
  public:
    /*
     * No-op constructor.
     */
    Avl(): root(NULL), length(0) {};
    ~Avl();
    bool find(T);
    bool retrieve(T, T&);
    bool insert(T);
    bool del(T);
    bool sort(T*);
    size_t getLength() {return length;}
  private:
    __AVLNode<T>* root;
    size_t length;
    __AVLNode<T>* __find(T key, __AVLNode<T>** parent);
    bool __delete(__AVLNode<T>* node);
    void __balance(__AVLNode<T>* root, bool deleted);
    void rotateRight(__AVLNode<T>* a);
    void rotateLeft(__AVLNode<T>* a);
};
#endif /*AVLIMP_STRUCT_HPP*/