#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>
#include <conio.h>

class Menu {
public:
	void print();
private:
	std::string colored(std::string text, std::string color);
	std::vector<std::string> options = {
		"Select database",
		"Create database",
		"Delete database",
		"Quit",
	};
};

#endif // !_MENU_H_