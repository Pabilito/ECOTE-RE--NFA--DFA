#pragma once
#include <string>

using namespace std;

class NodeMaster; //forward declaration needed here

void generateSubNFA(string RE, NodeMaster* master);
void part(string RE, NodeMaster* master, int start, int endd, int operators);


