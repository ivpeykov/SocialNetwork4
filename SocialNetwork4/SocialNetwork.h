#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"


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

	void setDirectory(const CustomString& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);
	static void setLoggedInUser(const User& newUser);
	static void setOpenedTopic(const Topic& newTopic);


	SocialNetwork& operator=(const SocialNetwork& other);

	void signup();

	void login();

	void editLoggedInUser();

	void createTopic();

	void searchTopic();

	void openTopic();

	Discussion createDiscussion();

	void postDiscussion(const Discussion& newDiscussion); //can use move semantics here

	void listDiscussionsInOpenedTopic();

	//add other commands down here....

private:
	CustomString directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
};