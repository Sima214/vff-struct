#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include <structures/avl/avl_implementation.hpp>

#include <cstddef>
#include <iostream>

template<typename T> class HashSet {
  public:
    HashSet(size_t s);
    ~HashSet();
    size_t getLength() { return length; };
    bool find(T&);
    bool add(T&);
    bool rem(T&);
    void stats(std::ostream&);
  private:
    Avl<T>* store;
    size_t length;
    size_t hash(T);
};
#endif /*HASH_SET_HPP*/