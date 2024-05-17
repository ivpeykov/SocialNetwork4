#pragma once
#include "User.h"
#include "Topic.h"
#include "Post.h"
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
	static void printPost(const Post& post);
	static void printComment(const Comment& comment);
	static void printReply(const Reply& reply);

	static void printUsers(const Vector<User>& users);
	static void printTopics(const Vector<Topic>& topics);
	static void printPosts(const Topic& topic);
	static void printComments(const Post& post);
	static void printReplies(const Comment& comment);

	static void printTopicsForSearch(const Vector<Topic>& topics);
	static void printPostsForList(const Vector<Post>& posts);

private:
	PrintHandler();
};