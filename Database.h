//
//  Database.h
//  Project 3
//
//  Created by Benjamin Elvon Bay on 7/7/15.
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
#include <map>
#include "Relation.h"
#include "Datalog.h"
#include "Predicate.h"
#include "Tuple.h"
#include "Node.h"
#include "Graph.h"
using namespace std;

class Database {
protected:
    map<string, Relation> relation_map;
    Datalog the_datalog;
public:
    Database(Datalog&);
    ~Database();
    
    map<string, Relation> makeRelations();
    string toString();
    string factEval();
    string queryEval();
    bool contains(string, vector<string>);
    bool containf(Relation&, vector<string>&);
    string ruleEval();
    string ruleEvalP5();
    map<string, Relation> getMap();
    string eachQuery(int, vector<Predicate>&);
    string eachRel(int, vector<Predicate>&, pair<string,Relation>&);
    string eachQueryParam(int, vector<Predicate>&, pair<string,Relation>&, int, vector<Parameter>&, vector<Tuple>&, Relation&, vector<int>&, bool&, map<string,int>&);
    void eachScheme(int, vector<Predicate>&, vector<Predicate>&, map<string, Relation>&);
    void eachFact(int, int, vector<Predicate>&, vector<Predicate>&, set<Tuple>&);
    void newRelation(Scheme, set<Tuple>&);
    string eachRuleFP(int, vector<Rule>&, bool&);
    string eachRule(int, vector<Rule>&);
    string makeGraphs();
    string postOrder(Graph&);
    string SCCorder(Graph&);
    string SCCprint(Graph&);
    void SCC(Graph&);
    int POrecursion(Graph&, Node&, int&);
    set<int> SCCrecursion(Graph&, Node&, set<int>&);
    bool contain(set<int>&, int&);
    void populate(unsigned int&, vector<Rule>&, Graph&, Graph&);
    string eachSCC(set<int>&, vector<Rule>&);
    void eachSCCcomponent(vector<Rule>&, int&, bool&);
};