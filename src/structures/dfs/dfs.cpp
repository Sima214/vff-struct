#include "dfs.hpp"

#include <dispatch/icommandable.hpp>
#include <structures/dequeue.hpp>

/*static*/ void dfs(dispatch::ICommandable* graph, int start_node) {
  Dequeue<int> stack;
  stack.pushStart(start_node);
  //While stack is not empty.
  while(stack.getLength() != 0) {
    int n = stack.popStart();
  }
}

int calculateConnectivity(dispatch::ICommandable* obj) {
  return -1;
}