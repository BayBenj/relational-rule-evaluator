//
//  Tuple.cpp
//  Project 3
//
//  Created by Benjamin Elvon Bay on 7/7/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Tuple.h"

Tuple::Tuple() {}
Tuple::~Tuple() {}


string Tuple::toString(vector<string> schemes) {
    stringstream ss;
    int smaller = 0;
    if (schemes.size() < size()) {
        smaller = schemes.size();
    }
    else {
        smaller = size();
    }
    for (int i = 0; i < smaller; i++) {          //Schemes is smaller than tuple!
        ss << schemes[i] << "=" << at(i);                   //Doing i < size() caused a seg fault
        if (i != size() - 1) {
            ss << " ";
        }
    }
    string the_string = ss.str();
    return the_string;
}