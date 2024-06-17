#pragma once
#include "SocialNetwork.h"
#include "ObjectFactory.h"
#include "FileHandler.h"
//Adjust COMMAND_INPUT_MAX_LENGTH in Configuration.h if adding longer commands.

enum Command { //Don't change order!

	Load,
	Signup,
	Login,
	Logout,
	Edit,
	EditAsModerator,
	Create,
	Search,
	Open,
	AddPost,
	List,
	PostOpen,
	PrintPostComments,
	AddComment,
	ReplyToComment,
	Upvote,
	Downvote,
	DeleteComment,
	DeletePost,
	DeleteTopic,
	QuitPost,
	QuitTopic,
	Help,
	Save,
	SaveAs,
	Exit,
	CommandsCount,

	Undefined = 999
};

class CommandsHandler
{
public:

	static void runCommands(SocialNetwork& currSocialNetwork);

	static void setCurrCommand(unsigned short newCommand);

	static unsigned short getCurrCommand();

	static const String commandsList[CommandsCount];

	static const String commandsDescriptions[CommandsCount];

private:
	CommandsHandler();

	static unsigned short currCommand;

	static bool networkLoaded;
};

