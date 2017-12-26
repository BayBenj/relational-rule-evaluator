/*
 * Scanner.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: bayb2
 */
#include "Scanner.h"
using namespace std;

Scanner::Scanner(string in_file_in) {
    line_num = 1;
    in_file = in_file_in;
    cha = 'B';
}
Scanner::~Scanner() {}

vector<Token> Scanner::getTokenVector() {
    return token_vector;
}

vector <Token> Scanner::scanToken() {
    in.open(in_file.c_str());
    if (in.is_open()) {
        whileLoop();
        in.close();
    }
    return token_vector;
}

void Scanner::whileLoop() {
    while(cha != EOF){
        cha = in.get();
        while (isspace(cha)) {
            if (cha == '\n') {
                line_num += 1;
            }
            cha = in.get();
        }
        switchAroo();
    }
}

void Scanner::switchAroo() {
    switch(cha) {
        case EOF :{
            Token temp("EOF", "", line_num);
            token_vector.push_back(temp);
            break;
        }
        case '#' :{
            while (in.get() != '\n') {
                //do nothing
            }
            line_num += 1;
            break;
        }
        case '?' :{
            Token temp("Q_MARK", "?", line_num);
            token_vector.push_back(temp);
            break;
        }
        case ',' :{
            Token temp("COMMA", ",", line_num);
            token_vector.push_back(temp);
            break;
        }
        case '.' :{
            Token temp("PERIOD", ".", line_num);
            token_vector.push_back(temp);
            break;
        }
        case '(' :{
            Token temp("LEFT_PAREN", "(", line_num);
            token_vector.push_back(temp);
            break;
        }
        case ')' :{
            Token temp("RIGHT_PAREN", ")", line_num);
            token_vector.push_back(temp);
            break;
        }
        case ':' :{
            if (in.peek() == '-') {
                in.get(cha);
                Token temp("COLON_DASH", ":-", line_num);
                token_vector.push_back(temp);
            }
            else {
                Token temp("COLON", ":", line_num);
                token_vector.push_back(temp);
            }
            break;
        }
        case '\'' :{
            string string_so_far = "\'";
            cha = in.get();
            while (cha != '\'' && cha != '\n') {
                string_so_far += cha;
                cha = in.get();
            }
            if (cha == '\n') {
                Token temp("ERROR", "Error", line_num);
                token_vector.push_back(temp);
            }
            else {
                string_so_far += "\'";
                Token temp("STRING", string_so_far, line_num);
                token_vector.push_back(temp);
            }
            
            break;
        }
        default:{
            deFault();
        }
            weirdCharacter();
    }
}

void Scanner::deFault() {
    if (isalpha(cha)) {
        string string_so_far = "";
        string_so_far += cha;
        string_so_far = peeker(string_so_far);
        string word_so_far = string_so_far;
        if (word_so_far == "Schemes") {
            Token temp("SCHEMES", "Schemes", line_num);
            token_vector.push_back(temp);
        }
        else if (word_so_far == "Facts") {
            Token temp("FACTS", "Facts", line_num);
            token_vector.push_back(temp);
        }
        else if (word_so_far == "Rules") {
            Token temp("RULES", "Rules", line_num);
            token_vector.push_back(temp);
        }
        else if (word_so_far == "Queries") {
            Token temp("QUERIES", "Queries", line_num);
            token_vector.push_back(temp);
        }
        else {
            Token temp("ID", string_so_far, line_num);
            token_vector.push_back(temp);
        }
    }
    else if (isdigit(cha)) {
        Token temp("ERROR", "Error", line_num);
        token_vector.push_back(temp);
    }
}

string Scanner::peeker(string string_so_far) {
    if (isalnum(in.peek()) ) {
        cha = in.get();
        while (isalnum(cha)) {
            string_so_far += cha;
            if (isalnum(in.peek()) ) {
                cha = in.get();
            }
            else {
                return string_so_far;
            }
        }
    }
    return string_so_far;
}

void Scanner::weirdCharacter() {
    if (!isalnum(cha) && !isblank(cha)) {
        Token temp("ERROR", "Error", line_num);
        token_vector.push_back(temp);
    }
}

void Scanner::outProcedure(string out_file) {
    bool terminated = false;
    ofstream out(out_file);
    if (out.is_open()) {
        for (int i = 0; i < token_vector.size(); i++) {
            if (token_vector[i].getType() != "ERROR" && terminated == false) {
                out << "(" << token_vector[i].getType() << ",\"" << token_vector[i].getValue() << "\"," << token_vector[i].getLineNum() << ")\n";
            }
            else if (terminated == false) {
                out << "Input Error on line " << token_vector[i].getLineNum() << endl;
                terminated = true;
            }
        }
        if (terminated == false) {
            out << "Total Tokens = " << token_vector.size() << endl;
        }
        out.close();
    }
}