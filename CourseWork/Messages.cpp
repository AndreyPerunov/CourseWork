#include "Messages.h"

Messages::Messages(std::string path) {
	Messages::path = path;
	Messages::readData();
}

void Messages::readData() {
	std::string filename = "messages.bin";
	std::ifstream messagesFileRead(Messages::path + filename, std::ios::binary);

	if (messagesFileRead.is_open()) {
		// If file already exists read data in vector
		Messages::messages.clear();
		Message message;
		while (messagesFileRead.peek() != EOF) {
			messagesFileRead.read((char*)&message.id, sizeof(message.id));
			messagesFileRead.read((char*)&message.fromId, sizeof(message.fromId));
			messagesFileRead.read((char*)&message.toId, sizeof(message.toId));
			messagesFileRead.read(message.message, sizeof(message.message));
			Messages::messages.push_back(message);
		}
		if (!Messages::messages.empty()) {
			Messages::lastId = Messages::messages.back().id;
		}
	}
	else {
		// Else create a file
		std::ofstream messagesFileWrite(Messages::path + filename, std::ios::binary);
		if (!messagesFileWrite.is_open()) {
			throw std::runtime_error("Error creating " + filename + "!");
		}
		messagesFileWrite.close();
	}
}

std::string Messages::save() {
	std::string filename = "messages.bin";
	std::ofstream messagesFile(Messages::path + filename, std::ios::binary);

	if (!messagesFile.is_open()) {
		return colored("Error opening file " + filename + "!", "red");
	}

	for (Message message: Messages::messages) {
		messagesFile.write((char*)&message.id, sizeof(message.id));
		messagesFile.write((char*)&message.fromId, sizeof(message.fromId));
		messagesFile.write((char*)&message.toId, sizeof(message.toId));
		messagesFile.write(message.message, sizeof(message.message));
	}

	messagesFile.close();

	return colored("Messages were saved successfully.", "green");
}

int Messages::getUserId(std::string whatToGet) {
	Users users(Messages::path);
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

char* Messages::getMessage() {
	std::string message;
	std::regex pattern("[a-zA-Z0-9!\\(\\)\\-\\.\\?\\[\\]_`~;:!@#$%^&*+= '\\',\"{}|><']+");

	while (true) {
		std::cout << "Enter " << colored("message", "blue") << ": ";
		std::getline(std::cin, message);
		if (!std::regex_match(message, pattern)) {
			std::cout << colored("Message can contain only english letters, numbers and special characters.", "red") << '\n';
		}
		else if (message.length() > 100) {
			std::cout << colored("Message can't exceed 100 characters.", "red") << '\n';
		}
		else if (message.length() < 1) {
			std::cout << colored("Message must be at least 1 character long.", "red") << '\n';
		}
		else {
			return stoc(message);
		}
	}
}

int Messages::getId() {
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

// Create
std::string Messages::create() {
	int fromId = Messages::getUserId("fromId");
	int toId = Messages::getUserId("toId");
	char* message = Messages::getMessage();

	Messages::lastId++;
	Message newMessage;
	newMessage.id = Messages::lastId;
	newMessage.fromId = fromId;
	newMessage.toId = toId;
	strncpy_s(newMessage.message, sizeof(newMessage.message), message, _TRUNCATE);

	Messages::messages.push_back(newMessage);
	Messages::save();

	return colored("Message " + std::to_string(newMessage.id) + " has been created.", "green");
}

// Read One
std::string Messages::readOneById() {
	Users users(Messages::path);

	int id = Messages::getId();
	for (Message message : Messages::messages) {
		if (message.id == id) {
			fort::char_table table;

			table << fort::header
				<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr
				<< message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << message.message << fort::endr;

			return table.to_string();
		}
	}

	return colored("Message does not exist.", "red");
}