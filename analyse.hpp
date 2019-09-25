#ifndef __ANALYSE_HPP__
#define __ANALYSE_HPP__        

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "instructions.hpp"
using namespace std;

extern string return_value;
extern map<string, int> labels_map;
extern vector<BasicBlock*> basic_blocks;

map<BasicBlock*, set<string>> in_map;
map<BasicBlock*, set<string>> out_map;


void analyze_livness();
void set_in(BasicBlock *bb);
void set_out(BasicBlock *bb);
void azuriraj();

#endif