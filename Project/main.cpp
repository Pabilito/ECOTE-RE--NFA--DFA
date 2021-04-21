#include "ErrorDetection.h"
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

// 3. Write a program reading regular expressions, then constructing NFA using Thompson algorithm,
// converting NFA into DFA and checking if input strings are generated by this expression (working on DFA).

//ε - epsilon

int main()
{
	string RE;
    cout << "Please input RE:  ";
	cin >> RE;
									//Let's assume that RE will be composed of letters so I can use numbers to index nodes
	checkRE(RE);					//Check if RE can be used to construct NFA. If not, program will be terminated.
	Node* start = constructNFA(RE);
	cout << "Your input was " + RE;

	return 0;
}
