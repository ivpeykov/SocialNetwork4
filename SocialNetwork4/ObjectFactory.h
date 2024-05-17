#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "Topic.h"

class SocialNetwork;

class ObjectFactory
{
public:
	static size_t getLastSignedUpUserId();
	static size_t getLastCreatedTopicId();

	static void setLastSignedUpUserId(const size_t newId);
	static void setLastCreatedTopicId(const size_t newId);

	static User createUser(const SocialNetwork& socialNetwork);

	static Topic createTopic(const SocialNetwork& socialNetwork);

	static Post createPost(const SocialNetwork& socialNetwork);

	static Comment createComment(const SocialNetwork& socialNetwork);

	static Reply createReply(const SocialNetwork& socialNetwork, const Reply& parentCommentLastReply, const size_t parentCommentId);

private:
	ObjectFactory();

	static size_t lastSignedUpUserId;
	static size_t lastCreatedTopicId;
};

