#pragma once
#ifndef _USERS_H_
#define _USERS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <cstring>
#include "Functions.h"
#include "fort.hpp"
#include "Posts.h"
#include "PostsLikes.h"
#include "Follows.h"

struct User {
	int id;
	char username[21];
	char password[51];
	char email[31];
};

class Users {
	public:
		Users(std::string path);
		std::string create();
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
		bool idExists(int id);
		std::string getUsernameById(int id);
	private:
		std::vector<User> users;
		std::string path;
		int lastId = 0;
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
