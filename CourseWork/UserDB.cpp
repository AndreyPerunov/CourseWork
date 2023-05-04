#include "UserDB.h"

UserDB::UserDB(std::string path) {
	UserDB::path = path;
}

void UserDB::add(std::string username, std::string password) {
	/*std::string filename = "user.bin";
	std::ofstream usersFile(UserDB::path + filename, std::ios::binary);
	
	UserDB::users.push_back({UserDB::lastId++,username, password, "mail"});

	if (!usersFile.is_open()) {
		std::cout << "Error opening file " << filename << "!" << '\n';
		return;
	}
		
	usersFile.close();*/
}

