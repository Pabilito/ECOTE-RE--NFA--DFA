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
		vector<Node*> nextNodes;                                        //nodes and their transitions
    public:
        Node(int num);
        void addNextNode(char tran, Node* next);
        string getTransitionAtPosition(int pos);                        //get transition symbol of particular transition
        int getNodeNumber();
        Node* findGroupEnd();
};

NodeMaster* constructNFA(string RE);
