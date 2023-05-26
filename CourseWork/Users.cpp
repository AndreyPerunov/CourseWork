#include "Users.h"

Users::Users(std::string path) {
	Users::path = path;

	std::string filename = "user.bin";
	std::ifstream usersFileRead(path + filename, std::ios::binary);

	if (usersFileRead.is_open()) {
		// If file already exists read data in vector
		User user;
		while (usersFileRead.peek() != EOF) {
            usersFileRead.read((char*)&user.id, sizeof(user.id));
            usersFileRead.read(user.username, sizeof(user.username));
            usersFileRead.read(user.password, sizeof(user.password));
            usersFileRead.read(user.email, sizeof(user.email));
			Users::users.push_back(user);
		}
        if (!Users::users.empty()) {
            Users::lastId = Users::users.back().id;
        }
	}
	else {
		// Else create a file
		std::ofstream usersFileWrite(path + filename, std::ios::binary);
		if (!usersFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		usersFileWrite.close();
	}
}

bool Users::usernameExists(std::string username) {
    for (User user : Users::users) {
        if (user.username == username) return true;
    }
    return false;
}

bool Users::emailExists(std::string email) {
    for (User user : Users::users) {
        if (user.email == email) return true;
    }
    return false;
}

int Users::getId() {
    std::string id;
    std::regex pattern("[0-9]+");
    while (true) {
        std::cout << "Enter " << colored("id", "blue") << ": ";
        std::getline(std::cin, id);
        if (!std::regex_match(id, pattern)) {
            std::cout << colored("ID contains only numbers.", "red") << '\n';
        }
        else {
            break;
        }
    }
    return stoi(id);
}

char* Users::getValidUsername() {
    std::string username;
    std::regex pattern("[a-zA-Z0-9]+");

    while (true) {
        std::cout << "Enter " << colored("username", "blue") << ": ";
        std::getline(std::cin, username);
        if (!std::regex_match(username, pattern)) {
            std::cout << colored("Username can contain only english letters and number.", "red") << '\n';
        }
        else if (username.length() > 20) {
            std::cout << colored("Username can't exceed 20 characters.", "red") << '\n';
        }
        else if (username.length() < 2) {
            std::cout << colored("Username must be at least 2 characters long.", "red") << '\n';
        }
        else if (Users::usernameExists(username)) {
            std::cout << colored("Username already exists.", "red") << '\n';
        }
        else {
            return stoc(username);
        }
    }
}

char* Users::getUsername() {
    std::string username;
    std::regex pattern("[a-zA-Z0-9]+");

    while (true) {
        std::cout << "Enter " << colored("username", "blue") << ": ";
        std::getline(std::cin, username);
        if (!std::regex_match(username, pattern)) {
            std::cout << colored("Username can contain only english letters and number.", "red") << '\n';
        }
        else if (username.length() > 20) {
            std::cout << colored("Username can't exceed 20 characters.", "red") << '\n';
        }
        else if (username.length() < 2) {
            std::cout << colored("Username must be at least 2 characters long.", "red") << '\n';
        }
        else {
            return stoc(username);
        }
    }
}

char* Users::getPassword() {
    std::string password;
    std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+= '\\',\"{}|><']+");

    while (true) {
        std::cout << "Enter " << colored("password", "blue") << ": ";
        std::getline(std::cin, password);
        if (!std::regex_match(password, pattern)) {
            std::cout << colored("Password can contain only english letters, numbers and special characters.", "red") << '\n';
        }
        else if (password.length() > 50) {
            std::cout << colored("Password can't exceed 50 characters.", "red") << '\n';
        }
        else if (password.length() < 7) {
            std::cout << colored("Password must be at least 7 characters long.", "red") << '\n';
        }
        else {
            return stoc(password);
        }
    }
}

char* Users::getValidEmail() {
    std::string email;
    std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    while (true) {
        std::cout << "Enter " << colored("email", "blue") << ": ";
        std::getline(std::cin, email);
        if (!std::regex_match(email, pattern)) {
            std::cout << colored("Invalid email.", "red") << '\n';
        }
        else if (email.length() > 30) {
            std::cout << colored("Email can't exceed 30 characters.", "red") << '\n';
        }
        else if (email.length() < 5) {
            std::cout << colored("Email must be at least 5 characters long.", "red") << '\n';
        }
        else if (Users::emailExists(email)) {
            std::cout << colored("Email already exists.", "red") << '\n';
        }
        else {
            return stoc(email);
        }
    }
}

char* Users::getEmail() {
    std::string email;
    std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    while (true) {
        std::cout << "Enter " << colored("email", "blue") << ": ";
        std::getline(std::cin, email);
        if (!std::regex_match(email, pattern)) {
            std::cout << colored("Invalid email.", "red") << '\n';
        }
        else if (email.length() > 30) {
            std::cout << colored("Email can't exceed 30 characters.", "red") << '\n';
        }
        else if (email.length() < 5) {
            std::cout << colored("Email must be at least 5 characters long.", "red") << '\n';
        }
        else {
            return stoc(email);
        }
    }
}

bool Users::idExists(int id) {
    for (User user : Users::users) {
        if (user.id == id) return true;
    }
    return false;
}

std::string Users::getUsernameById(int id) {
    for (User user : Users::users) {
        if (user.id == id) return user.username;
    }
    return colored("User not found!", "red");
}

// Create
std::string Users::create() {
    char* username = Users::getValidUsername();
    char* password = Users::getPassword();
    char* email = Users::getValidEmail();

    Users::lastId++;
    User newUser;
    newUser.id = Users::lastId;
    strncpy_s(newUser.username, sizeof(newUser.username), username, _TRUNCATE);
    strncpy_s(newUser.password, sizeof(newUser.password), password, _TRUNCATE);
    strncpy_s(newUser.email, sizeof(newUser.email), email, _TRUNCATE);
    Users::users.push_back(newUser);
    Users::save();

    return colored((newUser.username), "green") + colored(" has been created.", "green");;
}

// Read One
std::string Users::readOneById() {
    Posts posts(Users::path);
    Follows follows(Users::path);

    int id = Users::getId();
    for (User user : Users::users) {
        if (user.id == id) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr
                << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::readOneByUsername() {
    Posts posts(Users::path);
    Follows follows(Users::path);

    std::string username = Users::getUsername();
    for (User user : Users::users) {
        if (user.username == username) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr
                << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::readOneByEmail() {
    Posts posts(Users::path);
    Follows follows(Users::path);

    std::string email = Users::getEmail();
    for (User user : Users::users) {
        if (user.email == email) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr
                << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

// Read All
std::string Users::readAllById(){
    Posts posts(Users::path);
    Follows follows(Users::path);

    fort::char_table table;

    // Set Header
    table << fort::header
        << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr;

    // Set Content
    for (User user : Users::users) {
        table << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;
    }

    return table.to_string();
}

std::string Users::readAllByUsername() {
    Posts posts(Users::path);
    Follows follows(Users::path);

    std::vector<User> copyUsers = Users::users;

    // Sort
    std::sort(copyUsers.begin(), copyUsers.end(), [](User a, User b) {
        return strcmp(a.username, b.username) < 0;
    });

    // Create a table
    fort::char_table table;

    // Set Header
    table << fort::header
        << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr;

    // Set Content
    for (User user : copyUsers) {
        table << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;
    }

    return table.to_string();
}

std::string Users::readAllByEmail() {
    Posts posts(Users::path);
    Follows follows(Users::path);

    std::vector<User> copyUsers = Users::users;

    // Sort
    std::sort(copyUsers.begin(), copyUsers.end(), [](User a, User b) {
        return strcmp(a.email, b.email) < 0;
        });

    // Create a table
    fort::char_table table;

    // Set Header
    table << fort::header
        << "ID" << "Username" << "Password" << "Email" << "Posts" << "Followers" << "Following" << fort::endr;

    // Set Content
    for (User user : copyUsers) {
        table << user.id << user.username << user.password << user.email << posts.getPostsCount(user.id) << follows.getFollowersCount(user.id) << follows.getFollowingCount(user.id) << fort::endr;
    }

    return table.to_string();
}

// Update
std::string Users::updateById() {
    std::cout << Users::readAllById();
    int id = Users::getId();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (it->id == id) {
            std::string message = "";
            std::string answer;
            std::cout << "Whould you like to change the username? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldUsername = it->username;
                char* newUsername = getValidUsername();
                strncpy_s(it->username, sizeof(it->username), newUsername, _TRUNCATE);
                message += colored(std::string("Username ") + oldUsername + " has been changed to " + newUsername + ".\n", "green");
            }
            std::cout << "Whould you like to change the password? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldPassword = it->password;
                char* newPassword = getPassword();
                strncpy_s(it->password, sizeof(it->password), newPassword, _TRUNCATE);
                message += colored(std::string("Password ") + oldPassword + " has been changed to " + newPassword + ".\n", "green");
            }
            std::cout << "Whould you like to change the email? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldEmail = it->email;
                char* newEmail = getValidEmail();
                strncpy_s(it->email, sizeof(it->email), newEmail, _TRUNCATE);
                message += colored(std::string("Email ") + oldEmail + " has been changed to " + newEmail + ".\n", "green");
            }

            if (message == "") {
                return colored("Nothing was changed.", "green");
            }
            else {
                Users::save();
                return message;
            }
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::updateByUsername() {
    std::cout << Users::readAllByUsername();
    char* username = Users::getUsername();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (strcmp(it->username, username) == 0) {
            std::string message = "";
            std::string answer;
            std::cout << "Whould you like to change the username? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldUsername = it->username;
                char* newUsername = getValidUsername();
                strncpy_s(it->username, sizeof(it->username), newUsername, _TRUNCATE);
                message += colored(std::string("Username ") + oldUsername + " has been changed to " + newUsername + ".\n", "green");
            }
            std::cout << "Whould you like to change the password? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldPassword = it->password;
                char* newPassword = getPassword();
                strncpy_s(it->password, sizeof(it->password), newPassword, _TRUNCATE);
                message += colored(std::string("Password ") + oldPassword + " has been changed to " + newPassword + ".\n", "green");
            }
            std::cout << "Whould you like to change the email? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldEmail = it->email;
                char* newEmail = getValidEmail();
                strncpy_s(it->email, sizeof(it->email), newEmail, _TRUNCATE);
                message += colored(std::string("Email ") + oldEmail + " has been changed to " + newEmail + ".\n", "green");
            }

            if (message == "") {
                return colored("Nothing was changed.", "green");
            }
            else {
                Users::save();
                return message;
            }
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::updateByEmail() {
    std::cout << Users::readAllByEmail();
    char* email = Users::getEmail();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (strcmp(it->email, email) == 0) {
            std::string message = "";
            std::string answer;
            std::cout << "Whould you like to change the username? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldUsername = it->username;
                char* newUsername = getValidUsername();
                strncpy_s(it->username, sizeof(it->username), newUsername, _TRUNCATE);
                message += colored(std::string("Username ") + oldUsername + " has been changed to " + newUsername + ".\n", "green");
            }
            std::cout << "Whould you like to change the password? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldPassword = it->password;
                char* newPassword = getPassword();
                strncpy_s(it->password, sizeof(it->password), newPassword, _TRUNCATE);
                message += colored(std::string("Password ") + oldPassword + " has been changed to " + newPassword + ".\n", "green");
            }
            std::cout << "Whould you like to change the email? (y/n): ";
            std::getline(std::cin, answer);
            if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
                std::string oldEmail = it->email;
                char* newEmail = getValidEmail();
                strncpy_s(it->email, sizeof(it->email), newEmail, _TRUNCATE);
                message += colored(std::string("Email ") + oldEmail + " has been changed to " + newEmail + ".\n", "green");
            }

            if (message == "") {
                return colored("Nothing was changed.", "green");
            }
            else {
                Users::save();
                return message;
            }
        }
    }

    return colored("User does not exist.", "red");
}

// Delete
//TODO: messages
std::string Users::deleteById() {
    Posts posts(Users::path);
    PostsLikes postsLikes(Users::path);
    Follows follows(Users::path);

    std::cout << Users::readAllById();
    int id = Users::getId();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (it->id == id) {
            std::string username = it->username;
            Users::users.erase(it);
            Users::save();
            return colored(std::string("User ") + username + " has been deleted.\n", "green")
                + posts.deleteAllByAythorId(id)
                + postsLikes.deleteAllByUserId(id)
                + follows.deleteAllByFollowerId(id)
                + follows.deleteAllByFollowingId(id);
        }
    }

    return colored("User does not exist.", "red");
}

//TODO: messages
std::string Users::deleteByUsername(){
    Posts posts(Users::path);
    PostsLikes postsLikes(Users::path);
    Follows follows(Users::path);

    std::cout << Users::readAllByUsername();
    char* username = Users::getUsername();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (strcmp(it->username, username) == 0) {
            int id = it->id;
            Users::users.erase(it);
            Users::save();
            return colored(std::string("User ") + username + " has been deleted.\n", "green")
                + posts.deleteAllByAythorId(id)
                + postsLikes.deleteAllByUserId(id)
                + follows.deleteAllByFollowerId(id)
                + follows.deleteAllByFollowingId(id);
        }
    }

    return colored("User does not exist.", "red");
}

//TODO: messages
std::string Users::deleteByEmail(){
    Posts posts(Users::path);
    PostsLikes postsLikes(Users::path);
    Follows follows(Users::path);

    std::cout << Users::readAllByEmail();
    char* email = Users::getEmail();
    for (auto it = Users::users.begin(); it != Users::users.end(); ++it) {
        if (strcmp(it->email, email) == 0) {
            int id = it->id;
            std::string username = it->username;
            Users::users.erase(it);
            Users::save();
            return colored(std::string("User ") + username + " has been deleted.\n", "green")
                + posts.deleteAllByAythorId(id)
                + postsLikes.deleteAllByUserId(id)
                + follows.deleteAllByFollowerId(id)
                + follows.deleteAllByFollowingId(id);
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::save() {
    std::string filename = "user.bin";
    std::ofstream usersFile(Users::path + filename, std::ios::binary);

    if (!usersFile.is_open()) {
        return colored("Error opening file " + filename + "!", "red");
    }

    for (User user : Users::users) {
        usersFile.write((char*)&user.id, sizeof(user.id));
        usersFile.write(user.username, sizeof(user.username));
        usersFile.write(user.password, sizeof(user.password));
        usersFile.write(user.email, sizeof(user.email));
    }

    usersFile.close();

    return colored("Users were saved successfully.", "green");
}