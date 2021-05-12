#include "Postfix.h"
#include <iostream>
#include <string>

using namespace std;

string PostFix(string RE){
    //generate + operators
    int lenght = RE.length();
    for (int i = 0; i < lenght-1; ++i) {
		if ((RE[i] >= 97 && RE[i] <= 122) && ((RE[i+1] >= 97 && RE[i+1] <= 122))){
			lenght++;
			RE.insert(i+1, "+");
		}
    }
    cout<<"RE: "+ RE <<endl;
    return RE;
}
