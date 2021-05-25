#pragma once
#include <string>
#include <vector>

using namespace std;

class NodeMaster; //forward declaration needed here

void generateSubNFA(string RE, NodeMaster* master);
void printNFA(NodeMaster* master);
