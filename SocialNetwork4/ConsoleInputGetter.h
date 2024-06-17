#pragma once
#include "String.h"
#include "Configuration.h"
#include "InputValidator.h"

class ConsoleInputGetter
{
public:

	//getters
	static String& getSocialNetworkDirectoryInput();
	static String& getCommandInput();

	//methods
	static void resetCommandInput();
	static void resetSocialNetworkDirectoryInput();

	static bool isBufferOverfilled();

	static void flushInputBuffer();

	static void recieveCommandInput();

	static String recieveSocialNetworkDirectoryInput();

	//Recieve User Input data
	static void recieveFirstNameInput(String& firstName);
	static void recieveLastNameInput(String& lastName);
	static void recieveUserNameInput(String& userName);
	static void recievePasswordInput(String& password);
	static void recieveAnswerInputForEditing(short& answer, const short optionsCount);
	static size_t recieveIdInput();
	static void recieveModeratorStatusInput(bool& newModeratorStatus);

	//Recieve Topic Input data
	static void recieveTitleInput(String& title);
	static void recieveDescriptionInput(String& description);

	//Recieve Post Input data
	static void recievePostTitleInput(String& title);
	static void recievePostContentInput(String& content);

	//Recieve Comment Input data
	static void recieveCommentTextInput(String& text);

	static bool getExitSavingAnswer();

private:

	ConsoleInputGetter();

	static String commandInput;
	static String socialNetworkDirectoryInput;

};

