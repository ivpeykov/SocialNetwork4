#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "FileHandler.h"
#include "SocialNetwork.h"
#include "ObjectFactory.h"

enum Command { //don't change order!

	Load,
	Signup,
	Login,
	Logout,
	Edit,
	EditAsModerator,
	Create,
	Save,
	SaveAs,
	Search,
	Open,
	Post,
	List,
	PostOpen,
	AddComment,
	ReplyToComment,
	QuitDiscussion,
	Help,
	Exit,
	CommandsCount,

	Undefined = 999
};

class SocialNetwork;

class CommandsHandler
{
public:
	static void runCommands(SocialNetwork& currSocialNetwork);

	static void setCurrCommand(unsigned short newCommand);

	static unsigned short getCurrCommand();

	static const String commandsList[CommandsCount];

	static const String commandsDescriptions[CommandsCount];

	static bool networkLoaded;

private:

	CommandsHandler();

	static unsigned short currCommand;
};