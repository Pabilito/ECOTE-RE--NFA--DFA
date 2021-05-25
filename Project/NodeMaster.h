#pragma once
#include <string>
#include <vector>

using namespace std;

class Node;

class NodeMaster{
    private:
        int NumberOfNodes = 0;
        int NumberOfNodeGroups = 0;
        Node* startNode = nullptr;
        Node* endNode = nullptr;
        vector<Node*> subNodeStart;
        vector<Node*> subNodeEnd;
        Node* SearchSubNode(Node* node, int index, vector<int> indexList);
    public:
        void setEndNode(Node* node);
        void IncrementNodes(int number);
        void IncrementNodeGroups(int number);
        Node* GetStartNode();
        Node* GetEndNode();
        void SetStartNode(Node* newstart);
        int GetNumberOfNodes();
        void CreateStar(char trans);
        void CreateOr(char trans1, char trans2);
        void CreateAnd(char trans1, char trans2);
        void check_if_start_node_exists(Node* newnode);
        void ternimateSubNodeGeneration();
        Node* getNodeWithIndex(int index);
};


