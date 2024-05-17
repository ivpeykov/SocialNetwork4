#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "Topic.h"

class SocialNetwork;

class ObjectFactory
{
public:

	static Topic createTopic(const SocialNetwork& socialNetwork);

	static Post createPost(const SocialNetwork& socialNetwork);

	static Comment createComment(const SocialNetwork& socialNetwork);

	static Reply createReply(const SocialNetwork& socialNetwork, const Reply& parentCommentLastReply, const size_t parentCommentId);

private:
	ObjectFactory();
};

