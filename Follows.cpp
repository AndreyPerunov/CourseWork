#include "Follows.h"

Follows::Follows(std::string path) {
	Follows::path = path;
	Follows::readData();
}

void Follows::readData() {
	std::string filename = "follows.bin";
	std::ifstream followsFileRead(Follows::path + filename, std::ios::binary);

	if (followsFileRead.is_open()) {
		// If file already exists read data in vector
		Follows::follows.clear();
		Follow follow;
		while (followsFileRead.peek() != EOF) {
			followsFileRead.read((char*)&follow.id, sizeof(follow.id));
			followsFileRead.read((char*)&follow.followerId, sizeof(follow.followerId));
			followsFileRead.read((char*)&follow.followingId, sizeof(follow.followingId));
			Follows::follows.push_back(follow);
		}
		if (!Follows::follows.empty()) {
			Follows::lastId = Follows::follows.back().id;
		}
	}
	else {
		// Else create a file
		std::ofstream followsFileWrite(Follows::path + filename, std::ios::binary);
		if (!followsFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		followsFileWrite.close();
	}
}

std::string Follows::save() {
	std::string filename = "follows.bin";
	std::ofstream followsFile(Follows::path + filename, std::ios::binary);

	if (!followsFile.is_open()) {
		return colored("Error opening file " + filename + "!", "red");
	}

	for (Follow follow : Follows::follows) {
		followsFile.write((char*)&follow.id, sizeof(follow.id));
		followsFile.write((char*)&follow.followerId, sizeof(follow.followerId));
		followsFile.write((char*)&follow.followingId, sizeof(follow.followingId));
	}

	followsFile.close();

	return colored("Follow were saved successfully.", "green");
}

int Follows::getUserId(std::string whatToGet) {
	Users users(Follows::path);
	std::cout << users.readAllById();
	std::string id;
	std::regex pattern("[0-9]+");
	while (true) {
		std::cout << "Enter " << colored(whatToGet, "blue") << ": ";
		std::getline(std::cin, id);
		if (!std::regex_match(id, pattern)) {
			std::cout << colored("ID contains only numbers.", "red") << '\n';
		}
		else if (!users.idExists(stoi(id))) {
			std::cout << colored("User with id " + id + " does not exists.", "red") << '\n';
		}
		else {
			break;
		}
	}
	return stoi(id);
}

int Follows::getId() {
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

bool Follows::followed(int followerId, int followingId) {
	for (Follow follow : Follows::follows) {
		if (follow.followerId == followerId && follow.followingId == followingId) {
			return true;
		}
	}
	return false;
}

int Follows::getFollowersCount(int userId) {
	int count = 0;
	for (Follow follow : Follows::follows) {
		if (follow.followingId == userId) {
			++count;
		}
	}
	return count;
}

int Follows::getFollowingCount(int userId) {
	int count = 0;
	for (Follow follow : Follows::follows) {
		if (follow.followerId == userId) {
			++count;
		}
	}
	return count;
}

// Create
std::string Follows::create() {
	int followerId = Follows::getUserId("follower id");
	int followingId = Follows::getUserId("following id");

	if (Follows::followed(followerId, followingId)) {
		return colored("User " + std::to_string(followerId) + " already following user " + std::to_string(followingId) + ".", "red");
	}
	if (followerId == followingId) {
		return colored("User can't follow himself.", "red");
	}

	Follows::lastId++;
	Follow newFollows;
	newFollows.id = Follows::lastId;
	newFollows.followerId = followerId;
	newFollows.followingId = followingId;
	Follows::follows.push_back(newFollows);
	Follows::save();

	return colored("Follow " + std::to_string(newFollows.id) + " has been created.", "green");
}

// Read One
std::string Follows::readOneById() {
	Users users(Follows::path);

	int id = Follows::getId();
	for (Follow follow : Follows::follows) {
		if (follow.id == id) {
			fort::char_table table;

			table << fort::header
				<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr
				<< follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;

			table.row(0).set_cell_bg_color(fort::color::yellow);

			return table.to_string();
		}
	}

	return colored("Follow does not exist.", "red");
}

// Read All
std::string Follows::readAllById() {
	Users users(Follows::path);

	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr;

	// Set Content
	for (Follow follow : Follows::follows) {
		table << follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::yellow);

	return table.to_string();
}

std::string Follows::readAllByFollowerId() {
	Users users(Follows::path);

	std::vector<Follow> copyFollows = Follows::follows;

	// Sort
	std::sort(copyFollows.begin(), copyFollows.end(), [](Follow a, Follow b) {
		return a.followerId < b.followerId;
	});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr;

	// Set Content
	for (Follow follow : copyFollows) {
		table << follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::yellow);

	return table.to_string();
}

std::string Follows::readAllByFollowingId() {
	Users users(Follows::path);

	std::vector<Follow> copyFollows = Follows::follows;

	// Sort
	std::sort(copyFollows.begin(), copyFollows.end(), [](Follow a, Follow b) {
		return a.followingId < b.followingId;
		});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr;

	// Set Content
	for (Follow follow : copyFollows) {
		table << follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::yellow);

	return table.to_string();
}

// Filter
std::string Follows::filterByFollowerId() {
	Users users(Follows::path);

	int followerId = getUserId("follower id");

	std::vector<Follow> filteredFollows;

	for (Follow follow : Follows::follows) {
		if (follow.followerId == followerId) {
			filteredFollows.push_back(follow);
		}
	}

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr;

	// Set Content
	for (Follow follow : filteredFollows) {
		table << follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::yellow);

	return table.to_string();
}

std::string Follows::filterByFollowingId() {
	Users users(Follows::path);

	int followingId = getUserId("following id");

	std::vector<Follow> filteredFollows;

	for (Follow follow : Follows::follows) {
		if (follow.followingId == followingId) {
			filteredFollows.push_back(follow);
		}
	}

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Follower Id" << "Follower" << "Following Id" << "Following" << fort::endr;

	// Set Content
	for (Follow follow : filteredFollows) {
		table << follow.id << follow.followerId << users.getUsernameById(follow.followerId) << follow.followingId << users.getUsernameById(follow.followingId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::yellow);

	return table.to_string();
}

// Delete One
std::string Follows::deleteOneById() {
	std::cout << Follows::readAllById();
	int id = Follows::getId();
	for (auto it = Follows::follows.begin(); it != Follows::follows.end(); ++it) {
		if (it->id == id) {
			Follows::follows.erase(it);
			Follows::save();
			return colored("Follow with id " + std::to_string(id) + " has been deleted.", "green");
		}
	}

	return colored("Follow does not exist.", "red");
}

// Delete All
std::string Follows::deleteAllByFollowerId() {
	std::cout << Follows::readAllByFollowerId();
	int followerId = Follows::getUserId("follower id");
	std::string message = "";

	std::vector<Follow>::iterator it = Follows::follows.begin();
	while (it != Follows::follows.end()) {
		if (it->followerId == followerId) {
			int id = it->id;
			it = Follows::follows.erase(it);
			message += colored("Follow " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user is not following anyone.", "red");
	}

	Follows::save();

	return message;
}

std::string Follows::deleteAllByFollowerId(int userId) {
	std::string message = "";

	std::vector<Follow>::iterator it = Follows::follows.begin();
	while (it != Follows::follows.end()) {
		if (it->followerId == userId) {
			int id = it->id;
			it = Follows::follows.erase(it);
			message += colored("Follow " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user is not following anyone.\n", "red");
	}

	Follows::save();

	return message;
}

std::string Follows::deleteAllByFollowingId() {
	std::cout << Follows::readAllByFollowingId();
	int followingId = Follows::getUserId("following id");
	std::string message = "";

	std::vector<Follow>::iterator it = Follows::follows.begin();
	while (it != Follows::follows.end()) {
		if (it->followingId == followingId) {
			int id = it->id;
			it = Follows::follows.erase(it);
			message += colored("Follow " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user does not have any followers.", "red");
	}

	Follows::save();

	return message;
}

std::string Follows::deleteAllByFollowingId(int userId) {
	std::string message = "";

	std::vector<Follow>::iterator it = Follows::follows.begin();
	while (it != Follows::follows.end()) {
		if (it->followingId == userId) {
			int id = it->id;
			it = Follows::follows.erase(it);
			message += colored("Follow " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user does not have any followers.\n", "red");
	}

	Follows::save();

	return message;
}

std::string Follows::getNumberOfFollows(){
	std::string output = "There is " + colored(std::to_string(Follows::follows.size()), "blue");

    if (Follows::follows.size() == 1) {
        output += " follow.";
    } else {
        output += " follows.";
    }
	
	return output;
}