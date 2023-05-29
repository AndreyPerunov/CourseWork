#include "PostsLikes.h"

PostsLikes::PostsLikes(std::string path) {
	PostsLikes::path = path;
	PostsLikes::readData();
}

void PostsLikes::readData() {
	std::string filename = "postsLikes.bin";
	std::ifstream postsLikesFileRead(PostsLikes::path + filename, std::ios::binary);

	if (postsLikesFileRead.is_open()) {
		// If file already exists read data in vector
		PostsLikes::postsLikes.clear();
		PostLike postLike;
		while (postsLikesFileRead.peek() != EOF) {
			postsLikesFileRead.read((char*)&postLike.id, sizeof(postLike.id));
			postsLikesFileRead.read((char*)&postLike.postId, sizeof(postLike.postId));
			postsLikesFileRead.read((char*)&postLike.userId, sizeof(postLike.userId));
			PostsLikes::postsLikes.push_back(postLike);
		}
		if (!PostsLikes::postsLikes.empty()) {
			PostsLikes::lastId = PostsLikes::postsLikes.back().id;
		}
	}
	else {
		// Else create a file
		std::ofstream postsLikesFileWrite(PostsLikes::path + filename, std::ios::binary);
		if (!postsLikesFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		postsLikesFileWrite.close();
	}
}

std::string PostsLikes::save() {
	std::string filename = "postsLikes.bin";
	std::ofstream postsFile(PostsLikes::path + filename, std::ios::binary);

	if (!postsFile.is_open()) {
		return colored("Error opening file " + filename + "!", "red");
	}

	for (PostLike postLike : PostsLikes::postsLikes) {
		postsFile.write((char*)&postLike.id, sizeof(postLike.id));
		postsFile.write((char*)&postLike.postId, sizeof(postLike.postId));
		postsFile.write((char*)&postLike.userId, sizeof(postLike.userId));
	}

	postsFile.close();

	return colored("Posts likes were saved successfully.", "green");
}

int PostsLikes::getId() {
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

int PostsLikes::getPostId() {
	Posts posts(PostsLikes::path);
	std::cout << posts.readAllById();
	std::string id;
	std::regex pattern("[0-9]+");
	while (true) {
		std::cout << "Enter " << colored("post id", "blue") << ": ";
		std::getline(std::cin, id);
		if (!std::regex_match(id, pattern)) {
			std::cout << colored("ID contains only numbers.", "red") << '\n';
		}
		else if (!posts.idExists(stoi(id))) {
			std::cout << colored("Post with id " + id + " does not exists.", "red") << '\n';
		}
		else {
			break;
		}
	}
	return stoi(id);
}

int PostsLikes::getUserId() {
	Users users(PostsLikes::path);
	std::cout << users.readAllById();
	std::string id;
	std::regex pattern("[0-9]+");
	while (true) {
		std::cout << "Enter " << colored("user id", "blue") << ": ";
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

int PostsLikes::getLikesCount(int postId) {
	int count = 0;
	for (PostLike postLike : PostsLikes::postsLikes) {
		if (postLike.postId == postId) {
			++count;
		}
	}
	return count;
}

bool PostsLikes::liked(int postId, int userId) {
	for (PostLike postLike : PostsLikes::postsLikes) {
		if (postLike.postId == postId && postLike.userId == userId) {
			return true;
		}
	}
	return false;
}

// Create
std::string PostsLikes::create() {
	int postId = PostsLikes::getPostId();
	int userId = PostsLikes::getUserId();

	if (PostsLikes::liked(postId, userId)) {
		return colored("This user already liked this post.", "red");
	}

	PostsLikes::lastId++;
	PostLike newPostLike;
	newPostLike.id = PostsLikes::lastId;
	newPostLike.postId = postId;
	newPostLike.userId = userId;
	PostsLikes::postsLikes.push_back(newPostLike);
	PostsLikes::save();

	return colored("Post like with id ", "green") + colored(std::to_string(newPostLike.id), "green") + colored(" has been created.", "green");
}

// Read One
std::string PostsLikes::readOneById() {
	Users users(PostsLikes::path);
	Posts posts(PostsLikes::path);

	int id = PostsLikes::getId();
	for (PostLike postLike : PostsLikes::postsLikes) {
		if (postLike.id == id) {
			fort::char_table table;

			table << fort::header
				<< "ID" << "Post Id" << "Title" << "User Id" << "Username" << fort::endr
				<< postLike.id << postLike.postId << posts.getTitleById(postLike.postId) << postLike.userId << users.getUsernameById(postLike.userId) << fort::endr << fort::separator;

			table.row(0).set_cell_bg_color(fort::color::light_red);

			return table.to_string();
		}
	}

	return colored("Post does not exist.", "red");
}

// Read All
std::string PostsLikes::readAllById() {
	Users users(PostsLikes::path);
	Posts posts(PostsLikes::path);

	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Post ID" << "Title" << "User Id" << "Username" << fort::endr;

	// Set Content
	for (PostLike postLike : PostsLikes::postsLikes) {
		table << postLike.id << postLike.postId << posts.getTitleById(postLike.postId) << postLike.userId << users.getUsernameById(postLike.userId) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::light_red);

	return table.to_string();
}

std::string PostsLikes::readAllByPostId() {
	Users users(PostsLikes::path);
	Posts posts(PostsLikes::path);

	std::vector<PostLike> copyPostsLikes = PostsLikes::postsLikes;

	// Sort
	std::sort(copyPostsLikes.begin(), copyPostsLikes.end(), [](PostLike a, PostLike b) {
		return a.postId < b.postId;
	});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Post ID" << "Title" << "User Id" << "Username" << fort::endr;

	// Set Content
	for (PostLike postLike : copyPostsLikes) {
		table << postLike.id << postLike.postId << posts.getTitleById(postLike.postId) << postLike.userId << users.getUsernameById(postLike.userId) << fort::endr;
	}

	table.row(0).set_cell_bg_color(fort::color::light_red);

	return table.to_string();
}

std::string PostsLikes::readAllByUserId() {
	Users users(PostsLikes::path);
	Posts posts(PostsLikes::path);

	std::vector<PostLike> copyPostsLikes = PostsLikes::postsLikes;

	// Sort
	std::sort(copyPostsLikes.begin(), copyPostsLikes.end(), [](PostLike a, PostLike b) {
		return a.userId < b.userId;
		});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Post ID" << "Title" << "User Id" << "Username" << fort::endr;

	// Set Content
	for (PostLike postLike : copyPostsLikes) {
		table << postLike.id << postLike.postId << posts.getTitleById(postLike.postId) << postLike.userId << users.getUsernameById(postLike.userId) << fort::endr;
	}

	table.row(0).set_cell_bg_color(fort::color::light_red);
	
	return table.to_string();
}

// Update
std::string PostsLikes::updateById() {
	std::cout << PostsLikes::readAllById();
	int id = PostsLikes::getId();
	for (auto it = PostsLikes::postsLikes.begin(); it != PostsLikes::postsLikes.end(); ++it) {
		if (it->id == id) {
			std::string message = "";
			std::string answer;
			int newPostId = it->postId;
			int newUserId = it->userId;

			std::cout << "Whould you like to change the post id? (y - to change): ";
			std::getline(std::cin, answer);
			if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
				int oldPostId = it->postId;
				newPostId = getPostId();
				message += colored("Post id " + std::to_string(oldPostId) + " has been changed to " + std::to_string(newPostId) + ".\n", "green");
			}
			std::cout << "Whould you like to change the user id? (y - to change): ";
			std::getline(std::cin, answer);
			if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
				int oldUserId = it->userId;
				newUserId = getUserId();
				message += colored("User id " + std::to_string(oldUserId) + " has been changed to " + std::to_string(newUserId) + ".\n", "green");
			}

			if (message == "") {
				return colored("Nothing was changed.", "green");
			}
			else {
				if (PostsLikes::liked(newPostId, newUserId)) {
					return colored("This user already liked this post.", "red");
				}

				it->postId = newPostId;
				it->userId = newUserId;
				PostsLikes::save();
				return message;
			}
		}
	}

	return colored("Post like does not exist.", "red");
}

// Delete One
std::string PostsLikes::deleteOneById() {
	std::cout << PostsLikes::readAllById();
	int id = PostsLikes::getId();
	for (auto it = PostsLikes::postsLikes.begin(); it != PostsLikes::postsLikes.end(); ++it) {
		if (it->id == id) {
			PostsLikes::postsLikes.erase(it);
			PostsLikes::save();
			return colored("Post like with id " + std::to_string(id) + " has been deleted.", "green");
		}
	}

	return colored("Post like does not exist.", "red");
}

// Delete All
std::string PostsLikes::deleteAllByPostId() {
	std::cout << PostsLikes::readAllByPostId();
	int postId = PostsLikes::getPostId();
	std::string message = "";

	std::vector<PostLike>::iterator it = PostsLikes::postsLikes.begin();
	while (it != PostsLikes::postsLikes.end()) {
		if (it->postId == postId) {
			int id = it->id;
			it = PostsLikes::postsLikes.erase(it);
			message += colored("Post like " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This post has no likes", "red");
	}

	PostsLikes::save();

	return message;
}

std::string PostsLikes::deleteAllByPostId(int postId) {
	std::string message = "";

	std::vector<PostLike>::iterator it = PostsLikes::postsLikes.begin();
	while (it != PostsLikes::postsLikes.end()) {
		if (it->postId == postId) {
			int id = it->id;
			it = PostsLikes::postsLikes.erase(it);
			message += colored("Post like " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This post has no likes.\n", "red");
	}

	PostsLikes::save();

	return message;
}

std::string PostsLikes::deleteAllByUserId() {
	std::cout << PostsLikes::readAllByUserId();
	int userId = PostsLikes::getUserId();
	std::string message = "";

	std::vector<PostLike>::iterator it = PostsLikes::postsLikes.begin();
	while (it != PostsLikes::postsLikes.end()) {
		if (it->userId == userId) {
			int id = it->id;
			it = PostsLikes::postsLikes.erase(it);
			message += colored("Post like " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user hasn't liked anyone.", "red");
	}

	PostsLikes::save();

	return message;
}

std::string PostsLikes::deleteAllByUserId(int userId) {
	std::string message = "";

	std::vector<PostLike>::iterator it = PostsLikes::postsLikes.begin();
	while (it != PostsLikes::postsLikes.end()) {
		if (it->userId == userId) {
			int id = it->id;
			it = PostsLikes::postsLikes.erase(it);
			message += colored("Post like " + std::to_string(id) + " has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user hasn't liked anyone.\n", "red");
	}

	PostsLikes::save();

	return message;
}