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
        int GetNumberOfNodes();
        Node* CreateStar(string trans);
        Node* CreateOr(string trans1, string trans2);
        Node* CreateAnd(string trans1, string trans2);
};


