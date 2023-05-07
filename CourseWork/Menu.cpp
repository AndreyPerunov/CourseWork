#include "Menu.h"

Menu::Menu(std::string data) {
    Menu::data = data;
}

Menu::Menu(std::string data, Menu* parent) {
    Menu::data = data;
    Menu::parent = parent;
}


Menu* Menu::addChild(std::string data) {
    Menu* child = new Menu(data, this);
    childrens.push_back(child);
    return child;
}

void Menu::addGoBack(std::string data) {
    Menu* child = new Menu(data, this);
    child->goBack = true;
    childrens.push_back(child);
}


std::string Menu::navigate(std::string flashMessage) {
    int selectedOption = 0;
    char key;
    Menu* currentMenu = this;
    std::string path = currentMenu->data;
    while (true) {
        // If edge - return
        if (currentMenu->childrens.empty()) {
            return path;
        }

        system("cls");
        std::cout << colored(path, "yellow") << '\n';
        currentMenu->displayChildren(selectedOption);
        if (flashMessage != "") {
            std::cout << '\n' << flashMessage << '\n';
            flashMessage = "";
        }        

        key = _getch();
        // Arrow down key
        if (key == 80) {
            if (selectedOption >= Menu::childrens.size() - 1) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        // Arrow up key
        if (key == 72) {
            if (selectedOption <= 0) {
                selectedOption = Menu::childrens.size() - 1;
            }
            else {
                selectedOption--;
            }
        }
        // Enter key
        if (key == '\r') {
            // Go back
            if (currentMenu->childrens[selectedOption]->goBack) {
                currentMenu = currentMenu->parent;
                std::size_t pos = path.find_last_of('/');
                path.erase(pos);
            }
            // Go deeper
            else {
                currentMenu = currentMenu->childrens[selectedOption];
                path += '/' + currentMenu->data;
            }
            selectedOption = 0;
        }
    }
}

void Menu::displayChildren(int selectedOption) {
    for (size_t i = 0; i < childrens.size(); ++i) {
        if (selectedOption == i) {
            std::cout << colored('>'+childrens[i]->data, "green") << '\n';
        } else {
            std::cout << ' ' << childrens[i]->data << '\n';
        }
    }
}