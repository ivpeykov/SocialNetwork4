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

	static User& getLoggedInUser();
	static Topic& getOpenedTopic();
	static Discussion& getOpenedDiscussion();

	void setDirectory(const CustomString& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);
	static void setLoggedInUser(const User& newUser);
	static void setOpenedTopic(const Topic& newTopic);

	static bool isThereLoggedInUser();
	static bool isThereOpenedTopic();
	static bool isThereOpenedDiscussion();

	bool isLoginSuccessful(User& user);

	bool doesUsernameExist(const CustomString& userName);
	bool doesCommentExist(const size_t id, const Vector<Comment>& comments);

	SocialNetwork& operator=(const SocialNetwork& other);

	void signup();

	void login();

	void logout();

	void editLoggedInUser();

	void editUserAsModerator();

	Topic createTopic();

	void addTopic(const Topic& newTopic);

	void searchTopic();

	void openTopic();

	Discussion createDiscussion();

	void postDiscussion(const Discussion& newDiscussion); //can use move semantics here

	void listDiscussionsInOpenedTopic();

	void openDiscussion();

	Comment createComment();

	void addComment(const Comment& newComment); //can use move semantics here

	void replyToComment();

	//add other commands down here....

private:
	CustomString directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
	static Discussion openedDiscussion;
};