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

void NodeMaster::check_if_start_node_exists(Node* newnode){
    SetStartNode(newnode);
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

    check_if_start_node_exists(node1);

    IncrementNodes(4);
    IncrementNodeGroups(1);
    return node1;
}

Node* NodeMaster::CreateOr(string trans1, string trans2){
    Node* node1 = new Node(GetNumberOfNodes());
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);
    Node* node5 = new Node(GetNumberOfNodes()+4);
    Node* node6 = new Node(GetNumberOfNodes()+5);

    node1->addNextNode("E", node2);
    node1->addNextNode("E", node3);

    node2->addNextNode(trans1, node4);

    node3->addNextNode(trans2, node5);

    node4->addNextNode("E", node6);

    node5->addNextNode("E", node6);

    check_if_start_node_exists(node1);

    IncrementNodes(6);
    IncrementNodeGroups(1);
    return node1;
}

Node* NodeMaster::CreateAnd(string trans1, string trans2){
    Node* node1 = new Node(GetNumberOfNodes());



    //!ASSIGN NEXT TRANSITION

    check_if_start_node_exists(node1);

    IncrementNodeGroups(1);
    IncrementNodes(2);
    return node1;
}
