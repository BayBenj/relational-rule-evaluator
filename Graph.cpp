//
//  Graph.cpp
//  Project 5
//
//  Created by Benjamin Elvon Bay on 7/31/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Graph.h"

Graph::Graph() {}
Graph::~Graph() {}

stack<Node>* Graph::getStack() {
    return &N_stack;
}

stack<Node> Graph::getStackCopy() {
    return N_stack;
}

map<int,Node>* Graph::getMap() {
    return &the_graph;
}

void Graph::addNode(int i, Node new_node) {
    the_graph[i] = new_node;
}

int Graph::size() {
    return the_graph.size();
}

vector<Node> Graph::getNodes() {
    vector<Node> vec;
    for (pair<int,Node> node : the_graph) {
        vec.push_back(node.second);
    }
    return vec;
}

bool Graph::contain(int i) {
    for (pair<int,Node> node : the_graph) {
        if (node.first == i) {
            return true;
        }
    }
    return false;
}

vector<int>* Graph::getSCCorderNodes() {
    return &SCCorderNodes;
}

void Graph::addSCCorderNode(int i) {
    SCCorderNodes.push_back(i);
}

vector<set<int>> Graph::getSCCs() {
    return SCCs;
}

void Graph::addSCC(set<int> set) {
    SCCs.push_back(set);
    for (int i : set) {
        used_nodes.insert(i);
    }
    
}

void Graph::reset() {
    vector<Node> nodes = getNodes();
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].unvisit();
    }
}

set<int> Graph::getUsedNodes() {
    return used_nodes;
}



