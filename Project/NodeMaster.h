#pragma once
#include <string>

using namespace std;

class Node;

class NodeMaster{
    private:
        int NumberOfNodes = 0;
        int NumberOfNodeGroups = 0;
        Node* startNode = nullptr;
        vector<Node*> subNodeStart;
        vector<Node*> subNodeEnd;
    public:
        void IncrementNodes(int number);
        void IncrementNodeGroups(int number);
        Node* GetStartNode();
        void SetStartNode(Node* newstart);
        int GetNumberOfNodes();
        Node* CreateStar(char trans);
        Node* CreateOr(char trans1, char trans2);
        Node* CreateAnd(char trans1, char trans2);
        void check_if_start_node_exists(Node* newnode);
        void ternimateSubNodeGeneration();
};


