#include "Menu.h"


void Menu::print() {
	int selectedOption = 0;	
	char key;
	while (true)
	{
		system("cls");

		for (int i = 0; i < Menu::options.size(); i++) {
			if (selectedOption == i) {
				std::cout << colored((">" + Menu::options[i]), "green") << '\n';
			}
			else {
				std::cout << " " << Menu::options[i] << '\n';
			}
		}

		key = _getch();
		// arrow down key
		if (key == 80 && selectedOption < Menu::options.size() - 1) { 
			selectedOption++;
		}
		// arrow up key
		if (key == 72 && selectedOption > 0) {
			selectedOption--;
		}
		// enter key
		if (key == '\r') {
			std::cout	<< '\n'
						<< "You have selected: " 
						<< colored(Menu::options[selectedOption], "green")
						<< '\n';
			return;
		}
	}
}

std::string Menu::colored(std::string text, std::string color) {
	if (color == "black") return "\033[1;30m" + text + "\033[0m";
	if (color == "red") return "\033[1;31m" + text + "\033[0m";
	if (color == "green") return "\033[1;32m" + text + "\033[0m";
	if (color == "yellow") return "\033[1;33m" + text + "\033[0m";
	if (color == "blue") return "\033[1;34m" + text + "\033[0m";
	if (color == "magenta") return "\033[1;35m" + text + "\033[0m";
	if (color == "cyan") return "\033[1;36m" + text + "\033[0m";
	if (color == "white") return "\033[1;37m" + text + "\033[0m";
	return "Invalid color name!";
}