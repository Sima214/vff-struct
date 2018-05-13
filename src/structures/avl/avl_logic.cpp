#include "avl_logic.hpp"
#include "avl_implementation.hpp"

#include <iostream>

bool AvlLogic::readData(std::ifstream& input) {
  Avl<int> test;
  while(!input.eof()) {
    int a, b;
    input >> a >> b;
    test.insert(a);
    bool valid = test.validate();
    if(!valid) {
      std::cout<<"Something is wrong after adding: "<<a<<std::endl;
    }
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