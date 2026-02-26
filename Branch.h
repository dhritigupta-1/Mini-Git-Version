#ifndef BRANCH_H
#define BRANCH_H

#include "Commit.h"
#include <string>

using namespace std;

class Branch{
    public:

        string name; // branch name
        Commit* head; // latest commit on this branch
        Branch* next; // next branch in list

        Branch(string n, Commit* h){
            name = n;
            head = h;
            next = nullptr;
        }
};

#endif