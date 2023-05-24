#include "Posts.h"

Posts::Posts(std::string path) {
	Posts::path = path;

	std::string filename = "posts.bin";
	std::ifstream postsFileRead(path + filename, std::ios::binary);

	if (postsFileRead.is_open()) {
		// If file already exists read data in vector
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
		std::ofstream postsFileWrite(path + filename, std::ios::binary);
		if (!postsFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		postsFileWrite.close();
	}
}

char* Posts::getTitle() {
	std::string title;
	std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+=]+");

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
	std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+= '\\']+");

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

	return colored((newPost.title), "green") + colored(" has been created.", "green");;
}

std::string Posts::readAllById() {
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "Title" << "Body" << "Author ID" << fort::endr;

	// Set Content
	for (Post post : Posts::posts) {
		table << post.id << post.title << post.body << post.authorId << fort::endr;
	}

	return table.to_string();
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