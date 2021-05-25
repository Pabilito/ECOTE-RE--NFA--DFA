#pragma once
#include <string>
#include <vector>

using namespace std;

class NodeMaster;

class Node {
	private:
		int NodeNumber;
		int NodeGroupIndex;                                             //easier recognition of origin
		string transition = "";                                         //consecutive letters define consecutive transitions
    public:
        Node(int num);
        vector<Node*> nextNodes;                                        //nodes and their transitions
        void addNextNode(char tran, Node* next);
        string getTransitionAtPosition(int pos);                        //get transition symbol of particular transition
        int getNodeNumber();
        int getNodeNumberOfTransitions();
};

NodeMaster* constructNFA(string RE);
