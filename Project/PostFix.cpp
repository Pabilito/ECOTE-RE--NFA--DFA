#include "Postfix.h"
#include<bits/stdc++.h>         //stack operations
#include <iostream>
#include <string>

using namespace std;

//Precedence of operators
int prec(char c) {
    if(c == '|'){
        return 1;
    }
    else if(c == '+'){
        return 0;
    }
    else{
        return -1;
    }

}


string PostFix(string RE){
    //generate + operators
    int lenght = RE.length();
    for (int i = 0; i < lenght-1; ++i) {
		if ((RE[i] >= 97 && RE[i] <= 122) && ((RE[i+1] >= 97 && RE[i+1] <= 122) || RE[i+1]=='E')){
			lenght++;
			RE.insert(i+1, "+");
		}//we need also + operators after stars if the are some input symbols later - AND
		else if((RE[i] == '*') && ((RE[i+1] >= 97 && RE[i+1] <= 122) || RE[i+1]=='E')){
            lenght++;
			RE.insert(i+1, "+");
		}//brackets before symbol are by default AND symbol
		else if((RE[i] == ')') && ((RE[i+1] >= 97 && RE[i+1] <= 122) || RE[i+1]=='E')){
            lenght++;
			RE.insert(i+1, "+");
		}//brackets after symbol are by default AND symbol
		else if((RE[i+1] == '(') && ((RE[i] >= 97 && RE[i] <= 122)|| RE[i]=='E')){
            lenght++;
			RE.insert(i+1, "+");
		}
    }


    cout<<"RE: "+ RE <<endl;

    stack<char> st;
    string result;

    for(int i = 0; i < lenght; i++) {
        char c = RE[i];

        //Look for characters
        if((c >= 'a' && c <= 'z') || c == 'E' || c=='*'){                //star is already in postfix
            result += c;
        }

        //Push ( to the stack
        else if(c == '('){
            st.push('(');
        }

        // If the scanned character is an ‘)’,
        // pop and to output string from the stack until ‘(‘
        else if(c == ')') {
            while(!st.empty() && st.top() != '(')
            {
                char temp = st.top();
                st.pop();
                result += temp;
            }
            st.pop();
        }

        //Look for operands
        else {
            while(!st.empty() && prec(RE[i]) <= prec(st.top())) {
                char temp = st.top();
                st.pop();
                result += temp;
            }
            st.push(c);
        }
    }

    // Pop stack
    while(!st.empty()) {
        char temp = st.top();
        st.pop();
        result += temp;
    }

    cout << "Postfix: " << result << endl;
    return result;
}
