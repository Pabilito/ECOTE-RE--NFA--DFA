#include <iostream>
#include <string>
#include <vector>
#include "PostFix.h"
#include "SubNFA.h"
#include "Node.h"
#include "NodeMaster.h"

using namespace std;

Node::Node(int num){
	NodeNumber = num;
}

string Node::getTransitionAtPosition(int pos){
    string s(1,transition[pos]);
    return s;
}

Node* Node::findGroupEnd(){
    //!TO BE DONE
    return nullptr;
}

int Node::getNodeNumber(){
    return NodeNumber;
}

void Node::addNextNode(string tran, Node* next){
    nextNodes.push_back(next);
    transition += tran;             //append new transition symbol
}

NodeMaster* constructNFA(string RE) {
    RE = PostFix(RE);

    NodeMaster* master = new NodeMaster();

    generateSubNFA(RE, master);

	return master;
}

