#include "Posts.h"

Posts::Posts(std::string path) {
	Posts::path = path;
	Posts::readData();
}

void Posts::readData() {
	std::string filename = "posts.bin";
	std::ifstream postsFileRead(Posts::path + filename, std::ios::binary);

	if (postsFileRead.is_open()) {
		// If file already exists read data in vector
		Posts::posts.clear();
		Post post;
		while (postsFileRead.peek() != EOF) {
			postsFileRead.read((char*)&post.id, sizeof(post.id));
			postsFileRead.read(post.title, sizeof(post.title));
			postsFileRead.read(post.body, sizeof(post.body));
			postsFileRead.read((char*)&post.authorId, sizeof(post.authorId));
			Posts::posts.push_back(post);
		}
		if (!Posts::posts.empty()) {
			Posts::lastId = Posts::posts.back().id;
		}
	}
	else {
		// Else create a file
		std::ofstream postsFileWrite(Posts::path + filename, std::ios::binary);
		if (!postsFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		postsFileWrite.close();
	}
}

std::string Posts::save() {
	std::string filename = "posts.bin";
	std::ofstream postsFile(Posts::path + filename, std::ios::binary);

	if (!postsFile.is_open()) {
		return colored("Error opening file " + filename + "!", "red");
	}

	for (Post post : Posts::posts) {
		postsFile.write((char*)&post.id, sizeof(post.id));
		postsFile.write(post.title, sizeof(post.title));
		postsFile.write(post.body, sizeof(post.body));
		postsFile.write((char*)&post.authorId, sizeof(post.authorId));
	}

	postsFile.close();

	return colored("Posts were saved successfully.", "green");
}

char* Posts::getTitle() {
	std::string title;
	std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+= '\\',\"{}|><']+");

	while (true) {
		std::cout << "Enter " << colored("title", "blue") << ": ";
		std::getline(std::cin, title);
		if (!std::regex_match(title, pattern)) {
			std::cout << colored("Title can contain only english letters, numbers and special characters.", "red") << '\n';
		}
		else if (title.length() > 20) {
			std::cout << colored("Title can't exceed 20 characters.", "red") << '\n';
		}
		else if (title.length() < 2) {
			std::cout << colored("Title must be at least 2 characters long.", "red") << '\n';
		}
		else {
			return stoc(title);
		}
	}
}

char* Posts::getBody() {
	std::string title;
	std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+= '\\',\"{}|><']+");

	while (true) {
		std::cout << "Enter " << colored("body", "blue") << ": ";
		std::getline(std::cin, title);
		if (!std::regex_match(title, pattern)) {
			std::cout << colored("Body can contain only english letters, numbers and special characters.", "red") << '\n';
		}
		else if (title.length() > 200) {
			std::cout << colored("Body can't exceed 200 characters.", "red") << '\n';
		}
		else if (title.length() < 2) {
			std::cout << colored("Body must be at least 2 characters long.", "red") << '\n';
		}
		else {
			return stoc(title);
		}
	}
}

int Posts::getAuthorId() {
	Users users(Posts::path);
	std::cout << users.readAllById();
	std::string id;
	std::regex pattern("[0-9]+");
	while (true) {
		std::cout << "Enter " << colored("author id", "blue") << ": ";
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

int Posts::getId() {
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

int Posts::getPostsCount(int authorId) {
	int count = 0;
	for (Post post : Posts::posts) {
		if (post.authorId == authorId) {
			++count;
		}
	}
	return count;
}

std::string Posts::getTitleById(int id) {
	for (Post post : Posts::posts) {
		if (post.id == id) return post.title;
	}
	return colored("Title not found!", "red");
}

bool Posts::idExists(int id) {
	for (Post post : Posts::posts) {
		if (post.id == id) return true;
	}
	return false;
}

// Create
std::string Posts::create() {
	char* title = Posts::getTitle();
	char* body = Posts::getBody();
	int authorId = Posts::getAuthorId();

	Posts::lastId++;
	Post newPost;
	newPost.id = Posts::lastId;
	strncpy_s(newPost.title, sizeof(newPost.title), title, _TRUNCATE);
	strncpy_s(newPost.body, sizeof(newPost.body), body, _TRUNCATE);
	newPost.authorId = authorId;
	Posts::posts.push_back(newPost);
	Posts::save();

	return colored((newPost.title), "green") + colored(" has been created.", "green");
}

// Read One
std::string Posts::readOneById() {
	PostsLikes postsLikes(Posts::path);
	Users users(Posts::path);

	int id = Posts::getId();
	for (Post post : Posts::posts) {
		if (post.id == id) {
			fort::char_table table;

			table << fort::header
				<< "ID" << "Title" << "Body" << "Author ID" << "Author" << "Likes" << fort::endr
				<< post.id << post.title << post.body << post.authorId << users.getUsernameById(post.authorId) << postsLikes.getLikesCount(post.id) << fort::endr;

			return table.to_string();
		}
	}

	return colored("Post does not exist.", "red");
}

// Read All
std::string Posts::readAllById() {
	PostsLikes postsLikes(Posts::path);
	Users users(Posts::path);

	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Title" << "Body" << "Author ID" << "Author" << "Likes" << fort::endr;

	// Set Content
	for (Post post : Posts::posts) {
		table << post.id << post.title << post.body << post.authorId << users.getUsernameById(post.authorId) << postsLikes.getLikesCount(post.id) << fort::endr;
	}

	return table.to_string();
}

std::string Posts::readAllByTitle() {
	PostsLikes postsLikes(Posts::path);
	Users users(Posts::path);

	std::vector<Post> copyPosts = Posts::posts;

	// Sort
	std::sort(copyPosts.begin(), copyPosts.end(), [](Post a, Post b) {
		return strcmp(a.title, b.title) < 0;
	});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Title" << "Body" << "Author ID" << "Username" << "Likes" << fort::endr;

	// Set Content
	for (Post post : copyPosts) {
		table << post.id << post.title << post.body << post.authorId << users.getUsernameById(post.authorId) << postsLikes.getLikesCount(post.id) << fort::endr;
	}

	return table.to_string();
}

std::string Posts::readAllByBody() {
	PostsLikes postsLikes(Posts::path);
	Users users(Posts::path);

	std::vector<Post> copyPosts = Posts::posts;

	// Sort
	std::sort(copyPosts.begin(), copyPosts.end(), [](Post a, Post b) {
		return strcmp(a.body, b.body) < 0;
		});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Title" << "Body" << "Author ID" << "Author" << "Likes" << fort::endr;

	// Set Content
	for (Post post : copyPosts) {
		table << post.id << post.title << post.body << post.authorId << users.getUsernameById(post.authorId) << postsLikes.getLikesCount(post.id) << fort::endr;
	}

	return table.to_string();
}

std::string Posts::readAllByAuthorId() {
	PostsLikes postsLikes(Posts::path);
	Users users(Posts::path);

	std::vector<Post> copyPosts = Posts::posts;

	// Sort
	std::sort(copyPosts.begin(), copyPosts.end(), [](Post a, Post b) {
		return a.authorId < b.authorId;
	});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Title" << "Body" << "Author ID" << "Author" << "Likes" << fort::endr;

	// Set Content
	for (Post post : copyPosts) {
		table << post.id << post.title << post.body << post.authorId << users.getUsernameById(post.authorId) << postsLikes.getLikesCount(post.id) << fort::endr;
	}

	return table.to_string();
}

// Update
std::string Posts::updateById() {
	std::cout << Posts::readAllById();
	int id = Posts::getId();
	for (auto it = Posts::posts.begin(); it != Posts::posts.end(); ++it) {
		if (it->id == id) {
			std::string message = "";
			std::string answer;
			std::cout << "Whould you like to change the title? (y - to change): ";
			std::getline(std::cin, answer);
			if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
				std::string oldTitle = it->title;
				char* newTitle = Posts::getTitle();
				strncpy_s(it->title, sizeof(it->title), newTitle, _TRUNCATE);
				message += colored(std::string("Title ") + oldTitle + " has been changed to " + newTitle + ".\n", "green");
			}
			std::cout << "Whould you like to change the body? (y - to change): ";
			std::getline(std::cin, answer);
			if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
				std::string oldBody = it->body;
				char* newBody = Posts::getBody();
				strncpy_s(it->body, sizeof(it->body), newBody, _TRUNCATE);
				message += colored(std::string("Body ") + oldBody + " has been changed to " + newBody + ".\n", "green");
			}
			std::cout << "Whould you like to change the author id? (y - to change): ";
			std::getline(std::cin, answer);
			if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
				int oldAuthor = it->authorId;
				int newAuthor = Posts::getAuthorId();
				it->authorId = newAuthor;
				message += colored("Author " + std::to_string(oldAuthor) + " has been changed to " + std::to_string(newAuthor) + ".\n", "green");
			}

			if (message == "") {
				return colored("Nothing was changed.", "green");
			}
			else {
				Posts::save();
				return message;
			}
		}
	}

	return colored("Post does not exist.", "red");
}

// Delte One
std::string Posts::deleteOneById() {
	PostsLikes postsLikes(Posts::path);
	std::cout << Posts::readAllById();
	int id = Posts::getId();
	for (auto it = Posts::posts.begin(); it != Posts::posts.end(); ++it) {
		if (it->id == id) {
			std::string title = it->title;
			Posts::posts.erase(it);
			Posts::save();
			return colored(std::string("Post ") + title + " has been deleted.\n", "green") + postsLikes.deleteAllByPostId(id);
		}
	}

	return colored("Post does not exist.", "red");
}

// Delete All by authorId
std::string Posts::deleteAllByAythorId() {
	PostsLikes postsLikes(Posts::path);
	std::cout << Posts::readAllByAuthorId();
	int authorId = Posts::getAuthorId();
	std::string message = "";
	std::vector<Post>::iterator it = Posts::posts.begin();
	while (it != Posts::posts.end()) {
		if (it->authorId == authorId) {
			std::string title = it->title;
			int id = it->id;
			it = Posts::posts.erase(it);
			message += colored(std::string("Post ") + title + " has been deleted.\n", "green") + postsLikes.deleteAllByPostId(id) + '\n';
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user has no posts.\n", "red");
	}
	Posts::save();
	return message;
}

std::string Posts::deleteAllByAythorId(int authorId) {
	PostsLikes postsLikes(Posts::path);
	std::string message = "";
	auto it = Posts::posts.begin();
	while (it != Posts::posts.end()) {
		if (it->authorId == authorId) {
			std::string title = it->title;
			int id = it->id;
			it = Posts::posts.erase(it);
			message += colored(std::string("Post ") + title + " has been deleted.\n", "green") + postsLikes.deleteAllByPostId(id) + '\n';
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user has no posts.\n", "red");
	}
	Posts::save();
	return message;
}