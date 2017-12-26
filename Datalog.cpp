//
//  Datalog.cpp
//  Project 2
//
//  Created by Benjamin Elvon Bay on 7/2/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Datalog.h"


Datalog::Datalog(vector<Token>& token_vector_in, set<string>& string_set_in) {
    token_vector = token_vector_in;
    string_set = string_set_in;
    if (token_vector.size() == 0) {
        cout << "Danger! Token vector is empty!\n";
    }
    current_token = token_vector[0];
    previous_token = current_token;
    count = 0;
    current_type = token_vector[0].getType();
}
Datalog::~Datalog() {}


void Datalog::Parse() {
    datalogProgram();
}

void Datalog::nextToken() {
    count++;
    previous_token = current_token;
    current_token = token_vector[count];
    current_type = token_vector[count].getType();
}

void Datalog::Match(string the_string) {
    if (current_type == the_string) {
        nextToken();
    }
    else {
        Error();
    }
}

void Datalog::Error() {
    cout << "ERROR THROWN!\n";
    throw current_token;
}

Parameter Datalog::parameter() {
    Parameter to_return1(current_token);
    if (current_type == "STRING") {
        Parameter to_return2(current_token);
        Match("STRING");
        return to_return2;
    }
    else if (current_type == "ID") {
        Parameter to_return2(current_token);
        Match("ID");
        return to_return2;
    }
    else {
        Error();
        //cout << "Something that shouldn't have happened just happened.\n";
        return to_return1;
    }
}

void Datalog::parameterList(vector<Parameter>& parameter_vector) {
    if (current_type == "COMMA") {
        Match("COMMA");
        parameter_vector.push_back(parameter());
        parameterList(parameter_vector);
    }
    //epsilon
}

Predicate Datalog::predicate(vector<Parameter>& parameter_vector) {
    Token the_token(current_token);
    Predicate to_return1(the_token, parameter_vector);
    if (current_type == "ID") {
        Match("ID");
        Match("LEFT_PAREN");
        parameter_vector.push_back(parameter());
        parameterList(parameter_vector);
        Match("RIGHT_PAREN");
        Predicate to_return2(the_token, parameter_vector);
        parameter_vector.clear();
        return to_return2;
    }
    else {
        Error();
        //cout << "Something that shouldn't have happened just happened.\n";
        return to_return1;
    }
}

vector<Predicate> Datalog::predicateList(vector<Predicate>& predicate_vector, vector<Parameter>&parameter_vector) {
    if (current_type == "COMMA") {
        Match("COMMA");
        predicate_vector.push_back(predicate(parameter_vector));
        predicateList(predicate_vector, parameter_vector);
    }
    return predicate_vector;
    //epsilon
}

void Datalog::scheme() {
    vector<Parameter> parameter_vector;
    Predicate new_predicate = predicate(parameter_vector);
    scheme_vector.push_back(new_predicate);
}

Predicate Datalog::fact() {
    vector<Parameter> parameter_vector;
    Predicate to_return = predicate(parameter_vector);
    Match("PERIOD");
    return to_return;
}

Rule Datalog::rule() {
    vector<Parameter> bogus_para_vec;
    vector<Predicate> bogus_pred_vec;
    Predicate first = predicate(bogus_para_vec);
    bogus_para_vec.clear();
    Match("COLON_DASH");
    bogus_pred_vec.push_back(predicate(bogus_para_vec));
    bogus_para_vec.clear();
    predicateList(bogus_pred_vec, bogus_para_vec);
    Match("PERIOD");
    Rule to_return(first, bogus_pred_vec);
    return to_return;
}

void Datalog::query() {
    vector<Parameter> parameter_vector;
    Predicate new_predicate = predicate(parameter_vector);
    Match("Q_MARK");
    query_vector.push_back(new_predicate);
}

void Datalog::queryList() {
    if (current_type == "ID") {
        query();
        queryList();
    }
}

void Datalog::ruleList() {
    if (current_type == "ID") {
        vector<Predicate> bogus_pred;
        vector<Parameter> bogus_para;
        rule_vector.push_back(rule());
        ruleList();
    }
}

void Datalog::factList() {
    if (current_type == "ID") {
        fact_vector.push_back(fact());
        factList();
    }
    //epsilon
}

void Datalog::schemeList() {
    if (current_type == "ID") {
        scheme();
        schemeList();
    }
    //epsilon
}

void Datalog::datalogProgram() {
    if (current_type == "SCHEMES") {
        Match("SCHEMES");
        Match("COLON");
        scheme();
        schemeList();
        Match("FACTS");
        Match("COLON");
        factList();
        Match("RULES");
        Match("COLON");
        ruleList();
        Match("QUERIES");
        Match("COLON");
        query();
        queryList();
        endOfFile();
    }
    else {
        Error();
    }
}

void Datalog::endOfFile() {
    if (count + 1 < token_vector.size()) {
        //cout << "count was " << count << ", vector size was " << token_vector.size() << endl;
        //nextToken();
        Error();
    }
}

void Datalog::outProcedure(string out_file) {
    ofstream out(out_file);
    if (out.is_open()) {
        Token nothing;
        out << toString(false, nothing);
        out.close();
    }
}

void Datalog::outFailProcedure(string out_file, bool failure, Token& exception) {
    ofstream out(out_file);
    if (out.is_open()) {
        Token nothing;
        out << toString(failure, exception);
        out.close();
    }
}

string Datalog::toString(bool failure, Token& bad_token) {
    stringstream ss;
    if (!failure) {
        ss << "Success!\n";
        ss << "Schemes(" << scheme_vector.size() << "):\n";
        for (int i = 0; i < scheme_vector.size(); i++) {
            ss << "  ";
            //cout << "Scheme: " << scheme_vector[i].toString() << endl;
            ss << scheme_vector[i].toString();
            ss << "\n";
        }
        ss << "Facts(" << fact_vector.size() << "):\n";
        for (int i = 0; i < fact_vector.size(); i++) {
            ss << "  ";
            //cout << "Fact: " << fact_vector[i].toString() << endl;
            ss << fact_vector[i].toString();
            ss << "\n";
        }
        ss << "Rules(" << rule_vector.size() << "):\n";
        for (int i = 0; i < rule_vector.size(); i++) {
            ss << "  ";
            //cout << "Rule: " << rule_vector[i].toString() << endl;
            ss << rule_vector[i].toString();
            ss << "\n";
        }
        ss << "Queries(" << query_vector.size() << "):\n";
        for (int i = 0; i < query_vector.size(); i++) {
            ss << "  ";
            //cout << "Query: " << query_vector[i].toString() << endl;
            ss << query_vector[i].toString();
            ss << "\n";
        }
        ss << "Domain(" << string_set.size() << "):";
        for (string it : string_set) {
            ss << "\n  " << it;
        }
        ss << "\n";
    }
    else {
        ss << "Failure!\n  (" << bad_token.getType() << ",\"" << bad_token.getValue() << "\"," << bad_token.getLineNum() << ")\n";
    }
    return ss.str();
}

vector<Predicate> Datalog::getSchemes() {
    return scheme_vector;
}

vector<Predicate> Datalog::getFacts() {
    return fact_vector;
}

vector<string> Datalog::getStringFacts() {
    vector<string> string_vector;
    //string_vector = fact_vector
    for (int i = 0; i < fact_vector.size(); i++) {
        string_vector.push_back(fact_vector[i].toString());
    }
    return string_vector;
}

vector<Predicate> Datalog::getQueries() {
    return query_vector;
}

vector<Rule> Datalog::getRules() {
    return rule_vector;
}

void Datalog::addFact(string the_name, vector<string>& the_tuple) {
    Token new_token("ID", the_name, -1);
    vector<Parameter> param_vec;
    for (int i = 0; i < the_tuple.size(); i++) {
        Token new_token2("STRING", the_tuple[i], -1);
        Parameter new_param = Parameter(new_token2);
        param_vec.push_back(new_param);
    }
    Predicate new_fact = Predicate(new_token, param_vec);
    fact_vector.push_back(new_fact);
}


