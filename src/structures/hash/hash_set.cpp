#include "hash_set.hpp"

#include <structures/avl/avl_implementation.hpp>
#include <structures/keyvalue.hpp>
#include <structures/array/utils.hpp>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>

/*
 * Hash functions
 * https://stackoverflow.com/a/12996028/7303580
 */
static unsigned int hashi(unsigned int x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}

static size_t hash(int a) {
  return hashi(a);
}

static size_t hash(KeyValue < int, HashSet<int>* > a) {
  return hashi(a.key);
}

/*
 * Template definitions.
 */
template<typename T> static void transferStore(Avl<T>* dest, size_t dn, Avl<T>* source, size_t sn) {
  for(size_t i=0; i<sn; i++) {
    Avl<T>* current = source + i;
    size_t count = current->getLength();
    if(count != 0) {
      T* items = new T[count];
      current->sort(items);
      for(size_t j=0; j<count; j++) {
        T* c = items + j;
        size_t nh = hash(*c) % dn;
        dest[nh].insert(*c);
      }
      delete[] items;
    }
  }
  delete[] source;
}

template<typename T> HashSet<T>::HashSet(size_t s): size(s), length(0) {
  this->store = new Avl<T>[size]();
}

template<typename T> HashSet<T>::~HashSet() {
  delete[] store;
  //TODO: KeyValue specialization?
}

template<typename T> bool HashSet<T>::find(T& e) {
  size_t index = hash(e) % size;
  return store[index].retrieve(e, e);
}

template<typename T> bool HashSet<T>::add(T& e) {
  //Store resize
  if((size/2) <= length) {
    //std::cout<<"Resizing("<<size<<"->"<<(size*2)<<")"<<std::endl;
    size_t new_size = size * 2;
    Avl<T>* new_store = new Avl<T>[new_size];
    transferStore(new_store, new_size, store, size);
    store = new_store;
    size = new_size;
  }
  //Insertion
  size_t index = hash(e) % size;
  if(store[index].insert(e)) {
    this->length++;
    return true;
  }
  return false;
}

template<typename T> bool HashSet<T>::rem(T& e) {
  //Deletion.
  size_t index = hash(e) % size;
  if(store[index].del(e)) {
    length--;
    if(size > (length*2)) {
      //std::cout<<"Resizing("<<size<<"->"<<(size/2)<<")"<<std::endl;
      size_t new_size = std::max(size/2, (size_t)1);
      Avl<T>* new_store = new Avl<T>[new_size];
      transferStore(new_store, new_size, store, size);
      store = new_store;
      size = new_size;
    }
    return true;
  }
  //Nothing happened.
  return false;
}

template<typename T> bool HashSet<T>::sort(T* &a) {
  T* previous = NULL;
  size_t cs = 0;
  for(size_t i=0; i<size; i++) {
    size_t l = store[i].getLength();
    if(l != 0) {
      T* t = new T[l];
      store[i].sort(t);
      if(previous != NULL) {
        T* r = NULL;
        cs = ssmerge<T>(r, previous, cs, t, l);
        delete[] t;
        delete[] previous;
        previous = r;
      }
      else {
        previous = t;
        cs = l;
      }
    }
  }
  a = previous;
  return cs==length;
}

template class HashSet<int>;
template class HashSet< KeyValue < int, HashSet<int>* > >;