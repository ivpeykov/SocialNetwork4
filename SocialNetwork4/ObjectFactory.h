#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "Topic.h"

class SocialNetwork;

class ObjectFactory
{
public:

	static Topic createTopic(const SocialNetwork& socialNetwork);

private:
	ObjectFactory();
};

