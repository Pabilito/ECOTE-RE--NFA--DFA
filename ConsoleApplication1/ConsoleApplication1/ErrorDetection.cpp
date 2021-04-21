#include "Headers.h"
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

void checkRE(string RE) {
	//allowed symbos are ()|*
	if (RE == "") {
		cout << "Empty string!  Aborting!";
		exit(-1);
	}

	int countL = 0, countR = 0;
	char prev = ' ';
	int lenght = RE.length();

	if (RE[0] == '|' || RE[0] == ')' || RE[0] == '*') {
		cout << "RE cannot start with )|* symbols. Aborting!";
		exit(-4);
	}
	else if (RE[lenght-1] == '(' || RE[lenght-1] == '|') {
		cout << "RE cannot end with (| symbols. Aborting!";
		exit(-4);
	}

	for (int i = 0; i < lenght; ++i) {
		if (RE[i] == '(') {
			countL++;
		}
		else if (RE[i] == ')') {
			countR++;
		}
		else if (prev == '|' && RE[i] == '|'  || prev == '*' && RE[i] == '*') {
			cout << "|| or ** are not accepted!  Aborting!";
			exit(-3);
		}
		prev = RE[i];
	}

	if (countL != countR) {
		cout << "Unequal number of left and right parenthesis! Aborting!";
		exit(-2);
	}

}