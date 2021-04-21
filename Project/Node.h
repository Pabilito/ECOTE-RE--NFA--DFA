#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "NodeMaster.h"                 //forward declaration was not enough
#include "SubNFA.h"

class Node {
	private:
		Node(int num, char trans, NodeMaster* master);
		int NodeNumber;
		int NodeGroupIndex;                                            //easier recognition of origin
		char Transition;
		vector<Node*> nextNodes;
};

Node::Node(int num, char trans, NodeMaster* master) {
	Transition = trans;
	NodeNumber = num;
	master->IncrementNodes();
}

NodeMaster* constructNFA(string RE, int parenthesis) {
    NodeMaster* master = new NodeMaster();
    int nesting, occurance;                                            //check how nested parenthesis is
    int indexBegin, length;

    if(parenthesis == 0){                                               //no parenthesis to take care of
        generateSubNFA(RE);
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
                    generateSubNFA(RE.substr(indexBegin+1, length-1));
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
