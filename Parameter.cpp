//
//  Parameter.cpp
//  Project 2
//
//  Created by Benjamin Elvon Bay on 7/2/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Parameter.h"

Parameter::Parameter(Token data_in) {
    data = data_in;
    value = data.getValue();
}
Parameter::Parameter() {}
Parameter::~Parameter() {}

string Parameter::toString() {
    stringstream ss;
    ss << value;
    return ss.str();
}

string Parameter::getValue() {
    return value;
}

Token Parameter::getToken() {
    return data;
}