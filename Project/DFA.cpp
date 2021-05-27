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

    unordered_map<char, int> m;

    for (int i = 0; i < RE.length(); i++) {
        m[RE[i]]++;
    }

    int inputSymbols = m.size();

    //we don't care about some symbols
    if (RE.find('+') != string::npos){
        inputSymbols--;
    }
    if (RE.find('|') != string::npos){
        inputSymbols--;
    }
    if (RE.find('*') != string::npos){
        inputSymbols--;
    }
    if (RE.find('E') != string::npos){
        inputSymbols--;
    }

    Node* startNode = new Node(master->GetNumberOfDFANodes());
    master->IncrementDFANodes(1);
    master->setDFAstart(startNode);

    vector<vector<int>> DFAnodes;

    vector<int> closure = master->getEClosure(master->GetStartNode()->getNodeNumber()); //find E-closure of initial node

    sort(closure.begin(), closure.end());
    startNode->DFANodes.insert(startNode->DFANodes.end(), closure.begin(), closure.end());  //saving closure as point A
    DFAnodes.push_back(closure);
    cout<<"DFA 00:"<<DFAnodes[0][0]<<endl;       //works

    vector<int> test;
    test = master->getMove(DFAnodes[0], 'b');
    cout<<"Empty: "<<test.empty()<<endl;

    for(int i=0; i<master->GetNumberOfDFANodes(); i++){         //check every new DFA node
        for(int j=0; j<inputSymbols; j++){                      //the number of times indicated by number of input symbols

        }
    }

    return;
}

void printDFA(NodeMaster* master){
    cout<<endl<<"Printing DFA"<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;


    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;

    return;
}
