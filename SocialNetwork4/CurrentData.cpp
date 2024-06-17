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
