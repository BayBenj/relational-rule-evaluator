//
//  main.cpp
//  Project 3
//
//  Created by Benjamin Elvon Bay on 7/7/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Scanner.h"
#include "Token.h"
#include "Datalog.h"
#include "Database.h"
using namespace std;

set<string> findStrings(vector<Token> token_vector) {
    set<string> string_set;
    int count = 0;
    for (unsigned int i = 0; i < token_vector.size(); i++) {
        if (token_vector[i].getType() == "STRING") {
            string_set.insert(token_vector[i].getValue());
            count++;
        }
    }
    return string_set;
}

void allEval(string out_file, Database& the_database) {
    stringstream ss;
    ss << "Scheme Evaluation\n\n";
    ss << "Fact Evaluation\n\n";
    ss << the_database.factEval();
    ss << "Rule Evaluation\n\n";
    ss << the_database.ruleEvalP5();
    ss << "Query Evaluation\n";
    ss << the_database.queryEval();
    string the_string = ss.str();
    ofstream out(out_file);
    if (out.is_open()) {
        out << the_string;
        out.close();
    }
}

int main(int argc, const char * argv[]) {
    // - - - - - - - - - - - - - - - - - - - - - Project 1: Datalog Scanner - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Scanner the_scanner(argv[1]);
    vector<Token> token_vector = the_scanner.scanToken();
    the_scanner.outProcedure("P1_Output.txt");
    ///- - - - - - - - - - - - - - - - - - - - - Project 2: Datalog Parser - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    set<string> string_set = findStrings(token_vector);
    Datalog the_datalog(token_vector, string_set);
    bool failure = false;
    try {
        the_datalog.Parse();
    }
    catch(Token exception) {
        failure = true;
        the_datalog.outFailProcedure("P2_Output.txt", failure, exception);
        return 0;
    }
    the_datalog.outProcedure("P2_Output.txt");
    ///- - - - - - - - - - - - - - - - - - - - - - Projects 3 & 4: Relational Database & Datalog Interpreter - - - - - - - - - - - - - - - - - - - - - - -
    Database the_database(the_datalog);
    allEval(argv[2], the_database);
    // - - - - - - - - - - - - - - - - - - - - - - Project 5: Optimizing Rule Evaluation - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the_database.ruleEvalP5(argv[2]);
    return 0;
}






