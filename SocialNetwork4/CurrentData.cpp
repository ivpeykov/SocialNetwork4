#include "CurrentData.h"

SocialNetwork CurrentData::currSocialNetwork(nullptr);

bool CurrentData::changesMade = false;

SocialNetwork& CurrentData::getCurrSocialNetwork()
{
    return currSocialNetwork;
}

bool CurrentData::getChangesMadeStatus()
{
	return changesMade;
}

void CurrentData::setCurrSocialNetwork(const SocialNetwork& newSocialNetwork)
{
    currSocialNetwork = newSocialNetwork;
}

void CurrentData::setChangesMadeStatus(const bool newStatus)
{
	changesMade = newStatus;
}


bool CurrentData::doesUsernameExist(const CustomString& userName)
{
	size_t usersSize = currSocialNetwork.getCurrUsers().getSize();

	for (int i = 0; i < usersSize; i++) {
		if (userName == currSocialNetwork.getCurrUsers()[i].getUserName())
			return true;
	}
	return false;
}
