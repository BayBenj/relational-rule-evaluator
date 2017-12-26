//
//  Predicate.h
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
#include "Parameter.h"
#include "Token.h"
#include "Scheme.h"
using namespace std;

class Predicate {
protected:
    Token the_id;
    vector<Parameter> parameter_vector;
public:
    Predicate(Token the_id_in, vector<Parameter> parameter_vector_in);
    Predicate();
    ~Predicate();
    
    string toString();
    string getID();
    vector<string> getParameters();
    vector<Parameter> getActualParameters();
    Scheme getParametersForScheme();
};