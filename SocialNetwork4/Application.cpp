#include "Application.h"

Application& Application::getInstance()
{
	static Application instance;
	return instance;
}

void Application::run()
{
	//big optimisation: instead of searching for user,topic,post, position, keep the opened positions as variables and directly use them, update them when they change.

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

	/*
	std::cout << "Opened Topic: " << std::endl;
	PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	std::cout << "Opened Post: " << std::endl;
	PrintHandler::printPost(CurrentData::getCurrSocialNetwork().getOpenedPost());

	std::cout << "Logged in user: " << std::endl;
	PrintHandler::printUser(CurrentData::getCurrSocialNetwork().getLoggedInUser());
	*/
}

Application::Application() {}
