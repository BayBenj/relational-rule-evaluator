//
//  Relation.h
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
#include <set>
#include <map>
#include "Tuple.h"
#include "Scheme.h"
#include "Predicate.h"
#include "Rule.h"
using namespace std;


class Relation {
protected:
    Scheme the_scheme;
    set<Tuple> tuple_set;
public:
    Relation(Scheme scheme_in, set<Tuple> tuple_set_in);
    Relation() {}
    ~Relation();
    
    void select(int index, string value);
    void special_select(int I1, int I2);
    void project(vector<int>);
    void project2(vector<int>&, Rule&);
    string rename(vector<string> strings);
    void rename2(Scheme);
    string toString();
    vector<Tuple> getTuples();
    set<Tuple> getTupleSet();
    Scheme getScheme();
    bool contain(int, vector<int>&);
    bool contains(string, vector<string>&);
    bool containt(Tuple&, vector<Tuple>&);
    bool joinable(Tuple&, Tuple&, Scheme, Scheme);
    void join(Relation&, Relation&);
    Relation Union(Relation&, Relation&);
    void changeScheme(Predicate&);
    void changeScheme2(Scheme&);
    int findCorrectPosition(string, Rule&);
    void pseudo(Relation&, Relation&, int, set<Tuple>&, Scheme&, Scheme&);
    void mainJoin(Relation&, Relation&);
    void rearrange(Tuple&, Rule&, set<Tuple>&);
};