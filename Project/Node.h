#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "NodeMaster.h"                 //forward declaration was not enough

class Node {
	private:
		Node(int num, char trans, NodeMaster* master);
		int NodeNumber;
		char Transition;
		vector<Node*> nextNodes;
};

Node::Node(int num, char trans, NodeMaster* master) {
	Transition = trans;
	NodeNumber = num;
	master->IncrementNodes();
}

NodeMaster* constructNFA(string RE) {
    NodeMaster* master = new NodeMaster();
    //let's divide RE into parts
    //first we consider (), I have to get inside


	return master;
}
