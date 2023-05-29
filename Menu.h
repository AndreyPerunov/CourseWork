#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "Functions.h"
#include <conio.h>

class Menu {
    public:
        Menu(std::string data);
        Menu(std::string data, Menu* parent);
        Menu* addChild(std::string data);
        void addGoBack(std::string data);
        std::string navigate();
        std::string navigate(std::string &flashMessage);
    private:
        void displayChildren(size_t selectedOption = 0);
        std::string data;
        std::vector<Menu*> children;
        Menu* parent;
        bool goBack = false;
};

#endif // !_MENU_H_