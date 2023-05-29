#include "Functions.h"

std::string colored(std::string text, std::string color) {
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

char* stoc(std::string string) {
	char* result = new char[string.length() + 1];
	strcpy_s(result, string.length() + 1, string.c_str());
	return result;
}

std::string cropLongText(std::string longText) {
    const int charLimit = 15;
    for (std::size_t i = charLimit; i < longText.size(); i += charLimit + 1) {
        if (longText[i - 1] == ' ') { // If the character before the newline is a space
            longText[i - 1] = '\n';  // Replace it with a newline
            longText.insert(i, " "); // Insert a space after the newline
        } else {
            longText.insert(i, "\n"); // Insert a newline
        }
    }
    return longText;
}