#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>
#include <string>
#include "Color.h"
#include <conio.h>

class Menu {
    public:
        Menu(std::string data);
        std::string navigate();
        Menu* addChild(std::string data);
    private:
        void displayChildren(int selectedOption = 0);
        std::string data;
        std::vector<Menu*> childrens;
};

#endif // !_MENU_H_