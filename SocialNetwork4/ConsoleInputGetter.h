#pragma once
#include "CustomString.h"
#include "Configuration.h"
#include "User.h"
#include "Topic.h"

class ConsoleInputGetter
{
public:
	static bool isBufferOverfilled();

	static void flushInputBuffer();

	static void recieveCommandInput();

	static void recieveSocialNetworkDirectoryInput();

	//Recieve User Input data
	static void recieveFirstNameInput(User& newUser);
	static void recieveLastNameInput(User& newUser);
	static void recieveUserNameInput(User& newUser);
	static void recievePasswordInput(User& newUser);
	static void recieveAnswerInputForEditing(short& answer);
	static void recieveIdInputForEditUserAsModerator(size_t& id);
	static void recieveModeratorStatusInputForEditUserAsModerator(bool& newModeratorStatus);

	//Recieve Topic Input data
	static void recieveTitleInput(Topic& newTopic);
	static void recieveDescriptionInput(Topic& newTopic);

	//Recieve Discussion Input data
	static void recieveTitleInput(Discussion& newDiscussion);
	static void recieveDescriptionInput(Discussion& newDiscussion);

	//Recieve Comment Input data
	//.....

	static CustomString& getSocialNetworkDirectoryInput();

	static CustomString& getCommandInput();

	static void resetCommandInput();

	static void resetSocialNetworkDirectoryInput();

private:
	static CustomString commandInput;
	static CustomString socialNetworkDirectoryInput;
};

