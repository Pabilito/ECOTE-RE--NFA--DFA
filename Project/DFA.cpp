#include <iostream>
#include <string>
#include "DFA.h"
#include "NodeMaster.h"
#include "Node.h"
#include <unordered_map> //to count unique input symbols
#include <vector>
#include <algorithm>    // sort()

using namespace std;

void generateDFA(NodeMaster* master, string RE){

    unordered_map<char, int> m;                                 //I absolutely don't need map here, I know

    for (int i = 0; i < RE.length(); i++) {
        m[RE[i]]++;
    }

    //we don't care about some symbols
    if (RE.find('+') != string::npos){
        m.erase('+');
    }
    if (RE.find('|') != string::npos){
        m.erase('|');
    }
    if (RE.find('*') != string::npos){
         m.erase('*');
    }
    if (RE.find('E') != string::npos){
        m.erase('E');
    }

    vector<char> inputS;

    for (auto it = m.begin(); it != m.end(); ++it){
        inputS.push_back(it->first);
    }

    int inputSymbols = m.size();

    Node* startNode = new Node(master->GetNumberOfDFANodes());
    master->IncrementDFANodes(1);
    master->setDFAstart(startNode);

    vector<int> closure = master->getEClosure(master->GetStartNode()->getNodeNumber()); //find E-closure of initial node

    sort(closure.begin(), closure.end());
    startNode->DFANodes.insert(startNode->DFANodes.end(), closure.begin(), closure.end());  //saving closure as point A

    //start node can be final as well
    for(int z = 0; z != closure.size(); z++) {
        if(closure[z] == master->GetEndNode()->getNodeNumber()){
                master->getDFAstart()->endNode = true;
                break;
        }
    }

    for(int i=0; i<master->GetNumberOfDFANodes(); i++){         //check every new DFA node
        cout<<endl<<"Total nodes:"<<master->GetNumberOfDFANodes()<<endl;
        for(int j=0; j<inputSymbols; j++){                      //the number of times indicated by number of input symbols

            vector<int> testNode;
            vector<int> epsilonNode;

            testNode = master->getMove(master->getDFANodeWithIndex(i)->DFANodes, inputS[j]);

            if(!testNode.empty()){                              //we have some move function on this input symbol

                epsilonNode = master->getEClosure(testNode);    //works here
                sort(epsilonNode.begin(), epsilonNode.end());
                bool newNode = true;

                for(int k=0; k<master->GetNumberOfDFANodes(); k++){                        //check if such DFA node already exists
                    if(epsilonNode == master->getDFANodeWithIndex(k)->DFANodes){        //we have a new DFA node
                        newNode = false;
                        Node* tmp = master->getDFANodeWithIndex(k);
                        master->getDFANodeWithIndex(i)->addNextNodeDFA(inputS[j], tmp);
                        cout<<"NEW TRRANSITION ADDED"<<endl;
                        //! new transition here
                    }
                }

                if(newNode){    //create a new node
                    Node* newNode = new Node(master->GetNumberOfDFANodes());
                    newNode->DFANodes = epsilonNode;
                    master->IncrementDFANodes(1);
                    master->getDFANodeWithIndex(i)->addNextNodeDFA(inputS[j], newNode);

                    for(int z = 0; z != epsilonNode.size(); z++) {
                        if(epsilonNode[z] == master->GetEndNode()->getNodeNumber()){
                            newNode->endNode = true;
                        }
                    }
                    cout<<"NODE ADDED"<<endl;
                }
            }
        }
        cout<<"END ITERATION"<<endl;
    }
    return;
}

void printDFA(NodeMaster* master){
    Node* curr;
    cout<<endl<<"Printing DFA"<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    for(int i=0; i<master->GetNumberOfDFANodes(); i++){
        curr = master->getDFANodeWithIndex(i);

        if(i == 0){
            cout<<"S|";
        }else{
            cout<<"-|";
        }

        if(curr->endNode){
            cout<<"F ";
        }else{
            cout<<"- ";
        }

        cout<<"Node "<< static_cast<char> (i+65)<<"| Transitions = "<<curr->getNodeNumberOfTransitionsDFA()<<" |  ";
        for(int j=0; j<curr->getNodeNumberOfTransitionsDFA(); j++){
            cout<<" To ";
            cout<< static_cast<char> (curr->nextNodesDFA[j]->getNodeNumber() +65);
            cout<<" on "<<curr->getTransitionAtPositionDFA(j)<<" ";
        }
        cout<<endl;
    }
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;

    return;
}
