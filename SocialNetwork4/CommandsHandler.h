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
	List,
	Exit,

	CommandsCount
};

class CommandsHandler
{
public:
	static void runCommands();

	static void setCurrCommand(unsigned short newCommand);

	static unsigned short getCurrCommand();

	static const CustomString commandsList[CommandsCount];

private:
	static unsigned short currCommand;
};