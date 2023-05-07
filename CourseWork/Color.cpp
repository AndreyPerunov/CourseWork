#include "Color.h"

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