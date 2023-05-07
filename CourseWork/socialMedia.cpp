#include "socialMedia.h"

Menu* buildMenu() {
    Menu* root = new Menu("Home");

    // CREATE
    Menu* createDB = root->addChild("Create DB");

    // SELECT
    Menu* selectDB = root->addChild("Select DB");
    selectDB->addGoBack("Go back");

    // DELETE
    Menu* deleteDB = root->addChild("Delete DB");
    deleteDB->addGoBack("Go back");

    // QUIT
    root->addChild("Quit");

    return root;
}

std::string handleCreateDB() {
    std::string title = "undefined";
    std::cout << "Title: ";
    std::cin >> title;
    return title;
}

SocialMedia::SocialMedia() {
    std::string flashMessage = "";
    while (true)
    {
        std::string selectedOption = buildMenu()->navigate(flashMessage);
        std::cout << '\n' + colored(selectedOption, "green") + '\n';
        if (selectedOption == "Home/Create DB") {
            flashMessage = colored("Database " + handleCreateDB() + " have been created.", "green");
        }
        if (selectedOption == "Home/Quit") {
            break;
        }
    }

    /*std::cout << "How wouold you like to call your social media database? ";
    std::cin >> SocialMedia::path;

    std::filesystem::path folder_path(SocialMedia::path);

    try {
        if (!std::filesystem::create_directory(folder_path)) {
            std::cout << "Folder '" << folder_path << "' already exists.\n";
        }
        SocialMedia::path = SocialMedia::path + '/';
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating folder: " << e.what() << '\n';
    }*/

}

bool SocialMedia::deleteSocialMedia() {
    try {
        if (std::filesystem::exists(SocialMedia::path) && std::filesystem::is_directory(SocialMedia::path)) {
            std::filesystem::remove_all(SocialMedia::path);
            return true;
        }
        else {
            std::cerr << "The provided path does not exist or is not a directory." << std::endl;
            return false;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}

UserDB SocialMedia::user() {
    UserDB obj(path);
    return obj;
}