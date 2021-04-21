#include <iostream>
#include <string>
#include <algorithm> //for counting number of symbols
//#include "Node.h"
//#include "NodeMaster.h"
using namespace std;

class NodeMaster;
class Node; //forward declaration

void generateSubNFA(string subRE, NodeMaster* master){
    int stars = count(subRE.begin(), subRE.end(), '*');
    int ors = count(subRE.begin(), subRE.end(), '|');

    Node* starBegins[stars];

    for (int i=0; i<stars; i++){
        starBegins[i] = master->CreateStar("a"); //!!!CHANGE LATER
    }


}


