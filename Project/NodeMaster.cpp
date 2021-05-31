#include <iostream>
#include "Node.h"
#include "NodeMaster.h"
#include <vector>
#include <algorithm>    //for find

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

int NodeMaster::GetNumberOfDFANodes(){
    return NumberOfDFANodes;
}

Node* NodeMaster::getDFAstart(){
    return startDFA;
}

void NodeMaster::IncrementDFANodes(int number){
    NumberOfDFANodes += number;
}

void NodeMaster::setDFAstart(Node* node){
    startDFA = node;
}

Node* NodeMaster::GetStartNode(){
    return startNode;
}

Node* NodeMaster::GetEndNode(){
    return endNode;
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

void NodeMaster::setEndNode(Node* node){
    endNode = node;
}

vector<int> NodeMaster::RecursiveClosure(Node* node, vector<int> indexes){

    for(int a=0; a<indexes.size(); a++){
            cout<<"|";
        cout<<indexes[a];
    }

    if (find(indexes.begin(), indexes.end(), node->getNodeNumber()) != indexes.end()) {
        //WE HAVE ALREADY BEEN HERE OR WE ARE IN A LOOP
        return indexes;
    }

    indexes.push_back(node->getNodeNumber());
    cout<<"    |Recursive closure - current node: " << node->getNodeNumber()<<endl;

    for(int i=0; i<node->getNodeNumberOfTransitions(); i++){
        if(node->getTransitionAtPosition(i) == "E"){           //we are search for E transitions
            indexes = RecursiveClosure(node->nextNodes[i], indexes);
        }
    }
    return indexes;
}

vector<int> NodeMaster::getEClosure(int nodeNumber){                //closure for single node
    Node* myNode = getNodeWithIndex(nodeNumber);
    vector <int> vec;
    vec.push_back(nodeNumber);  //we always add start point
    //traverse the graph

    for(int i=0; i<myNode->getNodeNumberOfTransitions(); i++){
        if(myNode->getTransitionAtPosition(i) == "E"){           //we are search for E transitions
            vec = RecursiveClosure(myNode->nextNodes[i], vec);
        }
    }
    return vec;
}

vector<int> NodeMaster::getEClosure(vector<int> moveNodes){       //closure for the set
    vector <int> vec;
    for(int k=0; k<moveNodes.size(); k++){ //extra for loop to prevent pointless going through the graph
        vec.push_back(moveNodes[k]);  //we always add start point
    }

    for(int l=0; l<moveNodes.size(); l++){
        Node* myNode = getNodeWithIndex(moveNodes[0]);
        for(int i=0; i<myNode->getNodeNumberOfTransitions(); i++){
            if(myNode->getTransitionAtPosition(i) == "E"){           //we are search for E transitions
                /*
                cout<<"Calling main rec: " << myNode->getNodeNumber()<<"->";
                for(int a=0; a<vec.size(); a++){
                    cout<<"|";
                    cout<<vec[a];
                }
                cout<<endl;
                */
                vec = RecursiveClosure(myNode->nextNodes[i], vec);
            }
        }
    }

    //PRINTING INFO
    cout<<"E-closure{";
    for(int a=0; a<moveNodes.size(); a++){
        cout<<moveNodes[a]<<",";
    }
    cout<<"}={";
    for(int a=0; a<vec.size(); a++){
        cout<<vec[a]<<",";
    }
    cout<<"}\n";

    return vec;
}

vector<int> NodeMaster::getMove(vector<int> DFAnode, char trans){
    vector <int> vec = {};
    for (int i = 0; i < DFAnode.size(); i++){
        for(int j = 0; j < getNodeWithIndex(DFAnode[i])->getNodeNumberOfTransitions(); j++){
            int index = getNodeWithIndex(DFAnode[i])->nextNodes[j]->getNodeNumber();
            if(find(DFAnode.begin(), DFAnode.end(), index) != DFAnode.end())
            {//node already in the list
                continue;
            }
            else if(string(1,trans) == getNodeWithIndex(DFAnode[i])->getTransitionAtPosition(j))
            {
                vec.push_back(index);
            }
        }
    }

    cout<<"Move({";
    for (int i = 0; i < DFAnode.size(); i++){
        cout<<DFAnode[i];
    }
    cout<<"},"<<trans<<")={";
    for (int i = 0; i < vec.size(); i++){
        cout<<vec[i];
    }
    cout<<"}\n";
    return vec;
}

Node* NodeMaster::getDFANodeWithIndex(int index)
{
    Node* node = nullptr;

    vector<int> indexList;                              //used to detect loops
    indexList.push_back(startDFA->getNodeNumber());

    if(startDFA->getNodeNumber() == index){
        return startDFA;
    }else{  //traverse the graph
        for(int i=0; i<startDFA->getNodeNumberOfTransitions(); i++){
            node = SearchSubNodeDFA(startDFA->nextNodesDFA[i], index, indexList);
            if(node){           //if not nullptr
                return node;
            }
        }
    }

    cout<<"Node with such index could not be found - terminating process\n";
    exit(-2);                       //such number was not found

}

Node* NodeMaster::getNodeWithIndex(int index){
    Node* node = nullptr;

    vector<int> indexList;                              //used to detect loops
    indexList.push_back(startNode->getNodeNumber());

    if(startNode->getNodeNumber() == index){
        return startNode;
    }else{  //traverse the graph
        for(int i=0; i<startNode->getNodeNumberOfTransitions(); i++){
            node = SearchSubNode(startNode->nextNodes[i], index, indexList);
            if(node){           //if not nullptr
                return node;
            }
        }
    }

    cout<<"Node with such index could not be found - terminating process\n";
    exit(-2);                       //such number was not found
}

Node* NodeMaster::SearchSubNodeDFA(Node* node, int index, vector<int> indexList){                     //recursively search graph
    Node* nodeReturn = nullptr;

    if (find(indexList.begin(), indexList.end(), node->getNodeNumber()) != indexList.end()) {
        //WE ARE IN A LOOP
        return nullptr;
    }else if(node->getNodeNumber() == index){
        return node;
    }else{
        for(int i=0; i<node->getNodeNumberOfTransitions(); i++){
            indexList.push_back(node->getNodeNumber());
            nodeReturn = SearchSubNode(node->nextNodesDFA[i], index, indexList);
            if(nodeReturn){
                return nodeReturn;
            }
        }
    }
    return nullptr;     //this subgraph does not have this node
}

Node* NodeMaster::SearchSubNode(Node* node, int index, vector<int> indexList){                     //recursively search graph
    Node* nodeReturn = nullptr;

    if (find(indexList.begin(), indexList.end(), node->getNodeNumber()) != indexList.end()) {
        //WE ARE IN A LOOP
        return nullptr;
    }else if(node->getNodeNumber() == index){
        return node;
    }else{
        for(int i=0; i<node->getNodeNumberOfTransitions(); i++){
            indexList.push_back(node->getNodeNumber());
            nodeReturn = SearchSubNode(node->nextNodes[i], index, indexList);
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
        node1 = subNodeEnd[int(trans1)-1];
        node3 = subNodeStart[int(trans2)-1];
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

        node3=subNodeEnd[int(trans2)-1];                    //change for correct subnodeend usage
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
