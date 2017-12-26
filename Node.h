//
//  Node.h
//  Project 5
//
//  Created by Benjamin Elvon Bay on 7/31/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <set>
#include <stack>
using namespace std;

class Node {
protected:
    int name;
    bool visited_marker;
    int postorder_num;
    set<int> adjacent_nodes;
public:
    Node(int num_in);
    Node(){}//default constructor
    ~Node();
    
    int getName();
    bool getMarker();
    int getPostorder();
    vector<int> getAdjacents();
    vector<string> getAdjacentsR();
    set<int> getAdjacentsSet();
    vector<int> getAdjacentsSettoStacktoVector();
    vector<int> getAdjacentsSCCorder();
    void addAdjacent(int);
    void assignPO(int);
    void visited();
    void unvisit();
};