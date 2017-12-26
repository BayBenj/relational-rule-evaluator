//
//  Rules.cpp
//  Project 2
//
//  Created by Benjamin Elvon Bay on 7/2/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Rule.h"

Rule::Rule(Predicate name_in, vector<Predicate> predicate_vector_in) {
    name = name_in;
    predicate_vector = predicate_vector_in;
}
Rule::~Rule() {}

string Rule::toString() {
    stringstream ss;
    ss << name.toString() << " :- " << predicate_vector[0].toString();
    for (int i = 1; i < predicate_vector.size(); i++) {
        ss << "," << predicate_vector[i].toString();
    }
    return ss.str();
}

vector<string> Rule::getAttributes() {
    return name.getParameters();
}

vector<Parameter> Rule::getActualAttributes() {
    return name.getActualParameters();
}

vector<Predicate> Rule::getMoreAttributes() {
    return predicate_vector;
}

string Rule::getName() {
    return name.getID();
}