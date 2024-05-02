#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "FileHandler.h"
#include "SocialNetwork.h"

enum Command { //don't change order!

	Load,
	Signup,
	Login,
	Create,
	Save,
	SaveAs,
	Search,
	Open,
	Post,
	List,
	Exit,

	CommandsCount
};

class SocialNetwork;

class CommandsHandler
{
public:
	static void runCommands(SocialNetwork& currSocialNetwork);

	static void setCurrCommand(unsigned short newCommand);

	static unsigned short getCurrCommand();

	static const CustomString commandsList[CommandsCount];

private:
	static unsigned short currCommand;
};