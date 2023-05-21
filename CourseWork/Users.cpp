#include "Users.h"

char* Users::stoc(std::string string) {
    char* result = new char[string.length() + 1];
    strcpy_s(result, string.length() + 1, string.c_str());
    return result;
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
            return Users::stoc(username);
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
            return Users::stoc(username);
        }
    }
}

char* Users::getPassword() {
    std::string password;
    std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+=]+");

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
            return Users::stoc(password);
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
            return Users::stoc(email);
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
            return Users::stoc(email);
        }
    }
}


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
        Users::lastId = Users::users.back().id;
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

std::string Users::readOneById() {
    std::string idstring;
    std::regex pattern("[0-9]+");
    while (true) {
        std::cout << "Enter id: ";
        std::getline(std::cin, idstring);
        if (!std::regex_match(idstring, pattern)) {
            std::cout << colored("ID contains only numbers.", "red") << '\n';
        } else {
            break;
        }
    }
    int id = stoi(idstring);
    for (User user : Users::users) {
        if (user.id == id) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << fort::endr
                << user.id << user.username << user.password << user.email << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::readOneByUsername() {
    std::string username = Users::getUsername();
    for (User user : Users::users) {
        if (user.username == username) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << fort::endr
                << user.id << user.username << user.password << user.email << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::readOneByEmail() {
    std::string email = Users::getEmail();
    for (User user : Users::users) {
        if (user.email == email) {
            fort::char_table table;

            table << fort::header
                << "ID" << "Username" << "Password" << "Email" << fort::endr
                << user.id << user.username << user.password << user.email << fort::endr;

            return table.to_string();
        }
    }

    return colored("User does not exist.", "red");
}

std::string Users::readAll(){
    fort::char_table table;

    // Set Header
    table << fort::header
        << "ID" << "Username" << "Password" << "Email" << fort::endr;

    // Set Content
    for (User user : Users::users) {
        table << user.id << user.username << user.password << user.email << fort::endr;
    }

    return table.to_string();
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

User Users::create() {
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
    return newUser;
}

User::User() {

}