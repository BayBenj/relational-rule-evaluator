/*
 * Token.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: bayb2
 */
#include "Token.h"

Token::Token(string type_in, string value_in, int line_num_in) {
    type = type_in;
    value = value_in;
    line_num = line_num_in;
}
Token::Token() {
    type = "";
    value = "";
    line_num = -1;
}
Token::~Token() {}

string Token::getType() {
    return type;
}

string Token::getValue() {
    return value;
}

int Token::getLineNum() {
    if (type == "EOF") {
        line_num += 1;
    }
    return line_num;
}