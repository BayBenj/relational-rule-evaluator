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
#include <map>
#include <stack>
#include "Node.h"
using namespace std;

class Graph {
protected:
    map<int, Node> the_graph;
    stack<Node> N_stack;
    vector<int> SCCorderNodes;
    vector<set<int>> SCCs;
    set<int> used_nodes;
public:
    Graph();
    ~Graph();
    
    vector<set<int>> getSCCs();
    vector<int>* getSCCorderNodes();
    stack<Node>* getStack();
    stack<Node> getStackCopy();
    map<int,Node>* getMap();
    map<int,Node>* getPOMap();
    void addNode(int, Node);
    int size();
    vector<Node> getNodes();
    bool contain(int);
    void addSCCorderNode(int);
    void addSCC(set<int>);
    void reset();
    set<int> getUsedNodes();
};