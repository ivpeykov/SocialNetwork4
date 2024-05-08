#pragma once
#include "User.h"
#include "Topic.h"
#include "Discussion.h"
#include "Comment.h"
#include "CurrentData.h"

class PrintHandler
{
public:

	//TODO :: Add exception handling for everything that tries to print nullptr

	static void printEnterCommandPrompt();

	static void printUser(const User& user);
	static void printTopic(const Topic& topic);
	static void printDiscussion(const Discussion& discussion);
	static void printComment(const Comment& comment);

	static void printUsers(const Vector<User>& users);
	static void printTopics(const Vector<Topic>& topics);
	static void printDiscussions(const Topic& topic);
	static void printComments(const Discussion& discussion);

	static void printTopicsForSearch(const Vector<Topic>& topics);
	static void printDiscussionsForList(const Vector<Discussion>& discussions);

	//Errors
	static void printErrorSignupFirstName();
	static void printErrorSignupLastName();
	static void printErrorSignupUserName();
	static void printErrorSignupPassword();

	static void printErrorLoginUserName();
	static void printErrorLoginPassword();

	static void printErrorCreateTitleTopic();
	static void printErrorCreateDescriptionTopic();

	static void printErrorCreateTitleDiscussion();
	static void printErrorCreateDescriptionDiscussion();
};