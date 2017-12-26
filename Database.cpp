//
//  Database.cpp
//  Project 5
//
//  Created by Benjamin Elvon Bay on 7/7/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//
// LOW COMPLEXITY
#include "Database.h"


void Database::eachFact(int j, int i, vector<Predicate>& schemes, vector<Predicate>& facts, set<Tuple>& set_of_tuples) {
    if (facts[j].getID() == schemes[i].getID()) {
        Tuple new_tuple;
        for (unsigned int k = 0; k < facts[j].getParameters().size(); k++) {
            new_tuple.push_back(facts[j].getParameters()[k]);
        }
        set_of_tuples.insert(new_tuple);
    }
}

void Database::eachScheme(int i, vector<Predicate>& schemes, vector<Predicate>& facts, map<string, Relation>& relations) {
    set<Tuple> set_of_tuples;
    for (unsigned int j = 0; j < facts.size(); j++) {
        eachFact(j, i, schemes, facts, set_of_tuples);
    }
    Scheme new_scheme = schemes[i].getParametersForScheme();
    Relation new_relation(new_scheme, set_of_tuples);
    relations[schemes[i].getID()] = new_relation;
}

map<string, Relation> Database::makeRelations() {
    map<string, Relation> relations;
    vector<Predicate> schemes = the_datalog.getSchemes();
    vector<Predicate> facts = the_datalog.getFacts();
    for (unsigned int i = 0; i < schemes.size(); i++) {
        eachScheme(i, schemes, facts, relations);
    }
    return relations;
}

Database::Database(Datalog& the_datalog_in) {
    the_datalog = the_datalog_in;
    relation_map = makeRelations();
}
Database::~Database() {}

map<string, Relation> Database::getMap() {
    return relation_map;
}

string Database::factEval() {
    stringstream ss;
    for (map<string,Relation>::iterator it = relation_map.begin(); it != relation_map.end(); ++it) {
        ss << it -> first << "\n";
        ss << it -> second.toString() << endl;
    }
    string the_string = ss.str();
    return the_string;
}

string Database::eachQueryParam(int i, vector<Predicate>& queries, pair<string,Relation>& rel, int j, vector<Parameter>& query_parameters, vector<Tuple>& tuples, Relation& select_relation, vector<int>& columns_to_kill_for_project, bool& strings_only, map<string,int>& ID_index_map) {
    stringstream ss;
        if (query_parameters[j].getToken().getType() == "STRING") {
            select_relation.select(j, query_parameters[j].getToken().getValue());
            columns_to_kill_for_project.push_back(j);
        }
        else if (query_parameters[j].getToken().getType() == "ID") {
            strings_only = false;
            bool unique_ID = true;
            for (pair<string,int> ID : ID_index_map) {
                if (ID.first == query_parameters[j].getToken().getValue()) {
                    unique_ID = false;
                    break;
                }
            }
            columns_to_kill_for_project.push_back(j);
            if (unique_ID) {
                pair<string,int> new_ID(query_parameters[j].getToken().getValue(),j);
                ID_index_map.insert(new_ID);
                columns_to_kill_for_project.pop_back();
            }
            else {
                select_relation.special_select(j, ID_index_map[query_parameters[j].getToken().getValue()]);
            }
        }
    string the_string = ss.str();
    return the_string;
}

string Database::eachRel(int i, vector<Predicate>& queries, pair<string,Relation>& rel) {
    stringstream ss;
        vector<Parameter> query_parameters = queries[i].getActualParameters();
        if (queries[i].getID() == rel.first) {
            bool strings_only = true;
            vector<int> columns_to_kill_for_project;
            string rename_string = "";
            map<string,int> ID_index_map;
            Relation select_relation = rel.second;
            Relation project_relation;
            Relation rename_relation;
            ss << "\n" << queries[i].toString() << "?" << " ";
            vector<int> int_vector;
            vector<Tuple> tuples = rel.second.getTuples();
            for (unsigned int j = 0; j < query_parameters.size(); j++) {
                ss << eachQueryParam(i, queries, rel, j, query_parameters, tuples, select_relation, columns_to_kill_for_project, strings_only, ID_index_map);
            }
            bool match = false;
            if (select_relation.getTuples().size() > 0) {
                match = true;
            }
            if (match) {
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Project - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                project_relation = select_relation;
                project_relation.project(columns_to_kill_for_project);
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Rename - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                rename_relation = project_relation;
                vector<string> new_names;
                map<int,string> index_before_ID;
                for (pair<string,int> ID : ID_index_map) {
                    index_before_ID[ID.second] = ID.first;
                }
                for (pair<int,string> ID : index_before_ID) {
                    new_names.push_back(ID.second);
                }
                rename_string = rename_relation.rename(new_names);
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Printing - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                ss << "Yes(" << select_relation.getTuples().size() << ")\n";
                ss << "select\n" << select_relation.toString();
                if (strings_only) {
                    ss << "project\n";
                }
                else {
                    ss << "project\n" << project_relation.toString();
                }
                ss << "rename\n" << rename_string;
            }
            else {
                ss << "No\n\n";
            }
        }
    string the_string = ss.str();
    return the_string;
}

string Database::eachQuery(int i, vector<Predicate>& queries) {
    stringstream ss;
    for (pair<string,Relation> rel : relation_map) {
        ss << eachRel(i, queries, rel);
    }
    string the_string = ss.str();
    return the_string;
}

string Database::queryEval() {
    stringstream ss;
    vector<Predicate> queries = the_datalog.getQueries();
    for (unsigned int i = 0; i < queries.size(); i++) {
       ss << eachQuery(i, queries);
    }
    string the_string = ss.str();
    return the_string;
}

bool Database::contains(string the_string, vector<string> strings) {
    for (unsigned int i = 0; i < strings.size(); i++) {
        if (strings[i] == the_string) {
            return true;
        }
    }
    return false;
}

bool Database::containf(Relation& rel, vector<string>& tuple) {
    vector<Tuple> tups = rel.getTuples();
    for (unsigned int i = 0; i < tups.size(); i++) {
        if (tups[i] == tuple) {
            return true;
        }
    }
    return false;
}

string Database::eachRuleFP(int i, vector<Rule>& rules, bool& facts_added) {
    stringstream ss;
    ss << rules[i].toString() << "\n";
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Join
    Relation rel1;
    Relation rel2;
    Relation new_relation;
    vector<Predicate> more_attribs = rules[i].getMoreAttributes();
    for (unsigned int j = 0; j < more_attribs.size(); j++) {
        if (relation_map.find(more_attribs[j].getID())->second.getTuples().size() == 0) {
            Relation wipe;
            new_relation = wipe;
            break;
        }
        else {
            Relation current_rel = relation_map.find(more_attribs[j].getID())->second;
            current_rel.changeScheme(more_attribs[j]);
            rel1 = new_relation;
            rel2 = current_rel;
            new_relation.join(rel1, rel2);
        }
    }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Project
    set<int> columns_to_kill;
    Scheme newrel_scheme = new_relation.getScheme();
    for (unsigned int k = 0; k < newrel_scheme.size(); k++) {
        if (!contains(newrel_scheme[k], rules[i].getAttributes())) {
            columns_to_kill.insert(k);
        }
    }
    vector<int> columns_to_demolish;
    for (unsigned int the_int : columns_to_kill) {
        columns_to_demolish.push_back(the_int);
    }
    new_relation.project2(columns_to_demolish, rules[i]);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Rename
    Relation current_rel = relation_map.find(rules[i].getName())->second;
    Scheme original_scheme = current_rel.getScheme();
    new_relation.rename2(original_scheme);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Add Facts
    //facts_added = false;
    vector<Tuple> newrel_tups = new_relation.getTuples();
    for (unsigned int k = 0; k < newrel_tups.size(); k++) {
        if (!containf(current_rel, newrel_tups[k])) {
            the_datalog.addFact(rules[i].getName(), newrel_tups[k]);
            facts_added = true;
            ss << "  " << newrel_tups[k].toString(new_relation.getScheme()) << "\n";
        }
    }
    //if (facts_added_num > 0) {
    //    ss << rules[i].toString() << "\n";
    //}
    //facts_added_num = 0;
    relation_map = makeRelations();
    string the_string = ss.str();
    return the_string;
}

string Database::eachRule(int i, vector<Rule>& rules) {
    stringstream ss;
    ss << rules[i].toString() << "\n";
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Join
    Relation rel1;
    Relation rel2;
    Relation new_relation;
    vector<Predicate> more_attribs = rules[i].getMoreAttributes();
    for (unsigned int j = 0; j < more_attribs.size(); j++) {
        if (relation_map.find(more_attribs[j].getID())->second.getTuples().size() == 0) {
            Relation wipe;
            new_relation = wipe;
            break;
        }
        else {
            Relation current_rel = relation_map.find(more_attribs[j].getID())->second;
            current_rel.changeScheme(more_attribs[j]);
            rel1 = new_relation;
            rel2 = current_rel;
            new_relation.join(rel1, rel2);
        }
    }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Project
    set<int> columns_to_kill;
    Scheme newrel_scheme = new_relation.getScheme();
    for (unsigned int k = 0; k < newrel_scheme.size(); k++) {
        if (!contains(newrel_scheme[k], rules[i].getAttributes())) {
            columns_to_kill.insert(k);
        }
    }
    vector<int> columns_to_demolish;
    for (unsigned int the_int : columns_to_kill) {
        columns_to_demolish.push_back(the_int);
    }
    new_relation.project2(columns_to_demolish, rules[i]);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Rename
    Relation current_rel = relation_map.find(rules[i].getName())->second;
    Scheme original_scheme = current_rel.getScheme();
    new_relation.rename2(original_scheme);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Add Facts
    vector<Tuple> newrel_tups = new_relation.getTuples();
    for (unsigned int k = 0; k < newrel_tups.size(); k++) {
        if (!containf(current_rel, newrel_tups[k])) {
            the_datalog.addFact(rules[i].getName(), newrel_tups[k]);
            ss << "  " << newrel_tups[k].toString(new_relation.getScheme()) << "\n";
        }
    }
    relation_map = makeRelations();
    string the_string = ss.str();
    return the_string;
}


/*
string Database::ruleEval() {
    stringstream ss;
    vector<Predicate> facts = the_datalog.getFacts();
    vector<Rule> rules = the_datalog.getRules();
    bool facts_added = true;
    int passes = 0;
    while (facts_added) {
        passes++;
        facts_added = false;
        Relation last_relation;
        for (unsigned int i = 0; i < rules.size(); i++) {
            ss << eachRule(i, rules, facts_added);
        }
    }
    ss << "\nConverged after " << passes << " passes through the Rules.\n\n";
    ss << factEval();
    string the_string = ss.str();
    return the_string;
}
*/

string Database::ruleEvalP5() {
    stringstream ss;
    ss << makeGraphs();
    string the_string = ss.str();
    return the_string;
}

void Database::populate(unsigned int& i, vector<Rule>& rules, Graph& forward_graph, Graph& reverse_graph) {
    Rule the_rule = rules[i];
    vector<Predicate> more_attribs = the_rule.getMoreAttributes();
    for (unsigned int j = 0; j < more_attribs.size(); j++) {
        for (unsigned int k = 0; k < rules.size(); k++) {
            if (more_attribs[j].getID() == rules[k].getName()) {
                forward_graph.getMap() -> at(i).addAdjacent(k);
                reverse_graph.getMap() -> at(k).addAdjacent(i);
            }
        }
    }
}

string Database::makeGraphs() {
    stringstream ss;
    vector<Rule> rules = the_datalog.getRules();
    Graph forward_graph;
    Graph reverse_graph;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Creates All Nodes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    for (unsigned int i = 0; i < rules.size(); i++) {
        Node for_node(i);
        Node rev_node(i);
        forward_graph.addNode(i, for_node);
        reverse_graph.addNode(i, rev_node);
    }
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Adds All Adjacents - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    for (unsigned int i = 0; i < rules.size(); i++) {
        populate(i, rules, forward_graph, reverse_graph);
    }
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Output - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ss << "Dependency Graph\n";
    for (int i = 0; i < forward_graph.size(); i++) {
        ss << "  R" << i << ":";
        vector<string> adjacents = forward_graph.getNodes()[i].getAdjacentsR();
        for (int j = 0; j < adjacents.size(); j++) {
            ss << " " << adjacents[j];
        }
        ss << "\n";
    }
    ss << "\nReverse Graph\n";
    for (int i = 0; i < reverse_graph.size(); i++) {
        ss << "  R" << i << ":";
        vector<string> adjacents = reverse_graph.getNodes()[i].getAdjacentsR();
        for (int j = 0; j < adjacents.size(); j++) {
            ss << " " << adjacents[j];
        }
        ss << "\n";
    }
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - Other Output Elements - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ss << "\n" << postOrder(reverse_graph);
    ss << "\n" << SCCorder(reverse_graph);
    vector<int>* rev_ints = reverse_graph.getSCCorderNodes();
    for (int i = 0; i < rev_ints -> size(); i++) {
        forward_graph.addSCCorderNode(rev_ints -> at(i));
    }
    SCC(forward_graph);
    ss << SCCprint(forward_graph);
    ss << "Rule Evaluation Complete\n\n" << factEval();
    string the_string = ss.str();
    return the_string;
}

string Database::postOrder(Graph& graph) {
    stringstream ss;
    ss << "Postorder Numbers\n";
    int i = 1;
    for (int j = 0; j < graph.size(); j++) {
        Node the_node = graph.getMap() -> at(j);
        if (!(the_node.getMarker())) {
            i = POrecursion(graph, the_node, i);
        }
        ss << "  R" << j << ": " << graph.getMap() -> at(j).getPostorder() << "\n";
    }
    string the_string = ss.str();
    return the_string;
}

int Database::POrecursion(Graph& graph, Node& current_node, int& PO) {
    current_node.visited();
    graph.getMap() -> at(current_node.getName()).visited();
    for (int i : current_node.getAdjacentsSet()) {
        Node the_node = graph.getMap() -> at(i);
        if (!(the_node.getMarker())) {
            POrecursion(graph, the_node, PO);
        }
    }
    graph.getMap() -> at(current_node.getName()).assignPO(PO);
    graph.getStack() -> push(current_node);
    PO++;
    return PO;
}

string Database::SCCorder(Graph& graph) {
    stringstream ss;
    ss << "SCC Search Order\n";
    stack<Node> current_stack = graph.getStackCopy();
    while (!current_stack.empty()) {
        Node current_node = current_stack.top();
        ss << "  R" << current_node.getName() << "\n";
        graph.addSCCorderNode(current_node.getName());
        current_stack.pop();
    }
    ss << "\n";
    string the_string = ss.str();
    return the_string;
}

void Database::SCC(Graph& graph) {
    graph.reset();
    map<int,Node>* the_map = graph.getMap();
    vector<int>* ints = graph.getSCCorderNodes();
    for (int i = 0; i < ints -> size(); i++) {
        int the_int = ints -> at(i);
        if (!(the_map -> at(the_int).getMarker())) {
            set<int> set;
            set = SCCrecursion(graph, the_map -> at(the_int), set);
            if (!set.empty()) {
                graph.addSCC(set);
            }
        }
    }
}

set<int> Database::SCCrecursion(Graph& graph, Node& current_node, set<int>& SCC) {
    current_node.visited();
    for (int i : current_node.getAdjacentsSet()) {
        if (!(graph.getMap() -> at(i).getMarker())) {
            SCCrecursion(graph, graph.getMap() -> at(i), SCC);
        }
    }
    set<int> the_set = graph.getUsedNodes();
    int the_name = current_node.getName();
    if (!contain(the_set, the_name)) {
        SCC.insert(current_node.getName());
    }
    return SCC;
}

void Database::eachSCCcomponent(vector<Rule>& rules, int& rule_num, bool& fixed_point) {
    for (int i = 0; i < rules[rule_num].getMoreAttributes().size(); i++) {
        if (rules[rule_num].getName() == rules[rule_num].getMoreAttributes()[i].getID()) {
            fixed_point = true;
        }
    }
}

string Database::eachSCC(set<int>& mini_set, vector<Rule>& rules) {
    stringstream ss;
    ss << "SCC:";
    bool fixed_point = false;
    if (mini_set.size() > 1) {
        fixed_point = true;
    }
    for (int rule_num : mini_set) {
        ss << " R" << rule_num;
    }
    ss << "\n";
    for (int rule_num : mini_set) {
        eachSCCcomponent(rules, rule_num, fixed_point);
    }
    bool facts_added = true;
    if (fixed_point) {
        while (facts_added) {
            facts_added = false;
            for (int rule_num : mini_set) {
                ss << eachRuleFP(rule_num, rules, facts_added);
            }
        }
    }
    else {
        for (int rule_num : mini_set) {
            ss << eachRule(rule_num, rules);
        }
    }
    ss << "\n";
    string the_string = ss.str();
    return the_string;
}

string Database::SCCprint(Graph& graph) {
    stringstream ss;
    vector<Rule> rules = the_datalog.getRules();
    //vector<Predicate> facts = the_datalog.getFacts();
    for (set<int> mini_set : graph.getSCCs()) {
        ss << eachSCC(mini_set, rules);
    }
    string the_string = ss.str();
    return the_string;
}

bool Database::contain(set<int>& set, int& i) {
    for (int integer : set) {
        if (integer == i) {
            return true;
        }
    }
    return false;
}

/*
 Bad Output:

*/

