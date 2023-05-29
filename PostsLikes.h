#pragma once
#ifndef _POSTSLIKES_H_
#define _POSTSLIKES_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Functions.h"
#include "fort.hpp"
#include "Users.h"
#include "Posts.h"

struct PostLike {
	int id;
	int postId;
	int userId;
};

class PostsLikes {
	public:
		PostsLikes(std::string path);
		void readData();
		std::string save();
		std::string create();
		std::string readOneById();
		std::string readAllById();
		std::string readAllByPostId();
		std::string readAllByUserId();
		std::string deleteOneById();
		std::string deleteAllByPostId();
		std::string deleteAllByPostId(int postId);
		std::string deleteAllByUserId();
		std::string deleteAllByUserId(int userId);
		std::string getNumberOfPostsLikes();
		int getLikesCount(int postId);
	private:
		std::vector<PostLike> postsLikes;
		std::string path;
		int lastId = 0;
		int getId();
		int getPostId();
		int getUserId();
		bool liked(int postId, int userId);
};


#endif // !_POSTSLIKES_H_