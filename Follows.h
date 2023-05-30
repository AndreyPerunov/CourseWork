#pragma once
#ifndef _FOLLOWS_H_
#define _FOLLOWS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <cstring>
#include "Functions.h"
#include "fort.hpp"
#include "Users.h"

struct Follow {
	int id;
	int followerId;
	int followingId;
};

class Follows {
	public:
		Follows(std::string path);
		std::string create();
		std::string readOneById();
		std::string readAllById();
		std::string readAllByFollowerId();
		std::string readAllByFollowingId();
		std::string filterByFollowerId();
		std::string filterByFollowingId();
		std::string deleteOneById();
		std::string deleteAllByFollowerId();
		std::string deleteAllByFollowerId(int userId);
		std::string deleteAllByFollowingId();
		std::string deleteAllByFollowingId(int userId);
		std::string getNumberOfFollows();
		int getFollowersCount(int userId);
		int getFollowingCount(int userId);
		void readData();
	private:
		std::vector<Follow> follows;
		std::string path;
		int lastId = 0;
		int getUserId(std::string whatToGet);
		int getId();
		bool followed(int followerId, int followingId);
		std::string save();
};


#endif // !_FOLLOWS_H_