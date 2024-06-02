#pragma once
#include "String.h"
#include "Configuration.h"
#include "InputValidator.h"
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
	static void recieveAnswerInputForEditing(short& answer, const short optionsCount);
	static void recieveIdInputForEditUserAsModerator(size_t& id);
	static void recieveModeratorStatusInputForEditUserAsModerator(bool& newModeratorStatus); //TODO: change this method's name

	//Recieve Topic Input data
	static void recieveTitleInput(Topic& newTopic);
	static void recieveDescriptionInput(Topic& newTopic);

	//Recieve Post Input data
	static void recievePostTitleInput(Post& newPost);
	static void recievePostContentInput(Post& newPost);

	//Recieve Comment Input data
	static void recieveCommentTextInput(Comment& newComment);
	static size_t recieveIdInput();

	static String& getSocialNetworkDirectoryInput();

	static String& getCommandInput();

	static void resetCommandInput();

	static void resetSocialNetworkDirectoryInput();

private:

	ConsoleInputGetter();

	static String commandInput;
	static String socialNetworkDirectoryInput;
};

