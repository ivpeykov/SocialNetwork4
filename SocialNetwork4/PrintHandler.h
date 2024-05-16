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
	static void printCommands(const String* commandsList, const String* commandsDescriptions, const size_t commandsCount);

	static void printUser(const User& user);
	static void printTopic(const Topic& topic);
	static void printDiscussion(const Discussion& discussion);
	static void printComment(const Comment& comment);
	static void printReply(const Reply& reply);

	static void printUsers(const Vector<User>& users);
	static void printTopics(const Vector<Topic>& topics);
	static void printDiscussions(const Topic& topic);
	static void printComments(const Discussion& discussion);
	static void printReplies(const Comment& comment);

	static void printTopicsForSearch(const Vector<Topic>& topics);
	static void printDiscussionsForList(const Vector<Discussion>& discussions);

private:
	PrintHandler();
};