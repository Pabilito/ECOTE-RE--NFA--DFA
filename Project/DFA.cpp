#include <iostream>
#include <string>
#include "DFA.h"
#include "NodeMaster.h"
#include "Node.h"
#include <unordered_map> //to count unique input symbols

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

    Node* startNode = new Node();
    master->setDFAstart(startNode);

    return;
}

void printDFA(NodeMaster* master){
    cout<<endl<<"Printing DFA"<<endl<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;


    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;

    return;
}
