#include <iostream>
#include <string>
#include <vector>
#include "PostFix.h"
#include "SubNFA.h"
#include "Node.h"
#include "NodeMaster.h"
#include "DFA.h"

using namespace std;

Node::Node(int num){
	NodeNumber = num;
}

string Node::getTransitionAtPosition(int pos){
    if(pos>=getNodeNumberOfTransitions()){              //there is no transition
        return "X";
    }
    string s(1,transition[pos]);
    return s;
}

int Node::getNodeNumberOfTransitions(){
    return transition.length();
}

int Node::getNodeNumberOfTransitionsDFA(){
    return transitionDFA.length();
}

int Node::getNodeNumber(){
    return NodeNumber;
}

void Node::addNextNode(char tran, Node* next){
    nextNodes.push_back(next);
    transition += tran;             //append new transition symbol
}

void Node::addNextNodeDFA(char tran, Node* next){
    nextNodesDFA.push_back(next);
    transitionDFA += tran;
}

NodeMaster* constructNFA(string RE) {
    RE = PostFix(RE);

    NodeMaster* master = new NodeMaster();

    generateSubNFA(RE, master);
    printNFA(master);
    generateDFA(master, RE);
    printDFA(master);

	return master;
}

