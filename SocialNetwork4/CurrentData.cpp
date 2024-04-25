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

bool CurrentData::isLoginSuccessful(User& user)
{
	size_t currUsersSize = currSocialNetwork.getCurrUsers().getSize();

	for (int i = 0; i < currUsersSize; i++) {

		User currUser = currSocialNetwork.getCurrUsers()[i];

		if (user.getUserName() == currUser.getUserName()
			&& user.getPassword() == currUser.getPassword()) {
			user = currUser;
			return true;
		}
	}
	return false;
}
