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
    readAllUsers->addChild("sort by id");
    readAllUsers->addChild("sort by username");
    readAllUsers->addChild("sort by email");
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
    posts->addChild("readOne")->addChild("by id");
    Menu* readAllPosts = posts->addChild("readAll");
    readAllPosts->addChild("sort by id");
    readAllPosts->addChild("sort by title");
    readAllPosts->addChild("sort by body");
    readAllPosts->addChild("sort by author id");
    posts->addChild("update")->addChild("by id");
    posts->addChild("deleteOne")->addChild("by id");
    posts->addChild("deleteAll")->addChild("by author id");
    posts->addGoBack("Go back");

    Menu* postsLikes = root->addChild("Posts Likes");
    postsLikes->addChild("create");
    postsLikes->addChild("readOne")->addChild("by id");
    Menu* readAllPostsLikes = postsLikes->addChild("readAll");
    readAllPostsLikes->addChild("sort by id");
    readAllPostsLikes->addChild("sort by post id");
    readAllPostsLikes->addChild("sort by user id");
    postsLikes->addChild("update")->addChild("by id");
    postsLikes->addChild("deleteOne")->addChild("by id");
    Menu* deleteAllPostsLikes = postsLikes->addChild("deleteAll");
    deleteAllPostsLikes->addChild("by user id");
    deleteAllPostsLikes->addChild("by post id");
    postsLikes->addGoBack("Go back");

    Menu* messages = root->addChild("Messages");
    Menu* follows = root->addChild("Follows");

     root->addChild("Home");

    return root;
}

void SocialMedia::editDB(std::string title) {
    try {
        Users users("./" + title + "/");
        Posts posts("./" + title + "/");
        PostsLikes postsLikes("./" + title + "/");

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
            // ".../Users/readAll/sort by id"
            if (selectedOption == "/Users/readAll/sort by id") {
                flashMessage = users.readAllById();
            }
            // ".../Users/readAll/sort by username"
            if (selectedOption == "/Users/readAll/sort by username") {
                flashMessage = users.readAllByUsername();
            }
            // ".../Users/readAll/sort by email"
            if (selectedOption == "/Users/readAll/sort by email") {
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
                posts.readData();
                postsLikes.readData();
            }
            // ".../Users/delete/by username"
            if (selectedOption == "/Users/delete/by username") {
                flashMessage = users.deleteByUsername();
                posts.readData();
                postsLikes.readData();
            }
            // ".../Users/delete/by email"
            if (selectedOption == "/Users/delete/by email") {
                flashMessage = users.deleteByEmail();
                posts.readData();
                postsLikes.readData();
            }

            ///////////////////////
            // POSTS
            ///////////////////////
            // CREATE
            // ".../Posts/create"
            if (selectedOption == "/Posts/create") {
                flashMessage = posts.create();
            }

            // READ ONE
            // ".../Posts/readOne/by id"
            if (selectedOption == "/Posts/readOne/by id") {
                flashMessage = posts.readOneById();
            }

            // READ ALL
            // ".../Posts/readAll/sort by id"
            if (selectedOption == "/Posts/readAll/sort by id") {
                flashMessage = posts.readAllById();
            }
            // ".../Posts/readAll/sort by title"
            if (selectedOption == "/Posts/readAll/sort by title") {
                flashMessage = posts.readAllByTitle();
            }
            // ".../Posts/readAll/sort by body"
            if (selectedOption == "/Posts/readAll/sort by body") {
                flashMessage = posts.readAllByBody();
            }
            // ".../Posts/readAll/sort by author id"
            if (selectedOption == "/Posts/readAll/sort by author id") {
                flashMessage = posts.readAllByAuthorId();
            }

            // UPDATE
            // ".../Posts/update/by id"
            if (selectedOption == "/Posts/update/by id") {
                flashMessage = posts.updateById();
            }

            // DELETE ONE
            // ".../Posts/deleteOne/by id"
            if (selectedOption == "/Posts/deleteOne/by id") {
                flashMessage = posts.deleteOneById();
                postsLikes.readData();
            }

            // DELETE ALL
            // ".../Posts/deleteAll/by author id"
            if (selectedOption == "/Posts/deleteAll/by author id") {
                flashMessage = posts.deleteAllByAythorId();
                postsLikes.readData();
            }

            ///////////////////////
            // POSTS LIKES
            ///////////////////////
            // CREATE
            // ".../Posts Likes/create"
            if (selectedOption == "/Posts Likes/create") {
                flashMessage = postsLikes.create(); 
            }

            // READ ONE
            // ".../Posts Likes/readOne/by id"
            if (selectedOption == "/Posts Likes/readOne/by id") {
                flashMessage = postsLikes.readOneById();
            }

            // READ ALL
            // ".../Posts Likes/readAll/sort by id"
            if (selectedOption == "/Posts Likes/readAll/sort by id") {
                flashMessage = postsLikes.readAllById();
            }
            // ".../Posts Likes/readAll/sort by post id"
            if (selectedOption == "/Posts Likes/readAll/sort by post id") {
                flashMessage = postsLikes.readAllByPostId();
            }
            // ".../Posts Likes/readAll/sort by user id"
            if (selectedOption == "/Posts Likes/readAll/sort by user id") {
                flashMessage = postsLikes.readAllByUserId();
            }

            // UPDATE
            // ".../Posts Likes/update/by id"
            if (selectedOption == "/Posts Likes/update/by id") {
                flashMessage = postsLikes.updateById();
            }

            // DELETE ONE
            // ".../Posts Likes/deleteOne/by id"
            if (selectedOption == "/Posts Likes/deleteOne/by id") {
                flashMessage = postsLikes.deleteOneById();
            }

            // DELETE ALL
            // ".../Posts Likes/deleteAll/by post id"
            if (selectedOption == "/Posts Likes/deleteAll/by post id") {
                flashMessage = postsLikes.deleteAllByPostId();
            }
            // ".../Posts Likes/deleteAll/by user id"
            if (selectedOption == "/Posts Likes/deleteAll/by user id") {
                flashMessage = postsLikes.deleteAllByUserId();
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