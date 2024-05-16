#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"
#include "Discussion.h"

class SocialNetwork
{
public:

	SocialNetwork(CustomString& directory);
	SocialNetwork(const char* directory);

	const CustomString& getDirectory() const;
	Vector<User>& getCurrUsers();
	const Vector<User>& getCurrUsers() const;
	Vector<Topic>& getCurrTopics();
	const Vector<Topic>& getCurrTopics() const;

	const User& getLoggedInUser() const;
	const Topic& getOpenedTopic() const;
	const Discussion& getOpenedDiscussion() const;

	void setDirectory(const CustomString& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);
	void setLoggedInUser(const User& newUser);
	void setOpenedTopic(const Topic& newTopic);

	bool isThereLoggedInUser() const;
	bool isThereOpenedTopic() const;
	bool isThereOpenedDiscussion() const;

	bool isLoginSuccessful(User& user);

	size_t doesUsernameExist(const CustomString& userName);
	size_t doesCommentExist(const size_t id, const Vector<Comment>& comments);

	SocialNetwork& operator=(const SocialNetwork& other);

	void signup();

	void login();

	void logout();

	void editLoggedInUser();

	void editUserAsModerator();

	void addTopic(const Topic& newTopic);

	void searchTopic();

	void openTopic();

	void postDiscussion(const Discussion& newDiscussion); //can use move semantics here

	void listDiscussionsInOpenedTopic();

	void openDiscussion();

	void addComment(const Comment& newComment); //can use move semantics here

	void replyToComment(const size_t parentId);
	//add other commands down here....

private:
	CustomString directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
	static Discussion openedDiscussion;
};