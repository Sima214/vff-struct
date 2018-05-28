#ifndef ARRAY_UTILS_HPP
#define ARRAY_UTILS_HPP

#include <cstdlib>
#include <vector>

template<class T> size_t binarySearch(T* array, size_t size, T& key) {
  if(size == 0) {
    //Avoid unsigned underflow.
    return -1;
  }
  int start = 0;
  int end = size - 1;
  while(start <= end) {
    int middle = start + (end - start)/2;
    T* cur = array + middle;
    if(*cur == key) {
      //Hit
      key = *cur;
      return middle;
    }
    else if(key < *cur) {
      //Left
      end = middle - 1;
    }
    else if(key > *cur) {
      //Right
      start = middle + 1;
    }
  }
  return -1;
}

template<class T> size_t binarySearch(std::vector<T> &array, T& key) {
  size_t size = array.size();
  if(size == 0) {
    //Avoid unsigned underflow.
    return -1;
  }
  int start = 0;
  int end = size - 1;
  while(start <= end) {
    int middle = start + (end - start)/2;
    T &cur = array.at(middle);
    if(cur == key) {
      //Hit
      key = cur;
      return middle;
    }
    else if(key < cur) {
      //Left
      end = middle - 1;
    }
    else if(key > cur) {
      //Right
      start = middle + 1;
    }
  }
  return -1;
}

/*
 * Figure out the right hole to put it in.
 */
template<class T> size_t findInsertPoint(std::vector<T> &array, T& key) {
  size_t size = array.size();
  if(size == 0) {
    //Avoid unsigned underflow.
    return 0;
  }
  int start = 0;
  int end = size - 1;
  while(start <= end) {
    int middle = start + (end - start)/2;
    T &cur = array.at(middle);
    if(cur == key) {
      //Hit
      return -1;
    }
    else if(key < cur) {
      //Left
      end = middle - 1;
    }
    else if(key > cur) {
      //Right
      start = middle + 1;
    }
  }
  return start;
}
#endif /*ARRAY_UTILS_HPP*/