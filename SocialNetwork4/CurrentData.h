#pragma once
#include "SocialNetwork.h"

//class User;
//class Topic;
//class Post;
//class Comment;
class SocialNetwork;

class CurrentData
{

public:

	static SocialNetwork& getCurrSocialNetwork();
	static bool getChangesMadeStatus();

	static void setCurrSocialNetwork(const SocialNetwork& newSocialNetwork);
	static void setChangesMadeStatus(const bool newStatus);

private:

	CurrentData();

	static SocialNetwork currSocialNetwork;
	static bool changesMade;

};