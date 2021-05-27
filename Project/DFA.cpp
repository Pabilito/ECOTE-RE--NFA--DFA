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

    vector<vector<int>> DFAnodes;

    vector<int> closure = master->getEClosure(master->GetStartNode()->getNodeNumber()); //find E-closure of initial node

    sort(closure.begin(), closure.end());
    startNode->DFANodes.insert(startNode->DFANodes.end(), closure.begin(), closure.end());  //saving closure as point A
    DFAnodes.push_back(closure);
    cout<<"DFA 00:"<<DFAnodes[0][0]<<endl;       //works

    vector<int> testNode;
    vector<int> epsilonNode;
    testNode = master->getMove(DFAnodes[0], 'b');
    cout<<"Empty: "<<testNode.empty()<<endl;

    for(int i=0; i<master->GetNumberOfDFANodes(); i++){         //check every new DFA node
        for(int j=0; j<inputSymbols; j++){                      //the number of times indicated by number of input symbols
            testNode = master->getMove(DFAnodes[0], inputS[j]);
            if(!testNode.empty()){                              //we have some move function on this input symbol
                cout<<"Help DFA function";
                epsilonNode = master->getEClosure(testNode);
                sort(epsilonNode.begin(), epsilonNode.end());
                bool newNode = true;
                int k;
                for(k=0; k<master->GetNumberOfDFANodes(); k++){                         //check if such DFA node already exists
                    if(epsilonNode == master->getDFANodeWithIndex(k)->DFANodes){        //we have a new DFA node
                        newNode = false;
                        //!potentially new transition here
                    }
                }
                if(newNode){    //create a new node
                    Node* newNode = new Node(master->GetNumberOfDFANodes());
                    master->IncrementDFANodes(1);
                    master->getNodeWithIndex(k)->addNextNodeDFA(m[j], newNode);
                    newNode->DFANodes.insert(newNode->DFANodes.end(), epsilonNode.begin(), epsilonNode.end());
                }
            }
        }
    }

    cout<<"DFA nodes: "<< master->GetNumberOfDFANodes()<<endl;
    return;
}

void printDFA(NodeMaster* master){
    cout<<endl<<"Printing DFA"<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;


    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;

    return;
}
