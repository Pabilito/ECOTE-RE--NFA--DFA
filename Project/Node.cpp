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

NodeMaster* constructNFA(string RE, int parenthesis) {
    RE = PostFix(RE);

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

