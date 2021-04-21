#include <iostream>
#include "Node.h"
#include "NodeMaster.h"

using namespace std;

void NodeMaster::IncrementNodes(int number){
    NumberOfNodes+=number;
}

void NodeMaster::IncrementNodeGroups(int number){
    NumberOfNodeGroups+=number;
}

int NodeMaster::GetNumberOfNodes(){
    return NumberOfNodes;
}

Node* NodeMaster::GetStartNode(){
    return startNode;
}

void NodeMaster::SetStartNode(Node* newstart){
        startNode = newstart;
}

Node* NodeMaster::CreateStar(string trans){
    Node* node1 = new Node(GetNumberOfNodes());             //We assume for now that it is the very first element
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);

    node1->addNextNode("E", node2);
    node1->addNextNode("E", node4);

    node2->addNextNode(trans, node3);

    node3->addNextNode("E", node2);
    node3->addNextNode("E", node4);

    if(GetStartNode() == nullptr){
        SetStartNode(node1);
    }

    IncrementNodes(4);
    IncrementNodeGroups(1);
    return node1;
}

Node* NodeMaster::CreateOr(string trans1, string trans2){
    IncrementNodes(6);
    return nullptr;
}

Node* NodeMaster::CreateAnd(string trans1, string trans2){
    IncrementNodes(2);
    return nullptr;
}
