#pragma once
#ifndef _POSTS_H_
#define _POSTS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Users.h"
#include "Functions.h"
#include "fort.hpp"

struct Post {
	int id;
	char title[21];
	char body[201];
	int authorId;
};

class Posts
{
	public:
		Posts(std::string path);
		std::string create();
		std::string readAllById();
		std::string save();
	private:
		std::vector<Post> posts;
		std::string path;
		int lastId = 0;
		char* getTitle();
		char* getBody();
		int getAuthorId();
};

#endif // !_POSTS_H_