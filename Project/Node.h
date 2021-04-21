#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SubNFA.h"

class NodeMaster; //forward declaration

class Node {
	private:
		Node(int num);
		int NodeNumber;
		int NodeGroupIndex;                                            //easier recognition of origin
		vector<char> transition;
		vector<Node*> nextNodes;                                        //nodes and their transitions
    public:
        void addNextNode(char tran, Node* next);
};

Node::Node(int num){
	NodeNumber = num;
}

void Node::addNextNode(char tran, Node* next){
    return;
}

NodeMaster* constructNFA(string RE, int parenthesis) {
    NodeMaster* master = new NodeMaster();
    int nesting, occurance;                                            //check how nested parenthesis is
    int indexBegin, length;

    if(parenthesis == 0){                                               //no parenthesis to take care of
        generateSubNFA(RE, master);
    }

    for(int i=parenthesis; i>0; --i){                                  //first we consider (), I have to get inside
        nesting = 0;
        indexBegin = -1;
        length = 0;
        occurance = 0;
        for (int j = 0; j < RE.length(); ++j) {                        //we will always find what we are looking for
            if(indexBegin>=0){
                ++length;                                              //we have found beginning of parenthesis clause
                if(RE[j] == '(') {
                    ++nesting;
                }
                else if(RE[j] == ')' && nesting>0){
                    --nesting;
                }
                else if(RE[j] == ')'){
                    generateSubNFA(RE.substr(indexBegin+1, length-1), master);
                    //simplify RE
                    RE = RE.substr(0, indexBegin) + "[" + to_string(i) + "]" + RE.substr(indexBegin+length+1, RE.length()-indexBegin-length-1);
                    cout << RE << endl;
                    break;
                }
                continue;                                               //optimization
            }
            if (RE[j] == '(') {
                occurance += 1;
                if(occurance == parenthesis){
                    indexBegin = j;
                }
            }
        }
        --parenthesis;
    }

	return master;
}

//!---------------------NODEMASTER---------------------

class NodeMaster{
    private:
        int NumberOfNodes = 0;
        int NumberOfNodeGroups = 0;
        Node* startNode = nullptr;
    public:
        void IncrementNodes(int number);
        void IncrementNodeGroups(int number);
        int GetNumberOfNodes();
        Node* CreateStar(string trans);
        Node* CreateOr(string trans1, string trans2);
        Node* CreateAnd(string trans1, string trans2);
};

void NodeMaster::IncrementNodes(int number){
    NumberOfNodes+=number;
}

void NodeMaster::IncrementNodeGroups(int number){
    NumberOfNodeGroups+=number;
}

int NodeMaster::GetNumberOfNodes(){
    return NumberOfNodes;
}

Node* NodeMaster::CreateStar(string trans){
    Node* node1 = new Node(GetNumberOfNodes());             //We assume for now that it is the very first element
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);


    IncrementNodes(4);
    IncrementNodeGroups(1);
    return node1;
}

Node* NodeMaster::CreateOr(string trans1, string trans2){
    IncrementNodes(6);
    return nullptr;
}

Node* NodeMaster::CreateAnd(string trans1, string trans2){
    IncrementNodes(2);
    return nullptr;
}
