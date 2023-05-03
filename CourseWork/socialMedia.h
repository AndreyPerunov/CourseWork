#pragma once
#ifndef _SOCIALMEDIA_H_
#define _SOCIALMEDIA_H_

#include <filesystem>
#include <iostream>
#include "UserDB.h"

class SocialMedia
{
public: 
	SocialMedia();
	bool deleteSocialMedia();
	UserDB user();
private:
	std::string path = "";
};

#endif // !_SOCIALMEDIA_H_
