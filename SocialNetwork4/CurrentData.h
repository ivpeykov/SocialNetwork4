#pragma once
#include "SocialNetwork.h"

class User;
class Topic;
class Discussion;
class Comment;
class SocialNetwork;

class CurrentData
{

public:

	static SocialNetwork& getCurrSocialNetwork();
	static bool getChangesMadeStatus();

	static void setCurrSocialNetwork(const SocialNetwork& newSocialNetwork);
	static void setChangesMadeStatus(const bool newStatus);

	static bool doesUsernameExist(const CustomString& userName); // TODO : consider moving to socialNetwork
	static bool isLoginSuccessful(User& user); //TODO :  consider moving this to socialNetwork

private:

	static SocialNetwork currSocialNetwork;
	static bool changesMade;

};

