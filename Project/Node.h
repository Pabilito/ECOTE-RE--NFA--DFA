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
        string transitionDFA = "";
    public:
        bool endNode = false;
        Node(int num);
        vector<Node*> nextNodes;                                        //nodes and their transitions
        vector<Node*> nextNodesDFA;
        vector<int> DFANodes;
        void addNextNode(char tran, Node* next);
        void addNextNodeDFA(char tran, Node* next);
        string getTransitionAtPosition(int pos);                        //get transition symbol of particular transition
        string getTransitionAtPositionDFA (int pos);
        int getTransitionAtInput(string input);
        int getNodeNumber();
        int getNodeNumberOfTransitions();
        int getNodeNumberOfTransitionsDFA();
};

NodeMaster* constructNFA(string RE);
