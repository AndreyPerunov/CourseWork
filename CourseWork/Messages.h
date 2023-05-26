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
