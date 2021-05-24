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

Node* NodeMaster::CreateStar(char trans){
    if((trans < 97 || trans > 122) && trans!=69){           //a group detected
        //DO GROUP MAGIC
    }

    Node* node1 = new Node(GetNumberOfNodes());
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);
    IncrementNodes(4);

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node4);
    node2->addNextNode(trans, node3);
    node3->addNextNode('E', node2);
    node3->addNextNode('E', node4);

    IncrementNodeGroups(1);                                 //we have a new group
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node4);
    check_if_start_node_exists(node1);

    cout<<"Processed simple STAR" << endl;

    return node1;
}

Node* NodeMaster::CreateOr(char trans1, char trans2){
    if(((trans1 < 97 || trans1 > 122) && trans1!=69) && ((trans2 < 97 || trans2 > 122) && trans2!=69)){           //a group detected
        //2 groups
    }else if((trans1 < 97 || trans1 > 122) && trans1!=69){
        //t1 is a group
    }else if((trans2 < 97 || trans2 > 122) && trans2!=69){
        //t2 is a group
    }

    Node* node1 = new Node(GetNumberOfNodes());
    Node* node2 = new Node(GetNumberOfNodes()+1);
    Node* node3 = new Node(GetNumberOfNodes()+2);
    Node* node4 = new Node(GetNumberOfNodes()+3);
    Node* node5 = new Node(GetNumberOfNodes()+4);
    Node* node6 = new Node(GetNumberOfNodes()+5);
    IncrementNodes(6);

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node3);
    node2->addNextNode(trans1, node4);
    node3->addNextNode(trans2, node5);
    node4->addNextNode('E', node6);
    node5->addNextNode('E', node6);

    IncrementNodeGroups(1);
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node6);
    check_if_start_node_exists(node1);

    cout<<"Processed simple OR"<<endl;

    return node1;
}

Node* NodeMaster::CreateAnd(char trans1, char trans2){

    if(((trans1 < 97 || trans1 > 122) && trans1!=69) && ((trans2 < 97 || trans2 > 122) && trans2!=69)){           //a group detected
        //2 groups
    }else if((trans1 < 97 || trans1 > 122) && trans1!=69){
        //t1 is a group
    }else if((trans2 < 97 || trans2 > 122) && trans2!=69){
        //t2 is a group
    }

                                                        //assume ab is at the beginning
    Node *node3 = new Node(GetNumberOfNodes()+2);       //on b
    Node *node2 = new Node(GetNumberOfNodes()+1);       //on a
    Node *node1 = new Node(GetNumberOfNodes());         //start node
    IncrementNodes(3);

    //start --a--> 1 --b--> 2
    node1->addNextNode(trans1, node2);
    node2->addNextNode(trans2, node3);

    IncrementNodeGroups(1);
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node3);
    check_if_start_node_exists(node1);

    cout<<"Processed simple AND"<<endl;

    return node1;
}
