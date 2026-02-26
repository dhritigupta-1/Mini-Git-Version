#ifndef COMMIT_H
#define COMMIT_H

#include<string>
#include<unordered_map>

using namespace std;

class Commit{
    public:
        int id; // unique commit number
        string message; // commit message

        // file name -> actual file content
        unordered_map<string, string> files;

        // Commit* left; // previous commit
        // Commit* right; // next commit
        // change to
        Commit* parent1; // primary parent
        Commit* parent2; // secondary parent (merge)

        Commit(int id, string msg, unordered_map<string, string> state){
            this->id = id;
            message = msg;
            files = state;

            // left = nullptr;
            // right = nullptr;

            parent1 = nullptr;
            parent2 = nullptr;
        }
};

#endif