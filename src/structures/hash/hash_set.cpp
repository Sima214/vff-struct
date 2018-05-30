#include "hash_set.hpp"

#include <structures/avl/avl_implementation.hpp>
#include <structures/keyvalue.hpp>

#include <cstddef>
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

template<> size_t HashSet<int>::hash(int a) {
  return hashi(a);
}

template<> size_t HashSet< KeyValue < int, HashSet<int>* > >::hash(KeyValue < int, HashSet<int>* > a) {
  return hashi(a.key);
}

/*
 * Template definitions.
 */
template<typename T> HashSet<T>::HashSet(size_t s): length(s) {
  store = new Avl<T>[length];
}

template<typename T> HashSet<T>::~HashSet() {
  delete[] store;
  //TODO: KeyValue specialization.
}

template<typename T> bool HashSet<T>::find(T& e) {
  size_t index = this->hash(e) % length;
  Avl<T>* bucket = store + index;
  return bucket->retrieve(e, e);
}

template<typename T> bool HashSet<T>::add(T& e) {
  size_t index = this->hash(e) % length;
}

template<typename T> bool HashSet<T>::rem(T& e) {
  size_t index = this->hash(e) % length;
}

template class HashSet<int>;
template class HashSet< KeyValue < int, HashSet<int>* > >;