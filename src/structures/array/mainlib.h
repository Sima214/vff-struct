//
// Created by Fundlak on 9.05.2018.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Node
{
public:
    unsigned int id;
    std::vector<unsigned int> connections;

};

class List
{
private:
    std::vector <Node> list;
    std::ifstream file;

public:
    explicit List(std::string filename) {file.open(filename); }
    std::vector <Node> addToVec();
    void printVec();
    void insertLink(unsigned int id,unsigned int link);
    void deleteLink(unsigned int id,unsigned int link);
    void findNeighbours(unsigned int id );
};