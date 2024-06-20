#pragma once
#include "String.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "Comment.h"

class PrintHandler
{
public:
	static void printEnterCommandPrompt();
	static void printCommands(const String* commandsList, const String* commandsDescriptions, const size_t commandsCount);

	static void safePrint(const char* label, const String& value);
	static void printUser(const User& user);
	static void printTopic(const Topic& topic);
	static void printPost(const Post& post);
	static void printComment(const Comment& comment);
	static void printReply(const Reply& reply);

	static void printUsers(const Vector<User>& users);
	static void printTopics(const Vector<Topic>& topics);
	static void printPosts(const Vector<Post>& posts);
	static void printComments(const Vector<Comment>& comments);
	static void printReplies(const Vector<Reply>& replies);

	static void printTopicsForSearch(const Vector<Topic>& topics);
	static void printPostsForList(const Vector<Post>& posts);

private:
	PrintHandler();
};

