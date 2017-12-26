//
//  Tuple.h
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

class Tuple : public vector<string> {
protected:
    string tuple_name;
public:
    Tuple();
    ~Tuple();
    
    string toString(vector<string> the_scheme);
};