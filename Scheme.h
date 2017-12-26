//
//  Scheme.h
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
using namespace std;

class Scheme : public vector<string> {
public:
    Scheme();
    ~Scheme();
    
    string toString();
    string factEval();
    void deleter(int position);
};