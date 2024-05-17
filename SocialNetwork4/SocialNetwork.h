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

	const User& getLoggedInUser() const;
	const Topic& getOpenedTopic() const;
	const Post& getOpenedPost() const;

	void setDirectory(const String& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);
	void setLoggedInUser(const User& newUser);
	void setOpenedTopic(const Topic& newTopic);

	bool isThereLoggedInUser() const;
	bool isThereOpenedTopic() const;
	bool isThereOpenedPost() const;

	bool isLoginSuccessful(User& user);

	size_t doesUsernameExist(const String& userName) const;
	size_t doesCommentExist(const size_t id, const Vector<Comment>& comments) const;

	SocialNetwork& operator=(const SocialNetwork& other);

	void signup();

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
	//add other commands down here....

private:
	String directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
	static Post openedPost;
};