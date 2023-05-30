#pragma once
#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <cstring>
#include "Functions.h"
#include "fort.hpp"
#include "Users.h"

struct Message {
	int id;
	int fromId;
	int toId;
	char message[101];
};

class Messages {
	public:
		Messages(std::string);
		void readData();
		std::string create();
		std::string readOneById();
		std::string readAllById();
		std::string readAllByFromId();
		std::string readAllByToId();
		std::string readAllByMessages();
		std::string filterByFromId();
		std::string filterByToId();
		std::string updateById();
		std::string deleteOneById();
		std::string deleteAllByFromId();
		std::string deleteAllByFromId(int userId);
		std::string deleteAllByToId();
		std::string deleteAllByToId(int userId);
		std::string getNumberOfMessages();
		std::string getNumberOfMessagesSentYourself();
	private:
		std::vector<Message> messages;
		std::string path;
		int lastId = 0;
		std::string save();
		int getUserId(std::string whatToGet);
		char* getMessage();
		int getId();
};

#endif // !_MESSAGES_H_
