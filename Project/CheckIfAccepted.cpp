#include <iostream>
#include <string>
#include "NodeMaster.h"
#include "CheckIfAccepted.h"

void check(string input, NodeMaster* master){
    Node* curr = master->getDFAstart();
    for(int i=0; i<input.length(); i++){
        cout<<i;
    }
}

