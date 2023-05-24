#pragma once
#ifndef _USERS_H_
#define _USERS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <cstring>
#include "Color.h"
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
		std::string readAllById();
		std::string readAllByUsername();
		std::string readAllByEmail();
		std::string updateById();
		std::string updateByUsername();
		std::string updateByEmail();
		std::string deleteById();
		std::string deleteByUsername();
		std::string deleteByEmail();
	private:
		std::vector<User> users;
		std::string path;
		int lastId = 0;
		char* stoc(std::string string);
		bool usernameExists(std::string username);
		bool emailExists(std::string username);
		int getId();
		char* getValidUsername();
		char* getUsername();
		char* getPassword();
		char* getValidEmail();
		char* getEmail();
};

#endif // !_USERS_H_
