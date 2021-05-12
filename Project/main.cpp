#include "ErrorDetection.h"
#include "Node.h"
#include "NodeMaster.h"
#include "SubNFA.h"
#include <iostream>
#include <string>

using namespace std;

// 3. Write a program reading regular expressions, then constructing NFA using Thompson algorithm,
// converting NFA into DFA and checking if input strings are generated by this expression (working on DFA).

// ε - epsilon will be replaced with big E
// only 97-122 ASCII characters allowed (small letters)

int main()
{
	string RE = "((aaa|(ab|b)*)b)bb";
	int parenthesis = checkRE(RE);			//Check if RE can be used to construct NFA and return number of parenthesis.
                                            //If not, program will be terminated.
	NodeMaster* start = constructNFA(RE, parenthesis);
	cout << "Your input was: " + RE << endl;
	cout << "Postfix: " + RE << endl;
	cout << start->GetStartNode()->getNodeNumber() << start->GetStartNode()->getTransitionAtPosition(0);

	return 0;
}
