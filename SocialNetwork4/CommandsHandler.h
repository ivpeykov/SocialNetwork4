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

	static const CustomString commandsList[CommandsCount];

	static const CustomString commandsDescriptions[CommandsCount];

	static bool networkLoaded;

private:

	CommandsHandler();

	static unsigned short currCommand;
};