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
		else if (id.length() >= 10) {
      std::cout << colored("ID cannot exceed 999999999.", "red") << '\n';
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
		else if (id.length() >= 10) {
      std::cout << colored("ID cannot exceed 999999999.", "red") << '\n';
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
				<< message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;

			table.row(0).set_cell_bg_color(fort::color::magenta);

			return table.to_string();
		}
	}

	return colored("Message does not exist.", "red");
}

// Read All
std::string Messages::readAllById() {
	Users users(Messages::path);

	fort::char_table table;

	// Set Header
	table << fort::header
		  << "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message : Messages::messages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);

	return table.to_string();
}

std::string Messages::readAllByFromId() {
	Users users(Messages::path);

	std::vector<Message> copyMessages = Messages::messages;

	// Sort
	std::sort(copyMessages.begin(), copyMessages.end(), [](Message a, Message b) {
		return a.fromId < b.fromId;
	});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message: copyMessages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);

	return table.to_string();
}

std::string Messages::readAllByToId() {
	Users users(Messages::path);

	std::vector<Message> copyMessages = Messages::messages;

	// Sort
	std::sort(copyMessages.begin(), copyMessages.end(), [](Message a, Message b) {
		return a.toId < b.toId;
		});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message : copyMessages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);

	return table.to_string();
}

std::string Messages::readAllByMessages() {
	Users users(Messages::path);

	std::vector<Message> copyMessages = Messages::messages;

	// Sort
	std::sort(copyMessages.begin(), copyMessages.end(), [](Message a, Message b) {
		return strcmp(a.message, b.message) < 0;
		});

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message : copyMessages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);
	
	return table.to_string();
}

std::string Messages::filterByFromId() {
	Users users(Messages::path);

	int fromId = getUserId("from id");

	std::vector<Message> filteredMessages;

	for (Message message : Messages::messages) {
		if (message.fromId == fromId) {
			filteredMessages.push_back(message);
		}
	}

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message: filteredMessages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);

	return table.to_string();
}

std::string Messages::filterByToId() {
	Users users(Messages::path);

	int toId = getUserId("to id");

	std::vector<Message> filteredMessages;

	for (Message message : Messages::messages) {
		if (message.toId == toId) {
			filteredMessages.push_back(message);
		}
	}

	// Create a table
	fort::char_table table;

	// Set Header
	table << fort::header
		<< "ID" << "From ID" << "From" << "To ID" << "To" << "Message" << fort::endr;

	// Set Content
	for (Message message: filteredMessages) {
		table << message.id << message.fromId << users.getUsernameById(message.fromId) << message.toId << users.getUsernameById(message.toId) << cropLongText(message.message) << fort::endr << fort::separator;
	}

	table.row(0).set_cell_bg_color(fort::color::magenta);

	return table.to_string();
}

// Update
std::string Messages::updateById() {
	std::cout << Messages::readAllById();
	int id = Messages::getId();
	for (auto it = Messages::messages.begin(); it != Messages::messages.end(); ++it) {
		if (it->id == id) {
			std::string oldMessage = it->message;
			char* newMessage = Messages::getMessage();
			strncpy_s(it->message, sizeof(it->message), newMessage, _TRUNCATE);
			Messages::save();
			return colored("Message " + oldMessage + " has been changed to " + newMessage + ".\n", "green");
		}
	}

	return colored("Message does not exist.", "red");
}

// Delete One
std::string Messages::deleteOneById() {
	std::cout << Messages::readAllById();
	int id = Messages::getId();
	for (auto it = Messages::messages.begin(); it != Messages::messages.end(); ++it) {
		if (it->id == id) {
			Messages::messages.erase(it);
			Messages::save();
			return colored("Message with id " + std::to_string(id) + " has been deleted.", "green");
		}
	}

	return colored("Message does not exist.", "red");
}

// Delete All
std::string Messages::deleteAllByFromId() {
	std::cout << Messages::readAllByFromId();
	int fromId = Messages::getUserId("from id");
	std::string message = "";
	std::vector<Message>::iterator it = Messages::messages.begin();
	while (it != Messages::messages.end()) {
		if (it->fromId == fromId) {
			std::string deletedMessage = it->message;
			it = Messages::messages.erase(it);
			message += colored("Message '" + deletedMessage + "' has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user have not sent any messages.\n", "red");
	}
	Messages::save();
	return message;
}

std::string Messages::deleteAllByFromId(int userId) {
	std::string message = "";
	std::vector<Message>::iterator it = Messages::messages.begin();
	while (it != Messages::messages.end()) {
		if (it->fromId == userId) {
			std::string deletedMessage = it->message;
			it = Messages::messages.erase(it);
			message += colored("Message '" + deletedMessage + "' has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user have not sent any messages.\n", "red");
	}
	Messages::save();
	return message;
}

std::string Messages::deleteAllByToId() {
	std::cout << Messages::readAllByToId();
	int toId = Messages::getUserId("to id");
	std::string message = "";
	std::vector<Message>::iterator it = Messages::messages.begin();
	while (it != Messages::messages.end()) {
		if (it->toId == toId) {
			std::string deletedMessage = it->message;
			it = Messages::messages.erase(it);
			message += colored("Message '" + deletedMessage + "' has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user have not recieved any messages.\n", "red");
	}
	Messages::save();
	return message;
}

std::string Messages::deleteAllByToId(int userId) {
	std::string message = "";
	std::vector<Message>::iterator it = Messages::messages.begin();
	while (it != Messages::messages.end()) {
		if (it->toId == userId) {
			std::string deletedMessage = it->message;
			it = Messages::messages.erase(it);
			message += colored("Message '" + deletedMessage + "' has been deleted.\n", "green");
		}
		else {
			++it;
		}
	}

	if (message == "") {
		return colored("This user have not recieved any messages.\n", "red");
	}
	Messages::save();
	return message;
}

// Summary
std::string Messages::getNumberOfMessages() {
	std::string output = "There is " + colored(std::to_string(Messages::messages.size()), "blue");

  if (Messages::messages.size() == 1) {
    output += " message.";
  } else {
  	output += " messages.";
  }

  return output;
}

std::string Messages::getNumberOfMessagesSentYourself() {
	int count = 0;
  for (Message message : Messages::messages) {
  	if(message.fromId == message.toId) {
      count++;
    }
  }

	std::string output = "There is " + colored(std::to_string(count), "blue");

  if (count == 1) {
    output += " message sent to yourself.";
  } else {
  	output += " messages sent to yourself.";
  }

  return output;
}