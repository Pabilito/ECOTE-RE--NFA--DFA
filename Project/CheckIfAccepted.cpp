#include <iostream>
#include <string>
#include "NodeMaster.h"
#include "Node.h"
#include "CheckIfAccepted.h"

void check(string input, NodeMaster* master){
    if(input == "E"){
        if(master->getDFAstart()->endNode){
            cout<<endl<<"String "<<input<<" is accepted! Start node is accepting node!"<<endl<<endl;
        }else{
            cout<<endl<<"String "<<input<<" is not accepted! DFA doesn't start in final state"<<endl<<endl;
        }
    }

    Node* curr = master->getDFAstart();
    cout<<"Transition's order: A";
    for(int i=0; i<input.length(); i++){
        string s(1, input[i]);
        curr = master->findDFAnodeATtransition(s, curr);
        if(curr == nullptr){
            cout<<endl<<"String "<<input<<" is not accepted! Invalid transition or input symbol found"<<endl<<endl;
            return;
        }
        cout<<"->"<<static_cast<char> (curr->getNodeNumber()+65);
    }

    if(!curr->endNode){
        cout<<endl<<"String "<<input<<" is not accepted! It doesn't end in final state"<<endl<<endl;
    }else{
        cout<<endl<<"String "<<input<<" is accepted!"<<endl<<endl;
    }
}

