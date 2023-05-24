#include "SocialMedia.h"
namespace fs = std::filesystem;

Menu* SocialMedia::buildMenu() {
    Menu* root = new Menu("Home");

    // CREATE
    Menu* createDB = root->addChild("Create DB");

    // SELECT
    Menu* selectDB = root->addChild("Select DB");
    for (auto entry : fs::directory_iterator("./")) {
        if (fs::is_directory(entry.status()) && entry.path() != "./x64") {
            selectDB->addChild(entry.path().filename().string());
        }
    }
    selectDB->addGoBack("Go back");

    // DELETE
    Menu* deleteDB = root->addChild("Delete DB");
    for (auto entry : fs::directory_iterator("./")) {
        if (fs::is_directory(entry.status()) && entry.path() != "./x64") {
            deleteDB->addChild(entry.path().filename().string());
        }
    }
    deleteDB->addGoBack("Go back");

    // QUIT
    root->addChild("Quit");

    return root;
}

Menu* SocialMedia::buildDBMenu(std::string title) {
    Menu* root = new Menu(title);
 
    Menu* users = root->addChild("Users");
    users->addChild("create");
    Menu* readOneUser = users->addChild("readOne");
    readOneUser->addChild("by id");
    readOneUser->addChild("by username");
    readOneUser->addChild("by email");
    Menu* readAllUsers = users->addChild("readAll");
    readAllUsers->addChild("by id");
    readAllUsers->addChild("by username");
    readAllUsers->addChild("by email");
    Menu* updateUser = users->addChild("update");
    updateUser->addChild("by id");
    updateUser->addChild("by username");
    updateUser->addChild("by email");
    Menu* deleteOneUser = users->addChild("delete");
    deleteOneUser->addChild("by id");
    deleteOneUser->addChild("by username");
    deleteOneUser->addChild("by email");

    users->addGoBack("Go back");

    Menu* posts = root->addChild("Posts");
    posts->addChild("create");
    posts->addChild("readOne");
    Menu* readAllPosts = posts->addChild("readAll");
    readAllPosts->addChild("by id");
    readAllPosts->addChild("by title");
    readAllPosts->addChild("by body");
    readAllPosts->addChild("by author id");
    posts->addChild("readMany");
    posts->addChild("update");
    posts->addChild("delete");
    posts->addGoBack("Go back");

    Menu* postLikes = root->addChild("Post Likes");
    Menu* messages = root->addChild("Messages");
    Menu* follows = root->addChild("Follows");

     root->addChild("Home");

    return root;
}

void SocialMedia::editDB(std::string title) {
    try {
        Users users("./" + title + "/");
        Posts posts("./" + title + "/");

        std::string flashMessage = "";
        while (true) {
            std::string selectedOption = buildDBMenu(title)->navigate(flashMessage);
            std::cout << '\n' + colored(selectedOption, "green") + '\n';
            selectedOption = selectedOption.substr(title.length());

            ///////////////////////
            // USERS
            ///////////////////////
            // ".../Users/create"
            if (selectedOption == "/Users/create") {
                flashMessage = users.create();
            }
            
            // READ ONE
            // ".../Users/readOne/by id"
            if (selectedOption == "/Users/readOne/by id") {
                flashMessage = users.readOneById();
            }
            // ".../Users/readOne/by username"
            if (selectedOption == "/Users/readOne/by username") {
                flashMessage = users.readOneByUsername();
            }
            // ".../Users/readOne/by email"
            if (selectedOption == "/Users/readOne/by email") {
                flashMessage = users.readOneByEmail();
            }

            // READ ALL
            // ".../Users/readAll/by id"
            if (selectedOption == "/Users/readAll/by id") {
                flashMessage = users.readAllById();
            }
            // ".../Users/readAll/by username"
            if (selectedOption == "/Users/readAll/by username") {
                flashMessage = users.readAllByUsername();
            }
            // ".../Users/readAll/by email"
            if (selectedOption == "/Users/readAll/by email") {
                flashMessage = users.readAllByEmail();
            }

            // UPDATE
            // ".../Users/update/by id"
            if (selectedOption == "/Users/update/by id") {
                flashMessage = users.updateById();
            }
            // ".../Users/update/by username"
            if (selectedOption == "/Users/update/by username") {
                flashMessage = users.updateByUsername();
            }
            // ".../Users/update/by email"
            if (selectedOption == "/Users/update/by email") {
                flashMessage = users.updateByEmail();
            }

            // DELETE
            // ".../Users/delete/by id"
            if (selectedOption == "/Users/delete/by id") {
                flashMessage = users.deleteById();
            }
            // ".../Users/delete/by username"
            if (selectedOption == "/Users/delete/by username") {
                flashMessage = users.deleteByUsername();
            }
            // ".../Users/delete/by email"
            if (selectedOption == "/Users/delete/by email") {
                flashMessage = users.deleteByEmail();
            }

            ///////////////////////
            // POSTS
            ///////////////////////
            // ".../Posts/create"
            if (selectedOption == "/Posts/create") {
                flashMessage = posts.create();
            }

            // ".../Posts/readAll/by id"
            if (selectedOption == "/Posts/readAll/by id") {
                flashMessage = posts.readAllById();
            }



            // ".../Home"
            if (selectedOption == "/Home") break;
        }
    }
    catch (std::exception e) {
        std::cout << colored(e.what(), "red");
        return;
    }
}

SocialMedia::SocialMedia() {
    std::string flashMessage = "";
    while (true) {
        std::string selectedOption = buildMenu()->navigate(flashMessage);
        std::cout << '\n' + colored(selectedOption, "green") + '\n';

        // "Home/Create DB"
        if (selectedOption == "Home/Create DB") {
            std::string DBTitle = "undefined";
            std::cout << "Title: ";
            std::cin >> DBTitle;
            fs::path folderPath(DBTitle);
            try {
                if (!fs::create_directory(folderPath)) {
                    flashMessage = colored("Database '" + DBTitle + "' already exists.", "red");
                }
                else {
                    flashMessage = colored("Database '" + DBTitle + "' have been created.", "green");
                }
            }
            catch (fs::filesystem_error e) {
                flashMessage = colored("Error creating folder: " + std::string(e.what()), "red");
            }
        }

        // "Home/Select DB/"
        std::regex selectPattern("Home\\/Select DB\\/([\\w\\s()-]+)");
        std::smatch matchToSelect;
        if (std::regex_search(selectedOption, matchToSelect, selectPattern)) {
            if (fs::exists("./" + matchToSelect[1].str())) {
                editDB(matchToSelect[1]);
            }
            else {
                flashMessage = colored("Error selecting " + matchToSelect[1].str(), "red");
            }
        }

        // "Home/Delete DB/"
        std::regex deletePattern("Home\\/Delete DB\\/([\\w\\s]+)");
        std::smatch matchToDelete;
        if (std::regex_search(selectedOption, matchToDelete, deletePattern)) {
            if (SocialMedia::deleteSocialMedia(matchToDelete[1])) {
                flashMessage = colored("Database '" + matchToDelete[1].str() + "' have been deleted.", "green");
            }
            else {
                flashMessage = colored("Error deleting " + matchToDelete[1].str(), "red");
            }
        }
        
        // "Home/Quit"
        if (selectedOption == "Home/Quit") break;
    }
}

bool SocialMedia::deleteSocialMedia(std::string path) {
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            fs::remove_all(path);
            return true;
        }
        else {
            // The provided path does not exist or is not a directory.
            return false;
        }
    }
    catch (const fs::filesystem_error& e) {
        // Filesystem error
        return false;
    }
}