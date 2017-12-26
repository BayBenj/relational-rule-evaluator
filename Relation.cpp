//
//  Relation.cpp
//  Project 3
//
//  Created by Benjamin Elvon Bay on 7/7/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Relation.h"

Relation::Relation(Scheme scheme_in, set<Tuple> tuple_set_in) {
    the_scheme = scheme_in;
    tuple_set = tuple_set_in;
}
Relation::~Relation() {}


string Relation::toString() {
    stringstream ss;
    vector<string> scheme = the_scheme;
    for (Tuple it : tuple_set) {
        ss << "  " << it.toString(scheme) << "\n";
    }
    string the_string = ss.str();
    if (the_string == "  ") {
        the_string = "";
    }
    return the_string;
}

void Relation::select(int index, string value) {
    set<Tuple> fewer_tuples;
    for (Tuple it : tuple_set) {
        if (it[index] == value) {
            fewer_tuples.insert(it);
        }
    }
    tuple_set = fewer_tuples;
}

void Relation::special_select(int I1, int I2) {
    set<Tuple> fewer_tuples;
    for (Tuple it : tuple_set) {
        if (it[I1] == it[I2]) {
            fewer_tuples.insert(it);
        }
    }
    tuple_set = fewer_tuples;
}

bool Relation::contain(int in, vector<int>& vector) {
    for (unsigned int i = 0; i < vector.size(); i++) {
        if (vector[i] == in) {
            return true;
        }
    }
    return false;
}

void Relation::project(vector<int> columns_to_kill) {
    if (columns_to_kill.size() > 0) {
        Scheme new_scheme;
        for (unsigned int i = 0; i< the_scheme.size(); i++) {
            if (!contain(i, columns_to_kill)) {
                new_scheme.push_back(the_scheme[i]);
            }
        }
        the_scheme = new_scheme;
        set<Tuple> tuples_minus_some;
        for (Tuple it : tuple_set) {
            Tuple new_tuple;
            for (unsigned int i = 0; i< it.size(); i++) {
                if (!contain(i, columns_to_kill)) {
                    new_tuple.push_back(it[i]);
                }
            }
            tuples_minus_some.insert(new_tuple);
        }
        tuple_set = tuples_minus_some;
    }
}

int Relation::findCorrectPosition(string scheme_element, Rule& rule) {
    vector<string> Attributes = rule.getAttributes();
    for (unsigned int i = 0; i < Attributes.size(); i++) {
        if (Attributes[i] == scheme_element) {
            return i;
        }
    }
    return -1;
}

void Relation::rearrange(Tuple& tup, Rule& rule, set<Tuple>& rearranged_tuples) {
    Tuple new_tuple = tup;
    for (unsigned int i = 0; i < tup.size(); i++) {
        int pos = findCorrectPosition(the_scheme[i], rule);
        new_tuple[pos] = tup[i];
    }
    rearranged_tuples.insert(new_tuple);
}

void Relation::project2(vector<int>& columns_to_kill, Rule& rule) {
    set<Tuple> rearranged_tuples;
    Scheme sliced_scheme;
    for (unsigned int i = 0; i< the_scheme.size(); i++) {
        if (!contain(i, columns_to_kill)) {
            sliced_scheme.push_back(the_scheme[i]);
        }
    }
    the_scheme = sliced_scheme;
    set<Tuple> tuples_minus_some;
    for (Tuple it : tuple_set) {
        Tuple new_tuple;
        Tuple new_sorted_tuple;
        for (unsigned int i = 0; i< it.size(); i++) {
            if (!contain(i, columns_to_kill)) {
                new_tuple.push_back(it[i]);
            }
        }
        tuples_minus_some.insert(new_tuple);
    }
    tuple_set = tuples_minus_some;
    Scheme sorted_scheme;
    vector<string> Attributes = rule.getAttributes();
    for (unsigned int i = 0; i < Attributes.size(); i++) {
        sorted_scheme.push_back(Attributes[i]);
    }
    for (Tuple tup : tuple_set) {
        rearrange(tup, rule, rearranged_tuples);
    }
    the_scheme = sorted_scheme;
    tuple_set = rearranged_tuples;
}

string Relation::rename(vector<string> strings) {
    string to_return = "";
    for (Tuple it : tuple_set) {
        to_return += "  ";
        to_return += it.toString(strings);
        if (to_return != "  ") {
            to_return += "\n";
        }
        else if (to_return == "  ") {
            to_return = "";
        }
    }
    return to_return;
}

vector<Tuple> Relation::getTuples() {
    vector<Tuple> tuple_vector;
    for (Tuple it : tuple_set) {
        tuple_vector.push_back(it);
    }
    return tuple_vector;
}

Scheme Relation::getScheme() {
    return the_scheme;
}

bool Relation::contains(string the_string, vector<string>& strings) {
    for (unsigned int i = 0; i < strings.size(); i++) {
        if (strings[i] == the_string) {
            return true;
        }
    }
    return false;
}

bool Relation::joinable(Tuple& tup1, Tuple& tup2, Scheme scheme1, Scheme scheme2) {
    for (unsigned int i = 0; i < scheme1.size(); i++) {
        for (unsigned int j = 0; j < scheme2.size(); j++) {
            if (scheme1[i] == scheme2[j]) {
                if (tup1[i] != tup2[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Relation::pseudo(Relation& rel1, Relation& rel2, int i, set<Tuple>& new_tuple_set, Scheme& scheme1, Scheme& scheme2) {
    vector<Tuple> rel2tups = rel2.getTuples();
    vector<Tuple> rel1tups = rel1.getTuples();
    for (unsigned int j = 0; j < rel2tups.size(); j++) {
        if (joinable(rel1tups[i], rel2tups[j], rel1.getScheme(), rel2.getScheme())) {
            Tuple new_tuple = rel2tups[j];
            for (unsigned int k = 0; k < rel1tups[i].size(); k++) {
                if (!contains(scheme1[k], scheme2)) {
                    new_tuple.push_back(rel1tups[i][k]);
                }
            }
            new_tuple_set.insert(new_tuple);
        }
    }
}

void Relation::mainJoin(Relation& rel1, Relation& rel2) {
    Scheme new_scheme;
    Scheme scheme1 = rel1.getScheme();
    Scheme scheme2 = rel2.getScheme();
    for (unsigned int i = 0; i < scheme2.size(); i++) {
        new_scheme.push_back(scheme2[i]);
    }
    for (unsigned int i = 0; i < scheme1.size(); i++) {
        if (!contains(scheme1[i], scheme2)) {
            new_scheme.push_back(scheme1[i]);
        }
    }
    set<Tuple> new_tuple_set;
    for (unsigned int i = 0; i < rel1.getTuples().size(); i++) {
        pseudo(rel1, rel2, i, new_tuple_set, scheme1, scheme2);
    }
    Relation new_relation(new_scheme, new_tuple_set);
    the_scheme = new_scheme;
    tuple_set = new_tuple_set;
}

void Relation::join(Relation& rel1, Relation& rel2) {
    if (rel1.getTuples().size() == 0) {
        the_scheme = rel2.getScheme();
        tuple_set = rel2.getTupleSet();
    }
    else if (rel2.getTuples().size() == 0) {
        the_scheme = rel1.getScheme();
        tuple_set = rel1.getTupleSet();
    }
    else {
        mainJoin(rel1, rel2);
    }
    for (unsigned int i = 0; i < the_scheme.size(); i++) {
        if (the_scheme[i][0] == '\'') {
            select(i, the_scheme[i]);
        }
    }
}

bool Relation::containt(Tuple& the_tuple, vector<Tuple>& tuples) {
    for (unsigned int i = 0; i < tuples.size(); i++) {
        if (tuples[i] == the_tuple) {
            return true;
        }
    }
    return false;
}

/*
Relation Relation::Union(Relation rel1, Relation rel2) {
    if (rel1.getScheme() != rel2.getScheme()) {
    }
    Scheme new_scheme = rel1.getScheme();
    set<Tuple> new_tuple_set;
    for (unsigned int i = 0; i < rel1.getTuples().size(); i++) {
        new_tuple_set.insert(rel1.getTuples()[i]);
    }
    for (unsigned int i = 0; i < rel2.getTuples().size(); i++) {
        if (!containt(rel2.getTuples()[i], rel1.getTuples())) {
            new_tuple_set.insert(rel2.getTuples()[i]);
        }
    }
    Relation new_relation(new_scheme, new_tuple_set);
    return new_relation;
}
 */

set<Tuple> Relation::getTupleSet() {
    return tuple_set;
}

void Relation::changeScheme(Predicate& pred) {
    Scheme new_scheme;
    vector<string> pred_params = pred.getParameters();
    for (unsigned int i = 0; i < pred_params.size(); i++) {
        new_scheme.push_back(pred_params[i]);
    }
    the_scheme = new_scheme;
}

void Relation::rename2(Scheme scheme) {
    for (unsigned int i = 0; i < the_scheme.size(); i++) {
        the_scheme[i] = scheme[i];
    }
}





