#include <iostream>
#include <string>
#include <algorithm> //for counting number of symbols
#include "Node.h"
#include "NodeMaster.h"

using namespace std;

void part(string RE, NodeMaster* master, int start, int endd, int operators){

    string t, t1;                               //!Substitute later with actual strings
    for (int i=0; i<operators; i++){
         //get operators from left to right
        if(RE[end-operators+1+i] == "*"){
            Node* newNode = master->CreateStar(t);
        }else if(RE[end-operators+1+i] == "|"){
            Node* newNode = master->CreateOr(t, t1);
        }else //    + operator
            Node* newNode = master->CreateAnd(t, t1);
        }
    }

    return;
}


void generateSubNFA(string RE, NodeMaster* master){
    //generate NFA parts here

    //our postfix notation may have a few parts that we will glue together
    int lenght = RE.length();
    int start = 0;
    int endd = 0;
    int operators = 0;

    for (int i = 0; i < lenght; ++i) {
        if((RE[i] < 97 || RE[i] > 122) && RE[i]!=69 && endd == 0){              //if not a input symbol
            endd = -1;
            operators = 1;
        }
        else if(endd!=0 && ((RE[i] >= 'a' && RE[i] <= 'z') || RE[i]=='E')){     //beginning of a new substring
            endd = i-1;
            part(RE, master, start, endd, operators);                                      //generates a part
            start = i;
            endd = 0;
        }
        else{
            operators++;
        }
    }
    part(RE, master, start, lenght-1 ,operators);  //
    return;
}



