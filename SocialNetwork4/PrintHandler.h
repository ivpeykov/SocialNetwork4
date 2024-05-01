#pragma once
#include "User.h"
#include "Topic.h"
#include "Discussion.h"
#include "Comment.h"
#include "CurrentData.h"

class PrintHandler
{
public:

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

	//Errors
	static void printErrorSignupFirstName();
	static void printErrorSignupLastName();
	static void printErrorSignupUserName();
	static void printErrorSignupPassword();

	static void printErrorLoginUserName();
	static void printErrorLoginPassword();

	static void printErrorCreateTitle();
	static void printErrorCreateDescription();
};