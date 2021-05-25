#include <iostream>
#include "Node.h"
#include "NodeMaster.h"
#include <vector>

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
    if(startNode == nullptr)
    {
        SetStartNode(newnode);
    }
}

Node* NodeMaster::getNodeWithIndex(int index){
    Node* node = nullptr;
    if(startNode->getNodeNumber() == index){
        return startNode;
    }else{  //traverse the graph
        for(int i=0; i<startNode->getNodeNumberOfTransitions(); i++){
            node = SearchSubNode(startNode->nextNodes[i], index);
            if(node){           //if not nullptr
                return node;
            }
        }
    }

    cout<<"Node with such index could not be found - terminating process\n";
    exit(-2);                       //such number was not found
}

Node* NodeMaster::SearchSubNode(Node* node, int index){                     //recursively search graph
    Node* nodeReturn = nullptr;
    if(node->getNodeNumber() == index){
        return node;
    }else{
        for(int i=0; i<node->getNodeNumberOfTransitions(); i++){
            nodeReturn = SearchSubNode(node->nextNodes[i], index);
            if(nodeReturn){
                return nodeReturn;
            }
        }
    }
    return nullptr;     //this subgraph does not have this node
}

void NodeMaster::CreateStar(char trans){
    Node *node1, *node2, *node3, *node4;

    if((trans < 97 || trans > 122) && trans!=69){           //a group detected
        node1 = new Node(GetNumberOfNodes());               //only 2 new nodes needed
        node4 = new Node(GetNumberOfNodes()+1);
        IncrementNodes(2);
        node2 = subNodeStart[int(trans)-1];                   //get existing nodes
        node3 = subNodeEnd[int(trans)-1];

        //CHECK IF START CHANGED
        if(node2 == startNode){
            SetStartNode(node1);
        }

        cout<<"Processed complex STAR" << endl;
    }else{
        node1 = new Node(GetNumberOfNodes());
        node2 = new Node(GetNumberOfNodes()+1);
        node3 = new Node(GetNumberOfNodes()+2);
        node4 = new Node(GetNumberOfNodes()+3);
        IncrementNodes(4);
        node2->addNextNode(trans, node3);                   //if group exists, it already has this transition
        check_if_start_node_exists(node1);
        cout<<"Processed simple STAR" << endl;
    }

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node4);
    node3->addNextNode('E', node2);
    node3->addNextNode('E', node4);

    IncrementNodeGroups(1);                                 //we have a new group
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node4);

    return;
}

void NodeMaster::CreateOr(char trans1, char trans2){

    Node *node1, *node2, *node3, *node4, *node5, *node6;

    if(((trans1 < 97 || trans1 > 122) && trans1!=69) && ((trans2 < 97 || trans2 > 122) && trans2!=69)){           //a group detected
        //2 groups detected
        node1 = new Node(GetNumberOfNodes());                   //we need only 2 new nodes
        node6 = new Node(GetNumberOfNodes()+1);
        IncrementNodes(2);
        node2 = subNodeStart[int(trans1)-1];
        node4 = subNodeEnd[int(trans1)-1];
        node3 = subNodeStart[int(trans2)-1];
        node5 = subNodeEnd[int(trans2)-1];

        cout<<"Processed t1&t2 OR"<<endl;
    }else if((trans1 < 97 || trans1 > 122) && trans1!=69){
         //g1 is a group
        node1 = new Node(GetNumberOfNodes());                   //we need only 4 new nodes
        node3 = new Node(GetNumberOfNodes()+1);
        node5 = new Node(GetNumberOfNodes()+2);
        node6 = new Node(GetNumberOfNodes()+3);
        IncrementNodes(4);
        node2 = subNodeStart[int(trans1)-1];
        node4 = subNodeEnd[int(trans1)-1];

        node3->addNextNode(trans1, node5);

        cout<<"Processed t1 OR"<<endl;
    }else if((trans2 < 97 || trans2 > 122) && trans2!=69){
        //g2 is a group
        node1 = new Node(GetNumberOfNodes());                   //we need only 4 new nodes
        node3 = new Node(GetNumberOfNodes()+1);
        node5 = new Node(GetNumberOfNodes()+2);
        node6 = new Node(GetNumberOfNodes()+3);
        IncrementNodes(4);
        node2 = subNodeStart[int(trans2)-1];
        node4 = subNodeEnd[int(trans2)-1];

        node3->addNextNode(trans2, node5);

        cout<<"Processed t2 OR"<<endl;
    }else{
        node1 = new Node(GetNumberOfNodes());
        node2 = new Node(GetNumberOfNodes()+1);
        node3 = new Node(GetNumberOfNodes()+2);
        node4 = new Node(GetNumberOfNodes()+3);
        node5 = new Node(GetNumberOfNodes()+4);
        node6 = new Node(GetNumberOfNodes()+5);
        IncrementNodes(6);

        node2->addNextNode(trans1, node4);
        node3->addNextNode(trans2, node5);

        check_if_start_node_exists(node1);

        cout<<"Processed simple OR"<<endl;
    }

    //CHECK IF START CHANGED (start node was a part of one of the groups)
    if(node2 == startNode){
        SetStartNode(node1);
    }else if(node3 == startNode){
        SetStartNode(node1);
    }

    node1->addNextNode('E', node2);
    node1->addNextNode('E', node3);
    node4->addNextNode('E', node6);
    node5->addNextNode('E', node6);

    IncrementNodeGroups(1);
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node6);

    return;
}

void NodeMaster::CreateAnd(char trans1, char trans2){

    Node *node1, *node2, *node3;

    if(((trans1 < 97 || trans1 > 122) && trans1!=69) && ((trans2 < 97 || trans2 > 122) && trans2!=69)){           //a group detected
        //2 groups
        //No new nodes to be created
        node1 = subNodeEnd[int(trans1)];
        node3 = subNodeStart[int(trans2)];
        node1->addNextNode('E', node3);                     //we have epsilon transition from node1 to node2
        cout<<"Processed g1&g2 AND"<<endl;
    }else if((trans1 < 97 || trans1 > 122) && trans1!=69){
        //g1 is a group
        node3 = new Node(GetNumberOfNodes());
        node1 = subNodeEnd[int(trans1)-1];
        IncrementNodes(1);
        node1->addNextNode(trans2, node3);
        cout<<"Processed g1 AND"<<endl;
    }else if((trans2 < 97 || trans2 > 122) && trans2!=69){
        //g2 is a group
        node1 = new Node(GetNumberOfNodes());
        node3 = subNodeStart[int(trans2)-1];
        node1->addNextNode(trans1, node3);
        IncrementNodes(1);

        //CHECK IF START CHANGED
        if(node3 == startNode){
            SetStartNode(node1);
        }
        cout<<"Processed g2 AND"<<endl;
    }else{
                                                            //assume ab is at the beginning
        node3 = new Node(GetNumberOfNodes()+2);             //on b
        node2 = new Node(GetNumberOfNodes()+1);             //on a
        node1 = new Node(GetNumberOfNodes());               //start node
        IncrementNodes(3);

        //start --a--> 1 --b--> 2
        node1->addNextNode(trans1, node2);
        node2->addNextNode(trans2, node3);
        check_if_start_node_exists(node1);                  //it does not exist
        cout<<"Processed simple AND"<<endl;
    }

    IncrementNodeGroups(1);
    subNodeStart.push_back(node1);                          //push beginning and end of group of nodes into special vector
    subNodeEnd.push_back(node3);

    return;
}
