/*
 * Token.h
 *
 *  Created on: Jun 29, 2015
 *      Author: bayb2
 */
#pragma once
#include <string>
using namespace std;

class Token {
protected:
    string type;
    string value;
    int line_num;
public:
    Token(string type_in, string value_in, int line_num_in);
    Token();
    ~Token();
    
    string getType();
    string getValue();
    int getLineNum();
};