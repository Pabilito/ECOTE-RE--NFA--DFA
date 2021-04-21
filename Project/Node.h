#pragma once
#include <string>
#include <vector>

using namespace std;

class Node {
	private:
		Node(int num, char trans);
		int NodeNumber;
		char Transition;
		vector<Node*> nextNodes;
};

Node::Node(int num, char trans) {
	Transition = trans;
	NodeNumber = num;
}

Node* constructNFA(string RE) {
	return nullptr;
}
