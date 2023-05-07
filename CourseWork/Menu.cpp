#include "Menu.h"

Menu::Menu(std::string data) {
    Menu::data = data;
}

Menu* Menu::addChild(std::string data) {
    Menu* child = new Menu(data);
    childrens.push_back(child);
    return child;
}

std::string Menu::navigate() {
    int selectedOption = 0;
    char key;
    Menu* currentMenu = this;
    while (true) {
        if (currentMenu->childrens.empty()) {
            return (currentMenu->data);
        }
        system("cls");
        std::cout << "Current menu: " << currentMenu->data << '\n';

        currentMenu->displayChildren(selectedOption);

        key = _getch();
        // arrow down key
        if (key == 80) {
            if (selectedOption >= Menu::childrens.size() - 1) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        // arrow up key
        if (key == 72) {
            if (selectedOption <= 0) {
                selectedOption = Menu::childrens.size() - 1;
            }
            else {
                selectedOption--;
            }
        }
        // enter key
        if (key == '\r') {
            currentMenu = currentMenu->childrens[selectedOption];
        }
    }
}

void Menu::displayChildren(int selectedOption) {
    for (size_t i = 0; i < childrens.size(); ++i) {
        if (selectedOption == i) {
            std::cout << '>' << colored(childrens[i]->data, "green") << '\n';
        } else {
            std::cout << ' ' << childrens[i]->data << '\n';
        }
    }
}