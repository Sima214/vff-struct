#include "avl_logic.hpp"
#include "avl_implementation.hpp"

#include <iostream>

bool AvlLogic::readData(std::ifstream& input) {
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    tree.insert(a);
    //TODO: links
    tree.insert(b);
    //TODO: links
  }
  return true;
}

bool AvlLogic::dumpData(std::ofstream& output) {
  return true;
}

bool AvlLogic::addLink(int x, int y) {
  return true;
}

bool AvlLogic::delLink(int x, int y) {
  return true;
}

int AvlLogic::getNeighbors(int node, bool directions, int* neighbors[]) {
  return 0;
}