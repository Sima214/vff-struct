#include "dequeue.hpp"
/*Implementation file - must get included by the header file.*/

#include <cstring>

template<typename T> void Dequeue<T>::pushEnd(T e) {
  __DequeueNode<T>* node = new __DequeueNode<T>;
  node->next = NULL;
  node->previous = NULL;
  node->value = e;
  if(this->end == NULL) {
    this->end = node;
    if(this->start != NULL) {
      node->previous = this->start;
    }
  }
  else {
    if(this->start == NULL) {
      //Two elements in queue.
      this->start = this->end;
    }
    this->end->next = node;
    node->previous = this->next;
    this->end = node;
  }
  this->length++;
}

template<typename T> void Dequeue<T>::pushStart(T e) {
  __DequeueNode<T>* node = new __DequeueNode<T>;
  node->next = NULL;
  node->previous = NULL;
  node->value = e;
  if(this->start == NULL) {
    this->start = node;
    if(this->end != NULL) {
      node->next = this->end;
    }
  }
  else {
    if(this->end == NULL) {
      //Two elements in queue.
      this->end = this->start;
    }
    this->start->previous = node;
    node->next = this->start;
    this->start = node;
  }
  this->length++;
}

template<typename T> T Dequeue<T>::popEnd() {
  if(this->end != NULL && this->start != NULL) {
    __DequeueNode<T>* ret = this->end;
    if(ret->previous == this->start) {
      //Two elements.
      this->start->next = NULL;
      this->end = NULL;
    }
    else {
      ret->previous->next = NULL;
      this->end = ret->previous;
    }
    T copy = ret->value;
    delete ret;
    this->length--;
    return copy;
  }
  else if(this->length == 1) {
    //Only one element.
    __DequeueNode<T>* ret = this->start? this->start: this->end;
    this->start = NULL;
    this->end = NULL;
    T copy = ret->value;
    delete ret;
    this->length--;
    return copy;
  }
  else {
    T stackspace;
    memset(&stackspace, 0, sizeof(T));
    return stackspace;
  }
}

template<typename T> T Dequeue<T>::popStart() {
  if(this->start != NULL && this->end != NULL) {
    __DequeueNode<T>* ret = this->start;
    if(ret->next == this->end) {
      //Two elements
      this->end->previous = NULL;
      this->start = NULL;
    }
    else {
      ret->next->previous = NULL;
      this->start = ret->next;
    }
    T copy = ret->value;
    delete ret;
    this->length--;
    return copy;
  }
  else if(this->length == 1) {
    //Only one element.
    __DequeueNode<T>* ret = this->end? this->end: this->start;
    /*If this parts does not make sense, I will say this: bugs and no time.*/
    this->end = NULL;
    this->start = NULL;
    T copy = ret->value;
    delete ret;
    this->length--;
    return copy;
  }
  else {
    T stackspace;
    memset(&stackspace, 0, sizeof(T));
    return stackspace;
  }
}