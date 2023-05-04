# MENU

`>` means that you can select it with arrows

`...` means input

```
> Create DB
	Title: ...
> Select DB
	> Instagram
		> Users
			> ReadOne
				> by id
					<< id; username; password; email; followers count; following count; post count
				> by username
				> by email
			> u.t.c.
		> Posts
		> Post Likes
		> Messages
		> Follows
	> Facebook
	> u.t.c
	> Go back
> Delete DB
	> Instagram
		> I want to delete db Instagram
			To confirm that you want to delete it, type "Instagram": ...
		> Go back
	> Facebook
	> u.t.c
	> Go back
> Quit
```

# DB

Gona create folder of database

```
Tables:
	User
	Posts
	PostsLikes
	Follows
	Messages
Methods:
	createDB(title)
	deleteDB(title)
```

# USER

```
Fields:
	userID - unique
	username - unique
	password
	email - unique
	?time
```

```
Methods:
	create (username, password, email)
	readOne (userID || username || email)
	readAll (null || userID || username || email)
	update (userID || username || email, username || password || email)
	delete (userID || username || email)
```

`create()` Creates the user.

`readOne()` Read one user by `userID || username || email`.

`readAll()` Read all users, and sort by `null || userID || username || email`.

`update()` Select one user by `userID || username || email` and update `username || password || email` field.

`delete()` Delete one user by `userID || username || email`.

# POSTS

```
Fields:
	postID - unique
	title
	body
	author ~ USER.userID
	?time
```

```
Methods:
	create (title, body, author)
	readOne (postID)
	readAll (null || postID || title || body || author)
	readMany (title || body || author)
	update (postID, title || body || author)
	delete (postID)
```

`create()` Creates the post.

`readOne()` Read one post by `postID`.

`readAll()` Read all posts, and sort by `null || postID || title || body || author`.

`readMany()` Read many posts, and sort by `title || body || author`.

`update()` Select one post by `postID` and update `username || password || email` field.

`delete()` Delete one post by `postID`.

# POSTS LIKES

```
Fields:
	postLikeID
	postID ~ POST.postID
	userID ~ USER.userID
```

# FOLLOWS

```
Fields:
	followID
	followerID ~ USER.userID
	followingID ~ USER.userID
	?time
```

`followerID` is following `followingID`.

# MESSAGES

```
Fields:
	messageID
	fromID ~ USER.userID
	toID ~ USER.userID
	message
	?time
```
