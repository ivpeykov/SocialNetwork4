#pragma once
#include "ConsoleInputGetter.h"
#include "InputValidator.h"
#include "FileHandler.h"
#include "SocialNetwork.h"

enum Command { //don't change order!

	Load = 0,
	Signup = 1,
	Save = 2,
	SaveAs = 3,
	Exit = 4,

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