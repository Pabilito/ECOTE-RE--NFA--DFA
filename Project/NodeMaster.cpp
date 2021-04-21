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

Node* NodeMaster::CreateStar(string trans){
    Node* node1 = new Node(GetNumberOfNodes());             //We assume for now that it is the very first element
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);


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
