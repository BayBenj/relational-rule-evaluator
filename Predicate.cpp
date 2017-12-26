//
//  Predicate.cpp
//  Project 2
//
//  Created by Benjamin Elvon Bay on 7/2/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Predicate.h"

Predicate::Predicate(Token the_id_in, vector<Parameter> parameter_vector_in) {
    parameter_vector = parameter_vector_in;
    the_id = the_id_in;
}
Predicate::Predicate() {}
Predicate::~Predicate() {}

string Predicate::toString() {
    stringstream ss;
    ss << the_id.getValue() << "(" << parameter_vector[0].getValue();
    for (int i = 1; i < parameter_vector.size(); i++) {
        ss << "," << parameter_vector[i].getValue();
    }
    ss << ")";
    return ss.str();
}

string Predicate::getID() {
    return the_id.getValue();
}

vector<string> Predicate::getParameters() {
    vector<string> new_vector;
    for (int i = 0; i < parameter_vector.size(); i++) {
        new_vector.push_back(parameter_vector[i].getValue());
    }
    return new_vector;
}

vector<Parameter> Predicate::getActualParameters() {
    vector<Parameter> new_vector;
    for (int i = 0; i < parameter_vector.size(); i++) {
        new_vector.push_back(parameter_vector[i]);
    }
    return new_vector;
}

Scheme Predicate::getParametersForScheme() {
    Scheme new_scheme;
    for (int i = 0; i < parameter_vector.size(); i++) {
        new_scheme.push_back(parameter_vector[i].getValue());
    }
    return new_scheme;
}