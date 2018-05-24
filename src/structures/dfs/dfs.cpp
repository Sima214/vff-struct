#include "dfs.hpp"

#include <cstddef>
#include <iostream>

#include <dispatch/icommandable.hpp>
#include <structures/dequeue.hpp>
#include <structures/keyvalue.hpp>
#include <structures/array/utils.hpp>

static bool allFound(KeyValue<int, bool>* discovered, size_t size, int& start) {
  for(size_t i=0; i<size; i++) {
    KeyValue<int, bool>* current = discovered + i;
    if(!current->value) {
      start = current->key;
      return true;
    }
  }
  return false;
}

static void dfs(dispatch::ICommandable* graph, KeyValue<int, bool>* discovered, size_t size, int start_node) {
  Dequeue<int> stack;
  stack.pushStart(start_node);
  //While stack is not empty.
  while(stack.getLength() != 0) {
    int n = stack.popStart();
    KeyValue<int, bool> cache(n, false);
    size_t index = binarySearch< KeyValue<int, bool> >(discovered, size, cache);
    if(index == -1) {
      abort();
    }
    //If not discovered yet.
    if(!cache.value) {
      KeyValue<int, bool>* nd = discovered + index;
      nd->value = true;
      //Get all adjacent nodes.
      int* neighbors = NULL;
      int count = graph->getNeighbors(n, neighbors);
      for(int i=0; i<count; i++) {
        stack.pushStart(neighbors[i]);
      }
      delete[] neighbors;
    }
  }
}

int calculateConnectivity(dispatch::ICommandable* obj) {
  int* nodes = NULL;
  size_t count = obj->getNodes(nodes);
  //Generate look-up table for discovered nodes.
  KeyValue<int, bool>* discovered = new KeyValue<int, bool>[count];
  for(size_t i=0; i<count; i++) {
    KeyValue<int, bool>* current = discovered + i;
    current->key = nodes[i];
    current->value = false;
  }
  delete[] nodes;
  //Select random starting point.
  int start = std::rand() % count;
  start = discovered[start].key;
  //Run DFS until all nodes have been discovered.
  int runs = 0;
  do {
    runs++;
    dfs(obj, discovered, count, start);
  } while(allFound(discovered, count, start));
  delete[] discovered;
  return runs;
}