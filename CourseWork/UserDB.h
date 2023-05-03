#pragma once
#ifndef _USERDB_H_
#define _USERDB_H_

#include <fstream>
#include <iostream>
#include <vector>

struct User {
	int id;
	char username[20];
	char uassword[50];
	char email[30];
};

class UserDB
{
	public:
		UserDB(std::string path);
		void add(std::string username, std::string password);
	private:
		std::vector<User> users;
		std::string path;
		int lastId;
};

#endif // !_USERDB_H_
