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
	static void printTopic(Topic& topic);
	static void printDiscussion(Discussion& discussion);
	static void printComment(Comment& comment);

	static void printCurrUsers();
	static void printCurrTopics();
	static void printDiscussions(Topic& topic);
	static void printComments(Discussion& discussion);

	static void printErrorSignupFirstName();
	static void printErrorSignupLastName();
	static void printErrorSignupUserName();
	static void printErrorSignupPassword();

};