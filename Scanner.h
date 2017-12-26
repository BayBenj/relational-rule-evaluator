/*
 * Scanner.h
 *
 *  Created on: Jun 29, 2015
 *      Author: bayb2
 */
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "Token.h"
using namespace std;

class Scanner {
protected:
    vector<Token> token_vector;
    int line_num;
    ifstream in;
    string in_file;
    char cha;
public:
    Scanner(string in_file_in);
    ~Scanner();
    
    vector<Token> getTokenVector();
    vector<Token> scanToken();
    void whileLoop();
    void switchAroo();
    void deFault();
    string peeker(string string_so_far);
    void weirdCharacter();
    void outProcedure(string out_file);
};