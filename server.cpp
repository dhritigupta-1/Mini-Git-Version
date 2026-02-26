#include "crow_all.h"
#include "Repository.h"
#include <fstream>
#include <sstream>

Repository repo;

int main() {

    crow::SimpleApp app;

    // Serve HTML
    CROW_ROUTE(app,"/")
    ([](){
        std::ifstream file("index.html");
        std::ostringstream buf;
        buf << file.rdbuf();
        return buf.str();
    });

    // Add file
    CROW_ROUTE(app,"/add")
    ([](const crow::request& req){
        repo.addFile(
            req.url_params.get("name"),
            req.url_params.get("content"));
        return "File added";
    });

    // Commit
    CROW_ROUTE(app,"/commit")
    ([](const crow::request& req){
        repo.commit(req.url_params.get("msg"));
        return "Committed";
    });

    // Undo
    CROW_ROUTE(app,"/undo")([](){
        repo.undo(); return "Undo";
    });

    // Redo
    CROW_ROUTE(app,"/redo")([](){
        repo.redo(); return "Redo";
    });

    // Create branch
    CROW_ROUTE(app,"/createBranch")
    ([](const crow::request& req){
        repo.createBranch(req.url_params.get("name"));
        return "Branch created";
    });

    // Switch branch
    CROW_ROUTE(app,"/switchBranch")
    ([](const crow::request& req){
        repo.switchBranch(req.url_params.get("name"));
        return "Branch switched";
    });

    // Merge branch
    CROW_ROUTE(app,"/merge")
    ([](const crow::request& req){
        repo.mergeBranch(req.url_params.get("name"));
        return "Merged";
    });

    // Revert to commit
    CROW_ROUTE(app,"/revert")
    ([](const crow::request& req){
        repo.revertTo(stoi(req.url_params.get("id")));
        return "Reverted";
    });

    // Show history
    CROW_ROUTE(app,"/history")
    ([](){ return repo.showHistory(); });

    // Show current files
    CROW_ROUTE(app,"/files")
    ([](){ return repo.showCurrentFiles(); });

    // Show branches
    CROW_ROUTE(app,"/branches")
    ([](){ return repo.showBranches(); });

    app.bindaddr("127.0.0.1").port(18080).run();
}

   
