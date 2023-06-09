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
#include "Messages.h"

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
		std::string readOneById();
		std::string readOneByUsername();
		std::string readOneByEmail();
		std::string readAllById();
		std::string readAllByUsername();
		std::string readAllByEmail();
		std::string filterWithPosts();
		std::string filterWithFollowers();
		std::string filterWithFollowing();
		std::string updateById();
		std::string updateByUsername();
		std::string updateByEmail();
		std::string deleteById();
		std::string deleteByUsername();
		std::string deleteByEmail();
		std::string getNumberOfUsers();
		std::string getNumberOfUsersWithPosts();
		std::string getNumberOfUsersWithFollowers();
		std::string getNumberOfUsersWithFollowing();
		bool idExists(int id);
		std::string getUsernameById(int id);
	private:
		std::vector<User> users;
		std::string path;
		int lastId = 0;
		std::string save();
		bool usernameExists(std::string username);
		bool emailExists(std::string username);
		int getId();
		int getNumber(std::string prompt);
		char* getValidUsername();
		char* getUsername();
		char* getPassword();
		char* getValidEmail();
		char* getEmail();
};

#endif // !_USERS_H_
