#include "SocialMedia.h"
namespace fs = std::filesystem;

Menu* SocialMedia::buildMenu(std::string title) {
    Menu* root = new Menu(title);
 
    Menu* users = root->addChild("Users");
    users->addChild("create");
    Menu* readOneUser = users->addChild("readOne");
    readOneUser->addChild("by id");
    readOneUser->addChild("by username");
    readOneUser->addChild("by email");
    Menu* readAllUsers = users->addChild("readAll");
    readAllUsers->addChild("sort by id");
    readAllUsers->addChild("sort by username");
    readAllUsers->addChild("sort by email");
    Menu* updateUser = users->addChild("update");
    updateUser->addChild("by id");
    updateUser->addChild("by username");
    updateUser->addChild("by email");
    Menu* deleteOneUser = users->addChild("delete");
    deleteOneUser->addChild("by id");
    deleteOneUser->addChild("by username");
    deleteOneUser->addChild("by email");
    Menu* summaryUsers = users->addChild("summary");
    summaryUsers->addChild("get number of users");
    summaryUsers->addChild("get number of users with posts more than...");
    summaryUsers->addChild("get number of users with followers more than...");
    summaryUsers->addChild("get number of users with following more than...");
    users->addGoBack("Go back");

    Menu* posts = root->addChild("Posts");
    posts->addChild("create");
    posts->addChild("readOne")->addChild("by id");
    Menu* readAllPosts = posts->addChild("readAll");
    readAllPosts->addChild("sort by id");
    readAllPosts->addChild("sort by title");
    readAllPosts->addChild("sort by body");
    readAllPosts->addChild("sort by author id");
    posts->addChild("update")->addChild("by id");
    posts->addChild("deleteOne")->addChild("by id");
    posts->addChild("deleteAll")->addChild("by author id");
    Menu* summaryPosts = posts->addChild("summary");
    summaryPosts->addChild("get number of posts");
    summaryPosts->addChild("get number of posts where number of likes is bigger than...");
    posts->addGoBack("Go back");

    Menu* postsLikes = root->addChild("Posts Likes");
    postsLikes->addChild("create");
    postsLikes->addChild("readOne")->addChild("by id");
    Menu* readAllPostsLikes = postsLikes->addChild("readAll");
    readAllPostsLikes->addChild("sort by id");
    readAllPostsLikes->addChild("sort by post id");
    readAllPostsLikes->addChild("sort by user id");
    postsLikes->addChild("deleteOne")->addChild("by id");
    Menu* deleteAllPostsLikes = postsLikes->addChild("deleteAll");
    deleteAllPostsLikes->addChild("by user id");
    deleteAllPostsLikes->addChild("by post id");
    Menu* summaryPostsLikes = postsLikes->addChild("summary");
    summaryPostsLikes->addChild("get number of postsLikes");
    postsLikes->addGoBack("Go back");

    Menu* follows = root->addChild("Follows");
    follows->addChild("create");
    follows->addChild("readOne")->addChild("by id");
    Menu* readAllFollows = follows->addChild("readAll");
    readAllFollows->addChild("sort by id");
    readAllFollows->addChild("sort by follower id");
    readAllFollows->addChild("sort by following id");
    follows->addChild("deleteOne")->addChild("by id");
    Menu* deleteAllFollows= follows->addChild("deleteAll");
    deleteAllFollows->addChild("by follower id");
    deleteAllFollows->addChild("by following id");
    Menu* summaryFollows = follows->addChild("summary");
    summaryFollows->addChild("get number of follows");
    follows->addGoBack("Go back");

    Menu* messages = root->addChild("Messages");
    messages->addChild("create");
    messages->addChild("readOne")->addChild("by id");
    Menu* readAllMessages = messages->addChild("readAll");
    readAllMessages->addChild("sort by id");
    readAllMessages->addChild("sort by from id");
    readAllMessages->addChild("sort by to id");
    readAllMessages->addChild("sort by message");
    messages->addChild("update")->addChild("by id");
    messages->addChild("deleteOne")->addChild("by id");
    Menu* deleteAllMessages = messages->addChild("deleteAll");
    deleteAllMessages->addChild("by from id");
    deleteAllMessages->addChild("by to id");
    Menu* summaryMessages = messages->addChild("summary");
    summaryMessages->addChild("get number of messages");
    summaryMessages->addChild("get number of messages sent to yourself");
    messages->addGoBack("Go back");

     root->addChild("Quit");

    return root;
}

SocialMedia::SocialMedia(std::string title) {  
    try {
        std::string flashMessage = "";

        fs::path folderPath(title);

        // Creating directory
        try {
            if (!fs::create_directory(folderPath)) {
                flashMessage = colored("You have entered into an existing database '" + title + "'.", "yellow");
            }
            else {
                flashMessage = colored("Database '" + title + "' have been created.", "green");
            }
        }
        catch (fs::filesystem_error& e) {
            std::cout << colored("Error creating database: " + std::string(e.what()), "red");
            std::cin.get();
            return;
        }

        Users users("./" + title + "/");
        Posts posts("./" + title + "/");
        PostsLikes postsLikes("./" + title + "/");
        Follows follows("./" + title + "/");
        Messages messages("./" + title + "/");

        // Navigation
        while (true) {
            std::string selectedOption = buildMenu(title)->navigate(flashMessage);
            std::cout << '\n' + colored(selectedOption, "green") + '\n';
            selectedOption = selectedOption.substr(title.length());

            ///////////////////////
            // USERS
            ///////////////////////
            // CREATE
            if (selectedOption == "/Users/create") {
                flashMessage = users.create();
            }
            
            // READ ONE
            if (selectedOption == "/Users/readOne/by id") {
                flashMessage = users.readOneById();
            }
            if (selectedOption == "/Users/readOne/by username") {
                flashMessage = users.readOneByUsername();
            }
            if (selectedOption == "/Users/readOne/by email") {
                flashMessage = users.readOneByEmail();
            }

            // READ ALL
            if (selectedOption == "/Users/readAll/sort by id") {
                flashMessage = users.readAllById();
            }
            if (selectedOption == "/Users/readAll/sort by username") {
                flashMessage = users.readAllByUsername();
            }
            if (selectedOption == "/Users/readAll/sort by email") {
                flashMessage = users.readAllByEmail();
            }

            // UPDATE
            if (selectedOption == "/Users/update/by id") {
                flashMessage = users.updateById();
            }
            if (selectedOption == "/Users/update/by username") {
                flashMessage = users.updateByUsername();
            }
            if (selectedOption == "/Users/update/by email") {
                flashMessage = users.updateByEmail();
            }

            // DELETE
            if (selectedOption == "/Users/delete/by id") {
                flashMessage = users.deleteById();
                posts.readData();
                postsLikes.readData();
                follows.readData();
                messages.readData();
            }
            if (selectedOption == "/Users/delete/by username") {
                flashMessage = users.deleteByUsername();
                posts.readData();
                postsLikes.readData();
                follows.readData();
                messages.readData();
            }
            if (selectedOption == "/Users/delete/by email") {
                flashMessage = users.deleteByEmail();
                posts.readData();
                postsLikes.readData();
                follows.readData();
                messages.readData();
            }

            // SUMMARY
            if (selectedOption == "/Users/summary/get number of users") {
                flashMessage = users.getNumberOfUsers();
            }
            if (selectedOption == "/Users/summary/get number of users with posts more than...") {
                flashMessage = users.getNumberOfUsersWithPosts();
            }
            if (selectedOption == "/Users/summary/get number of users with followers more than...") {
                flashMessage = users.getNumberOfUsersWithFollowers();
            }
            if (selectedOption == "/Users/summary/get number of users with following more than...") {
                flashMessage = users.getNumberOfUsersWithFollowing();
            }

            ///////////////////////
            // POSTS
            ///////////////////////
            // CREATE
            if (selectedOption == "/Posts/create") {
                flashMessage = posts.create();
            }

            // READ ONE
            if (selectedOption == "/Posts/readOne/by id") {
                flashMessage = posts.readOneById();
            }

            // READ ALL
            if (selectedOption == "/Posts/readAll/sort by id") {
                flashMessage = posts.readAllById();
            }
            if (selectedOption == "/Posts/readAll/sort by title") {
                flashMessage = posts.readAllByTitle();
            }
            if (selectedOption == "/Posts/readAll/sort by body") {
                flashMessage = posts.readAllByBody();
            }
            if (selectedOption == "/Posts/readAll/sort by author id") {
                flashMessage = posts.readAllByAuthorId();
            }

            // UPDATE
            if (selectedOption == "/Posts/update/by id") {
                flashMessage = posts.updateById();
            }

            // DELETE ONE
            if (selectedOption == "/Posts/deleteOne/by id") {
                flashMessage = posts.deleteOneById();
                postsLikes.readData();
            }

            // DELETE ALL
            if (selectedOption == "/Posts/deleteAll/by author id") {
                flashMessage = posts.deleteAllByAythorId();
                postsLikes.readData();
            }

            // SUMMARY
            if (selectedOption == "/Posts/summary/get number of posts") {
                flashMessage = posts.getNumberOfPosts();
            }
            if (selectedOption == "/Posts/summary/get number of posts where number of likes is bigger than...") {
                flashMessage = posts.getNumberOfPostsWithLikes();
            }

            ///////////////////////
            // POSTS LIKES
            ///////////////////////
            // CREATE
            if (selectedOption == "/Posts Likes/create") {
                flashMessage = postsLikes.create(); 
            }

            // READ ONE
            if (selectedOption == "/Posts Likes/readOne/by id") {
                flashMessage = postsLikes.readOneById();
            }

            // READ ALL
            if (selectedOption == "/Posts Likes/readAll/sort by id") {
                flashMessage = postsLikes.readAllById();
            }
            if (selectedOption == "/Posts Likes/readAll/sort by post id") {
                flashMessage = postsLikes.readAllByPostId();
            }
            if (selectedOption == "/Posts Likes/readAll/sort by user id") {
                flashMessage = postsLikes.readAllByUserId();
            }

            // DELETE ONE
            if (selectedOption == "/Posts Likes/deleteOne/by id") {
                flashMessage = postsLikes.deleteOneById();
            }

            // DELETE ALL
            if (selectedOption == "/Posts Likes/deleteAll/by post id") {
                flashMessage = postsLikes.deleteAllByPostId();
            }
            if (selectedOption == "/Posts Likes/deleteAll/by user id") {
                flashMessage = postsLikes.deleteAllByUserId();
            }

            // SUMMARY
            if (selectedOption == "/Posts Likes/summary/get number of postsLikes") {
                flashMessage = postsLikes.getNumberOfPostsLikes();
            }

            ///////////////////////
            // FOLLOWS
            ///////////////////////
            // CREATE
            if (selectedOption == "/Follows/create") {
                flashMessage = follows.create();
            }

            // READ ONE
            if (selectedOption == "/Follows/readOne/by id") {
                flashMessage = follows.readOneById();
            }

            // READ ALL
            if (selectedOption == "/Follows/readAll/sort by id") {
                flashMessage = follows.readAllById();
            }
            if (selectedOption == "/Follows/readAll/sort by follower id") {
                flashMessage = follows.readAllByFollowerId();
            }
            if (selectedOption == "/Follows/readAll/sort by following id") {
                flashMessage = follows.readAllByFollowingId();
            }

            // DELETE ONE
            if (selectedOption == "/Follows/deleteOne/by id") {
                flashMessage = follows.deleteOneById();
            }

            // DELETE ALL
            if (selectedOption == "/Follows/deleteAll/by follower id") {
                flashMessage = follows.deleteAllByFollowerId();
            }
            if (selectedOption == "/Follows/deleteAll/by following id") {
                flashMessage = follows.deleteAllByFollowingId();
            }

            // SUMMARY
            if (selectedOption == "/Follows/summary/get number of follows") {
                //TODO: flashMessage = follows.getNumberOfFollows();
            }

            ///////////////////////
            // MESSAGES
            ///////////////////////
            // CREATE
            if (selectedOption == "/Messages/create") {
                flashMessage = messages.create();
            }

            // READ ONE
            if (selectedOption == "/Messages/readOne/by id") {
                flashMessage = messages.readOneById();
            }

            // READ ALL
            if (selectedOption == "/Messages/readAll/sort by id") {
                flashMessage = messages.readAllById();
            }
            if (selectedOption == "/Messages/readAll/sort by from id") {
                flashMessage = messages.readAllByFromId();
            }
            if (selectedOption == "/Messages/readAll/sort by to id") {
                flashMessage = messages.readAllByToId();
            }
            if (selectedOption == "/Messages/readAll/sort by message") {
                flashMessage = messages.readAllByMessages();
            }

            // UPDATE
            if (selectedOption == "/Messages/update/by id") {
                flashMessage = messages.updateById();
            }

            // DELETE ONE
            if (selectedOption == "/Messages/deleteOne/by id") {
                flashMessage = messages.deleteOneById();
            }

            // DELETE ALL
            if (selectedOption == "/Messages/deleteAll/by from id") {
                flashMessage = messages.deleteAllByFromId();
            }
            if (selectedOption == "/Messages/deleteAll/by to id") {
                flashMessage = messages.deleteAllByToId();
            }

            // SUMMARY
            if (selectedOption == "/Messages/summary/get number of messages") {
                //TODO: flashMessage = messages.getNumberOfMessages();
            }
            if (selectedOption == "/Messages/summary/get number of messages sent to yourself") {
                //TODO: flashMessage = messages.getNumberOfMessagesSentYourself();
            }

            ///////////////////////
            // QUIT
            ///////////////////////
            if (selectedOption == "/Quit") break;
        }
    }
    catch (std::exception& e) {
        std::cout << colored(e.what(), "red");
        return;
    }
}