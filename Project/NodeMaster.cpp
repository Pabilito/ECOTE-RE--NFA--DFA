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

void NodeMaster::ResetSubNode(){
    Node* subNodeStart = nullptr;
    //!DONT CLEAR SUBNODE END
    bool subnodeStart = true;
    IncrementNodeGroups(1);
}

Node* NodeMaster::CreateStar(char trans){
    Node *node2, *node3;

    Node* node1 = new Node(GetNumberOfNodes());             //We assume for now that it is the very first element
    if(!subNodeStart){                                       //We encapsulate the expression we already have
        node2 = subNodeStart;
        node3 = subNodeEnd;
        IncrementNodes(2);
        //we already have transition 2->3
    }else{
        node2 = new Node(GetNumberOfNodes()+1);
        node3 = new Node(GetNumberOfNodes()+2);
        node2->addNextNode(trans, node3);
        IncrementNodes(4);
    }

    Node* node4 = new Node(GetNumberOfNodes()+3);

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node4);

    node3->addNextNode('E', node2);
    node3->addNextNode('E', node4);

    subNodeStart = node1;
    subNodeEnd = node4;

    check_if_start_node_exists(node1);

    subnodeStart = false;

    cout<<"Processed STAR" << endl;

    return node1;
}

Node* NodeMaster::CreateOr(char trans1, char trans2){
    if(subnodeStart){                   //SHOULD WORK ONLY IN THIS CASE
        cout<<"This part of code works only when or is a beginning of substring.";
        exit(-1);
    }

    Node* node1;

    if(!subNodeEnd){
        node1 = new Node(GetNumberOfNodes());
        IncrementNodes(6);
        check_if_start_node_exists(node1);
    }else{
        node1 = subNodeEnd;                 //Link with previous part
        IncrementNodes(5);
    }

    Node* node2 = new Node(GetNumberOfNodes()-5);
    Node* node3 = new Node(GetNumberOfNodes()-4);
    Node* node4 = new Node(GetNumberOfNodes()-3);
    Node* node5 = new Node(GetNumberOfNodes()-2);
    Node* node6 = new Node(GetNumberOfNodes()-1);

    subNodeStart = node1;
    subNodeEnd = node6;

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node3);

    node2->addNextNode(trans1, node4);

    node3->addNextNode(trans2, node5);

    node4->addNextNode('E', node6);

    node5->addNextNode('E', node6);

    subnodeStart = false;

    cout<<"Processed OR"<<endl;

    return node1;
}

Node* NodeMaster::CreateAnd(char trans1, char trans2){

    Node *node1, *node2, *node3;


    if(subnodeStart && !subNodeEnd){                    //assume ab is at the beginning
        node3 = new Node(GetNumberOfNodes()+2);         //on b
        node2 = new Node(GetNumberOfNodes()+1);         //on a
        node1 = new Node(GetNumberOfNodes());           //start node
        IncrementNodes(3);
        subNodeStart = node1;
        subNodeEnd = node3;
        check_if_start_node_exists(node1);

        node1->addNextNode(trans1, node2);
        node2->addNextNode(trans2, node3);
    }else{                                              //we already have 'a' in the diagram so we only need to add b
        node1 = subNodeEnd;
        node2 = new Node(GetNumberOfNodes());
        IncrementNodes(1);
        subNodeEnd = node2;

        node1->addNextNode(trans2, node2);
    }

    subnodeStart = false;

    node1->addNextNode('E', node2);

    cout<<"Processed AND"<<endl;

    return node1;
}
