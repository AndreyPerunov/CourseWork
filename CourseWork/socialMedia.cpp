#include "socialMedia.h"

SocialMedia::SocialMedia() {
    std::cout << "How wouold you like to call your social media database? ";
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
    }

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