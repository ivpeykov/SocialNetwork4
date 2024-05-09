#include <iostream>
#include "Configuration.h"
#include "CommandsHandler.h"
#include "PrintHandler.h"

int main(){

	PrintHandler::printCommands(CommandsHandler::commandsList, CommandsCount);

	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();

		ConsoleInputGetter::recieveCommandInput();
		if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
			ConsoleInputGetter::resetCommandInput();
		}
		CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork());
	}

	PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove


	//std::cout << "Opened Topic: " << std::endl;
	//PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	//std::cout << "Opened Discussion: " << std::endl;
	//PrintHandler::printDiscussion(CurrentData::getCurrSocialNetwork().getOpenedDiscussion());

	return 0;
}
