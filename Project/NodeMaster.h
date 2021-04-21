#pragma once
#include <iostream>

using namespace std;

class NodeMaster{
    private:
        int NumberOfNodes = 0;
    public:
        void IncrementNodes();
};

void NodeMaster::IncrementNodes(){
    NumberOfNodes++;
}
