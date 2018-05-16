#ifndef AVLIMP_STRUCT_HPP
#define AVLIMP_STRUCT_HPP

#include <dispatch/icommandable.hpp>

#include <cstddef>

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
    Avl() {
      root = NULL;
    };
    ~Avl();
    bool find(T);
    bool insert(T);
    bool del(T);
    bool sort(T[]);
    size_t getLength() {return length;}
    #ifndef NDEBUG
    /*
     * Validate avl property.
     */
    bool validate();
    #endif
  private:
    __AVLNode<T>* root;
    size_t length;
    __AVLNode<T>* __find(T key, __AVLNode<T>** parent);
    void __balanceInsert(__AVLNode<T>* root);
    #ifndef NDEBUG
    bool __validate(__AVLNode<T>* node);
    #endif
    void rotateRight(__AVLNode<T>* a);
    void rotateLeft(__AVLNode<T>* a);
};
#endif /*AVLIMP_STRUCT_HPP*/