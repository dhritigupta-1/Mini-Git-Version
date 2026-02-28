#include "Repository.h"
#include<iostream>
#include <unordered_set>

using namespace std;

// Constructor
Repository::Repository() {
    root = nullptr; // first commit
    head = nullptr; // latest commit (HEAD)
    commitCounter = 0; // auto-increment ID

    branches = nullptr; // head of branch list
    currentBranch = nullptr; // active branch
}

// Function 1: Add File
void Repository::addFile(string name, string content){

    workingDir[name] = content; // stage file in working directory
    // staged files are not yet in commit until commit() is called, so we just add to workingDir and print message

    cout<< "File added: "<< name << endl; 
}

// Function 2: Commit
// Most Important operation as it creates a new commit with snapshot of files and updates history

void Repository::commit(string message){

    if(workingDir.empty()){
        cout<< "Nothing to commit.\n";
        return;
    }

    // Create snapshot of files (hashing)
    unordered_map<string, string> snapshot; // snapshot : in-memory representation of files at commit time

    for(auto &file : workingDir){

        // Simple hash function for file content but changed to store content directly for simplicity
        // unsigned int h = 0;

        // for(char c : file.second)
        //     h = h * 31 + c;
    // snapshot[file.first] = to_string(h);
        
        snapshot[file.first] = file.second; // copy content directly
    }

    // Create new commit
    Commit* newCommit = new Commit(++commitCounter, message, snapshot); 
    allCommits[newCommit->id] = newCommit; // add to all commits map for easy lookup

    undoStack.push(newCommit); // push new commit to undo stack for potential future undos

    if(!root){

        root = newCommit;
        head = newCommit;
    }
    else{

        newCommit->parent1 = head; // set primary parent to current HEAD for linear history
        head = newCommit; // move HEAD to new commit
    }

    cout<< "Commit #" << newCommit->id
        << " created: "<< message << endl;

    // Clear working directory after commit - files are now in commit snapshot
    workingDir.clear();
}

// Function 3: Show Current Files
string Repository::showCurrentFiles() {

    if(!head)
        return "No commits yet.\n";

    if(head->files.empty())
        return "No files in last commit.\n";

    string result;

    for(auto &f : head->files)
        result += f.first + " -> " + f.second + "\n"; // show content directly

    return result;
}

// Function 4: show History
string Repository::showHistory() {

    if(!head) return "No commits\n";

    string r; //result string to accumulate history
    Commit* t = head; 

    while(t) {
        r += "Commit #" + to_string(t->id)
           + ": " + t->message + "\n";
        t = t->parent1; // follow primary parent for history
    }
    return r;
}

// Function 5: Undo
void Repository::undo() {

    if(undoStack.empty()) {
        cout << "Nothing to undo.\n";
        return;
    }

    // Move current commit to redo stack
    Commit* current = undoStack.top(); // get current commit to undo
    undoStack.pop(); // move back to previous commit
    redoStack.push(current); // move current commit to redo stack for potential future redo

    head = current->parent1;

    if(currentBranch)
        currentBranch->head = head; // Update branch pointer
    
    cout << "Undo successful.\n";
}

// Function 6: redo
void Repository::redo() {

    if(redoStack.empty()){
        cout << "Nothing to redo.\n";
        return;
    }

    Commit* commit = redoStack.top(); // get commit to redo
    redoStack.pop(); // move back to undo stack for potential future undos

    undoStack.push(commit); // move back to undo stack
    head = commit; // update HEAD to redo commit

    if(currentBranch)
        currentBranch->head = head;

    cout << "Redo successful.\n";
}

// Function 7: Create Branch
void Repository::createBranch(string name){

    if(!head) {
        cout<< "No commits yet. Cannot create branch.\n";
        return;
    }

    Branch* newBranch = new Branch(name, head);
    
    // Insert at beginning of branch list
    newBranch->next = branches;
    branches = newBranch;

    if(!currentBranch)
        currentBranch = newBranch;

    cout << "Branch '" << name <<"' created.\n";
}

// Function 8: Switch branch
void Repository::switchBranch(string name){
    Branch* temp = branches;

    while(temp){
        if(temp->name == name){ // found branch
            currentBranch = temp; // update current branch pointer
            head = temp->head;

            cout<< "Switched to branch '"<< name << "' \n";
            return;
        }

        temp = temp->next; // move to next branch
    }

    cout<< "Branch not found.\n";
}

// Function 9: Show Branches
string Repository::showBranches() {

    if(!branches) return "No branches\n";

    string r; // Mark current branch with *
    Branch* t = branches; // was temp but changed to t to avoid confusion with temp in switchBranch

    while(t) {
        if(t == currentBranch) r += "* ";
        r += t->name + "\n"; // was t->name + "\n";
        t = t->next; // move to next branch
    }
    return r;
}

// Function 10: Implement findCommit
Commit* Repository::findCommit(int id){

    Commit* temp = head;

    while(temp) {

        if(temp->id == id)
            return temp;
        
            temp = temp->parent1; // follow primary parent to search history
    }

    if(allCommits.count(id))
        return allCommits[id]; // check in all commits map for faster access (handles non-linear history)

    return nullptr;
}

// Function 11: Implement revertTo
void Repository::revertTo(int commitID) {

    Commit* target = findCommit(commitID); // find target commit in history or all commits map

    if(!target) {
        cout << "Commit not found.\n";
        return;
    }

    // Move HEAD
    head = target;

    // Update current branch pointer
    if(currentBranch)
        currentBranch->head = target;
    
    // Restore files
    restoreWorkingDirectory(target); // restore working directory to match target commit snapshot
    
    cout << "Reverted to commit #" << commitID << endl;
}

// Function 12: Restore working directory
void Repository::restoreWorkingDirectory(Commit* commit){
    if(!commit) return;

    // Clear current files
    workingDir.clear();

    // Load snapshot from commit
    for(auto &file : commit->files) {
        workingDir[file.first] = file.second; // restore content directly
    }

    cout << "Working directory restored to commit #"
         << commit->id << endl; // was commit->id << endl;
}

// Function 13: merge Branch
void Repository::mergeBranch(string name){
    if(!currentBranch){
        cout << "No active branch.\n";
        return;
    }

    // Find target branch
    Branch* temp = branches;

    while(temp){
        if(temp->name == name){
            if(temp == currentBranch){
                cout << "Cannot merge branch into itself.\n";
                return;
            }

            if(!temp->head){
                cout << "Target branch has no commits.\n";
                return;
            }

            // was not alowing to merge so deleted
            // detect up to date
            // if(isAncestor(temp->head, head)){
            //     cout << "Already up to date.\n";
            //     return;
            // }

            // Create merged snapshot with simple conflict resolution (keep current branch version)
            unordered_map<string, string> snapshot; // start with current branch files

            if(head)
                snapshot = head->files;

            // Merge files from target branch
            for(auto &f : temp->head->files) {

                if(snapshot.count(f.first) && snapshot[f.first] != f.second) {
                    cout << "Conflict detected in file: "
                         << f.first << endl;
                    // Keep current branch version (simple policy)
                }
                else 
                    snapshot[f.first] = f.second;
            }

            // ===== Create merge commit =====
            Commit* mergeCommit = new Commit(++commitCounter, "Merge branch '" + name + "'" , snapshot);

            // Two parents (DAG)
            mergeCommit->parent1 = head; // current branch head
            mergeCommit->parent2 = temp->head; // merged branch head

            allCommits[mergeCommit->id] = mergeCommit; // add to all commits map

            // Update HEAD and branch
            head = mergeCommit;
            currentBranch->head = head;

            // Restore merged files to working directory
            restoreWorkingDirectory(head);

            cout << "Merged branch '" << name
                 << "' into '" << currentBranch->name
                 << "'\n";
            
            return;
        }

        temp = temp->next; // move to next branch
    }

    cout << "Branch not found.\n";
}

