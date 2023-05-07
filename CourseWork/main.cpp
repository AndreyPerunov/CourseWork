#include <iostream>
#include "Menu.h"

int main() {
    Menu* root = new Menu("");
    Menu* createDB = root->addChild("Create DB");
    createDB->addChild("Title: ...");

    Menu* selectDB = root->addChild("Select DB");
    Menu* instagram = selectDB->addChild("Instagram");
    Menu* users = instagram->addChild("Users");

    users->addChild("ReadOne")
        ->addChild("by id")
        ->addChild("<< id; username; password; email; followers count; following count; post count");
    users->addChild("by username");
    users->addChild("by email");
    users->addChild("u.t.c.");

    instagram->addChild("Posts");
    instagram->addChild("Post Likes");
    instagram->addChild("Messages");
    instagram->addChild("Follows");

    selectDB->addChild("Facebook");
    selectDB->addChild("u.t.c");
    selectDB->addChild("Go back");

    Menu* deleteDB = root->addChild("Delete DB");
    Menu* deleteInstagram = deleteDB->addChild("Instagram");
    deleteInstagram->addChild("I want to delete db Instagram")
                    ->addChild("To confirm that you want to delete it, type \"Instagram\": ...");
    deleteInstagram->addChild("Go back");

    deleteDB->addChild("Facebook");
    deleteDB->addChild("u.t.c");
    deleteDB->addChild("Go back");

    root->addChild("Quit");
    std::cout << root->navigate();

	return 0;
}