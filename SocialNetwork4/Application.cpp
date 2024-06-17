#include "Application.h"

Application& Application::getInstance()
{
	static Application instance;
	return instance;
}

void Application::run()
{
	PrintHandler::printCommands(CommandsHandler::commandsList, CommandsHandler::commandsDescriptions, CommandsCount);

	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();

		ConsoleInputGetter::recieveCommandInput();
		if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
			ConsoleInputGetter::resetCommandInput();
			CommandsHandler::setCurrCommand(Undefined);
		}
		CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork());
	}


	//Debugging prints...


	PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove
	
}

Application::Application() {}
