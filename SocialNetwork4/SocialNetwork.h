#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"

class SocialNetwork
{
public:

	SocialNetwork(String& directory);
	SocialNetwork(const char* directory);

	const String& getDirectory() const;
	Vector<User>& getCurrUsers();
	const Vector<User>& getCurrUsers() const;
	Vector<Topic>& getCurrTopics();
	const Vector<Topic>& getCurrTopics() const;

	static User& getLoggedInUser();
	static Topic& getOpenedTopic();
	static Post& getOpenedPost();

	void setDirectory(const String& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);

	static void setLoggedInUser(const User& newUser);
	static void setOpenedTopic(const Topic& newTopic);
	static void setOpenedPost(const Post& newPost);

	static bool isThereLoggedInUser();
	static bool isThereOpenedTopic();
	static bool isThereOpenedPost();

	bool isLoginSuccessful(User& user);

	size_t doesUsernameExist(const String& userName) const;
	size_t doesCommentExist(const size_t id, const Vector<Comment>& comments) const;

	SocialNetwork& operator=(const SocialNetwork& other);

	void signup(const User& newUser);

	void login();

	void logout();

	void editLoggedInUser();

	void editUserAsModerator();

	void addTopic(const Topic& newTopic);

	void searchTopic();

	void openTopic();

	void addPost(const Post& newPost); //can use move semantics here

	void listPostsInOpenedTopic() const;

	void openPost();

	void addComment(const Comment& newComment); //can use move semantics here

	void replyToComment(const size_t parentId);

	void quitOpenedPost();

	void quitOpenedTopic();
	//add other commands down here....

private:
	String directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
	static Post openedPost;
};