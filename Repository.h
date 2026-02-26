#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Commit.h"
#include "Branch.h"
#include<unordered_map>
#include<string>
#include<stack>

using namespace std;

class Repository{
    private:
        Commit* root; // first commit
        Commit* head; // latest commit (HEAD)

        int commitCounter; // auto-increment ID

        // Working directory (staged files)
        unordered_map<string, string> workingDir;

        stack<Commit*> undoStack;
        stack<Commit*> redoStack;

        Branch* branches; // head of branch list
        Branch* currentBranch; // active branch

        unordered_map<int, Commit*> allCommits;

        void restoreWorkingDirectory(Commit* commit);

    public:
        Repository();

        void addFile(string name, string content);

        void commit(string message);

        string showCurrentFiles();

        string showHistory();

        void undo();

        void redo();

        void createBranch(string name);

        void switchBranch(string name);

        string showBranches();

        Commit* findCommit(int id);

        void revertTo(int commitID);
        
        void mergeBranch(string name);

};

#endif
