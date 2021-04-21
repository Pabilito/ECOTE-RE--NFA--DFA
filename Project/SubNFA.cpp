#include <iostream>
#include <string>
#include <algorithm> //for counting number of symbols
#include "Node.h"
#include "NodeMaster.h"

using namespace std;

void generateSubNFA(string subRE, NodeMaster* master){
    int stars = count(subRE.begin(), subRE.end(), '*');
    int ors = count(subRE.begin(), subRE.end(), '|');

    Node* starBegins[stars];
    Node* orBegins[ors];

    for (int i=0; i<stars; i++){
        starBegins[i] = master->CreateStar("a"); //!!!CHANGE LATER WITH ACTUAL VALUE
    }

    //! consider sequences of characters here

    for (int i=0; i<ors; i++){
        //!DO STH
    }
}



