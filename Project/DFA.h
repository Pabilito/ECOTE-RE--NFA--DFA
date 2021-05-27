#pragma once
#include <string>

using namespace std;

class NodeMaster;

void generateDFA(NodeMaster* master, string RE);
void printDFA(NodeMaster* master);
