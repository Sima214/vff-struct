#ifndef KEY_VALUE_HPP
#define KEY_VALUE_HPP

#include <cstdlib>

template<typename T, typename V> class KeyValue {
  public:
    T key;
    V value;
    KeyValue() {}//To make the compiler happy.
    KeyValue(T k, V v): key(k), value(v) {};
    ~KeyValue() {/*TODO: specialization for deleting pointers?*/};
    bool operator==(const KeyValue<T, V>& a) {
      return this->key == a.key;
    }
    bool operator!=(const KeyValue<T, V>& a) {
      return this->key != a.key;
    }
    bool operator<(const KeyValue<T, V>& a) {
      return this->key < a.key;
    }
    bool operator>(const KeyValue<T, V>& a) {
      return this->key > a.key;
    }
    bool operator<=(const KeyValue<T, V>& a) {
      return this->key <= a.key;
    }
    bool operator>=(const KeyValue<T, V>& a) {
      return this->key >= a.key;
    }
};
#endif /*KEY_VALUE_HPP*/