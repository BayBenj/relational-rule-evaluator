//
//  Rules.h
//  Project 2
//
//  Created by Benjamin Elvon Bay on 7/2/15.
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
#include "Predicate.h"
using namespace std;

class Rule {
protected:
    Predicate name;
    vector <Predicate> predicate_vector;
public:
    Rule(Predicate name_in, vector<Predicate> predicate_vector_in);
    ~Rule();
    
    string toString();
    vector<string> getAttributes();
    vector<Parameter> getActualAttributes();
    vector<Predicate> getMoreAttributes();
    string getName();
};