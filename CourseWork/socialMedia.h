#pragma once
#ifndef _SOCIALMEDIA_H_
#define _SOCIALMEDIA_H_

#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include "Menu.h"
#include "Functions.h"
#include "Users.h"
#include "Posts.h"
#include "PostsLikes.h"
#include "Follows.h"
#include "Messages.h"

class SocialMedia {
	public: 
		SocialMedia();
		bool deleteSocialMedia(std::string path);
	private:
		Menu* buildMenu();
		Menu* buildDBMenu(std::string title);
		void editDB(std::string title);
};

#endif // !_SOCIALMEDIA_H_
