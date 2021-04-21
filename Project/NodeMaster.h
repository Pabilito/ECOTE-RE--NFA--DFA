#pragma once
#include <string>

using namespace std;

class Node;

class NodeMaster{
    private:
        int NumberOfNodes = 0;
        int NumberOfNodeGroups = 0;
        Node* startNode = nullptr;
    public:
        void IncrementNodes(int number);
        void IncrementNodeGroups(int number);
        Node* GetStartNode();
        void SetStartNode(Node* newstart);
        int GetNumberOfNodes();
        Node* CreateStar(string trans);
        Node* CreateOr(string trans1, string trans2);
        Node* CreateAnd(string trans1, string trans2);
        void check_if_start_node_exists(Node* newnode);
};


