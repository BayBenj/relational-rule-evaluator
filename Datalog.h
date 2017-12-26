//
//  Datalog.h
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
#include <set>
#include "Predicate.h"
#include "Rule.h"
#define foreach BOOST_FOREACH
using namespace std;

class Datalog {
protected:
    vector<Predicate> scheme_vector;
    vector<Predicate> fact_vector;
    vector<Predicate> query_vector;
    vector<Rule> rule_vector;
    
    vector<Token> token_vector;
    set<string> string_set;
    Token current_token;
    Token previous_token;
    int count;
    string current_type;
public:
    Datalog(vector<Token>& token_vector_in, set<string>& string_set_in);
    Datalog() {}
    ~Datalog();
    
    void Parse();
    void nextToken();
    void Match(string the_string);
    void Error();
    Parameter parameter();
    void parameterList(vector<Parameter>& parameter_vector);
    Predicate predicate(vector<Parameter>& parameter_vector);
    vector<Predicate> predicateList(vector<Predicate>& predicate_vector, vector<Parameter>&parameter_vector);
    void scheme();
    Predicate fact();
    Rule rule();
    void query();
    void queryList();
    void ruleList();
    void factList();
    void schemeList();
    void datalogProgram();
    void outProcedure(string out_file);
    void outFailProcedure(string out_file, bool failure, Token& exception);
    string toString(bool failure, Token& bad_token);
    void endOfFile();
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<string> getStringFacts();
    vector<Predicate> getQueries();
    vector<Rule> getRules();
    void addFact(string, vector<string>&);
};


