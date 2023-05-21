#pragma once
#ifndef _USERS_H_
#define _USERS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include "Color.h"
#include <regex>
#include <string>
#include "fort.hpp"

struct User {
	User();
	int id;
	char username[21];
	char password[51];
	char email[31];
};

class Users
{
	public:
		Users(std::string path);
		User create();
		std::string save();
		std::string readOneById();
		std::string readOneByUsername();
		std::string readOneByEmail();
		std::string readAll();
		std::string deleteOneByUsername();
		std::string deleteOneByEmail();
		std::string deleteAll();
	private:
		std::vector<User> users;
		std::string path;
		int lastId = 0;
		char* stoc(std::string string);
		bool usernameExists(std::string username);
		char* getValidUsername();
		char* getUsername();
		char* getPassword();
		bool emailExists(std::string username);
		char* getValidEmail();
		char* getEmail();
};

#endif // !_USERS_H_
