#include "Repository.h"
#include <iostream>

using namespace std;

int main() {
    Repository repo;

    repo.addFile("file1.txt", "Hello World");
    repo.addFile("file2.txt", "Min Git Project");

    repo.showCurrentFiles();

    repo.commit("Initial commit");

    repo.addFile("file3.txt", "New feature added");
    repo.commit("Second commit");

    repo.showHistory();

    repo.undo();
    repo.showHistory();

    repo.undo();
    repo.showHistory();

    repo.redo();
    repo.showHistory();

    repo.createBranch("main");
    repo.createBranch("dev");

    repo.showBranches();

    repo.switchBranch("dev");

    repo.addFile("feature.txt", "New dev feature");
    repo.commit("Dev commit");

    repo.showHistory();

    repo.revertTo(2);

    repo.showHistory();

    repo.showCurrentFiles();

    repo.revertTo(1);

    repo.showCurrentFiles();

    repo.switchBranch("main");
    repo.mergeBranch("dev");

    repo.showHistory();
    repo.showCurrentFiles();

    return 0;
}