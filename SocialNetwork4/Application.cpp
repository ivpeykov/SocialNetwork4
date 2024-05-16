#include "Application.h"

void Application::run()
{

	//MAJOR BUG: Discussions, Comments, Replies are transferring between topics! After replying i think
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

	//PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove


	//std::cout << "Opened Topic: " << std::endl;
	//PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	//std::cout << "Opened Discussion: " << std::endl;
	//PrintHandler::printDiscussion(CurrentData::getCurrSocialNetwork().getOpenedDiscussion());
}
