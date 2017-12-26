//
//  Parameter.h
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
#include "Token.h"
using namespace std;

class Parameter {
protected:
    Token data;     //string or id
    string value;
public:
    Parameter(Token data_in);
    Parameter();
    ~Parameter();
    
    string toString();
    string getValue();
    Token getToken();
};