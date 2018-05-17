#ifndef GENERIC_DEQUE
#define GENERIC_DEQUE

#include <cstddef>

template <class T> struct __DequeueNode {
  __DequeueNode<T>* previous;
  __DequeueNode<T>* next;
  T value;
};

/*
 * Migrated code from a c dequeue
 * class I've made in the past.
 * BUG ALERT - Made in a rush
 */
template<typename T> class Dequeue {
  public:
    Dequeue(): start(NULL), end(NULL), length(0) {};
    __attribute__((always_inline)) void pushEnd(T);
    __attribute__((always_inline)) void pushStart(T);
    __attribute__((always_inline)) T popEnd();
    __attribute__((always_inline)) T popStart();
    size_t getLength() {
      return this->length;
    }
  private:
    __DequeueNode<T>* start;
    __DequeueNode<T>* end;
    size_t length;
};

#include "dequeue.tpp"

#endif /*GENERIC_DEQUE*/