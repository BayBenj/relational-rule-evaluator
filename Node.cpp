//
//  Node.cpp
//  Project 5
//
//  Created by Benjamin Elvon Bay on 7/31/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Node.h"

Node::Node(int num_in) {
    visited_marker = false;
    postorder_num = -1;
    name = num_in;
}
Node::~Node() {}

int Node::getName() {
    return name;
}

bool Node::getMarker() {
    return visited_marker;
}

int Node::getPostorder() {
    return postorder_num;
}

vector<int> Node::getAdjacents() {
    vector<int> vec;
    for (int i : adjacent_nodes) {
        vec.push_back(i);
    }
    return vec;
}

set<int> Node::getAdjacentsSet() {
    return adjacent_nodes;
}

void Node::addAdjacent(int adjacent) {
    adjacent_nodes.insert(adjacent);
}

void Node::assignPO(int i) {
    postorder_num = i;
}

vector<string> Node::getAdjacentsR() {
    vector<string> vec;
    for (int i : adjacent_nodes) {
        vec.push_back("R" + to_string(i));
    }
    return vec;
}

void Node::visited() {
    visited_marker = true;
}

void Node::unvisit() {
    visited_marker = false;
}

vector<int> Node::getAdjacentsSettoStacktoVector() {
    vector<int> vec;
    stack<int> s;
    for (int i : adjacent_nodes) {
        s.push(i);
    }
    while (!s.empty()) {
        vec.push_back(s.top());
        s.pop();
    }
    return vec;
}


/*
vector<int> Node::getAdjacentsSCCorder(){
    vector<int> vec;
    for (int i : adjacent_nodes) {
        vec.push_back(i);
    }
    return vec;
}
*/

