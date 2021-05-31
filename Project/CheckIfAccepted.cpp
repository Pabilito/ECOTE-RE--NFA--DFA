#include <iostream>
#include <string>
#include "NodeMaster.h"
#include "CheckIfAccepted.h"

void check(string input, NodeMaster* master){
    Node* curr = master->getDFAstart();
    cout<<"Transitions order: A";
    for(int i=0; i<input.length(); i++){
        curr = master->findDFAnodeATtransition(input[i], curr);
        if(curr == nullptr){
            cout<<endl<<"String "<<input<<" is not accepted! Invalid transition found"<<endl;
        }
        cout<<static_cast<char> (curr->getNodeNumber()+65);
    }

    if(!curr->endNode){
        cout<<endl<<"String "<<input<<" is not accepted! It doesn't end in final state"<<endl;
    }else{
        cout<<endl<<"String "<<input<<" is accepted!"<<endl;
    }
}

