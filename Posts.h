#pragma once
#ifndef _POSTS_H_
#define _POSTS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Functions.h"
#include "fort.hpp"
#include "Users.h"
#include "PostsLikes.h"

struct Post {
	int id;
	char title[21];
	char body[201];
	int authorId;
};

class Posts {
	public:
		Posts(std::string path);
		void readData();
		std::string save();
		std::string create();
		std::string readOneById();
		std::string readAllById();
		std::string readAllByTitle();
		std::string readAllByBody();
		std::string readAllByAuthorId();
		std::string updateById();
		std::string deleteOneById();
		std::string deleteAllByAythorId();
		std::string deleteAllByAythorId(int authorId);
		std::string getNumberOfPosts();
		std::string getNumberOfPostsWithLikes();
		int getPostsCount(int authorId);
		bool idExists(int id);
		std::string getTitleById(int id);
	private:
		std::vector<Post> posts;
		std::string path;
		int lastId = 0;
		int getId();
		char* getTitle();
		char* getBody();
		int getAuthorId();
		int getLikes();
};

#endif // !_POSTS_H_