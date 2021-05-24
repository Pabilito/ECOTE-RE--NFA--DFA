#include <iostream>
#include <string>
#include <algorithm> //for counting number of symbols
#include "Node.h"
#include "NodeMaster.h"

using namespace std;

void generateSubNFA(string RE, NodeMaster* master){

    //I need a stack of symbols
    char stackOfSymbols[length];
    //if char is a number we process a grouped expression

    int height = 0;

    for (int i = 0; i < lenght; ++i) {
        if((RE[i] < 97 || RE[i] > 122) && RE[i]!=69 && endd == 0){              //operator detected
            if(RE[i] == '*' && height>=1){
                master->CreateStar(stackOfSymbols[height]);
            }else if(RE[i] == '|' && height>=2){
                master->CreateOr(stackOfSymbols[height-1], stackOfSymbols[height]);
            }else if(RE[i] == '+' && height>=2){
                master->CreateAnd(stackOfSymbols[height-1], stackOfSymbols[height]);
            }else{
                cout<<"Too many operators/too few input symols"<<endl;
            }
        }
        else{
            ++height;
            stackOfSymbols[height] = RE[i];                                     //put character on the stack
        }
    }

    return;
}



