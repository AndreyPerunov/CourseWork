#include <iostream>
#include "socialMedia.h"

int main() {
	SocialMedia db;
	UserDB user = db.user();
	user.add("Name", "Password");
	

	// dev mode ->
	std::cout << "Press any button to exit! ";
	int x;
	std::cin >> x;
	db.deleteSocialMedia();

	return 0;
}