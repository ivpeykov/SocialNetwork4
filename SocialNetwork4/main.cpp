#include <iostream>
#include "Configuration.h"
#include "CommandsHandler.h"
#include "PrintHandler.h"

int main(){

	bool networkLoaded = false;
	PrintHandler::printCommands(CommandsHandler::commandsList, CommandsCount);

	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();

		ConsoleInputGetter::recieveCommandInput();
		if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
			ConsoleInputGetter::resetCommandInput();
		}

		else if (CommandsHandler::getCurrCommand() == Help) {
			PrintHandler::printCommands(CommandsHandler::commandsList, CommandsCount);
		}
	
		else if (CommandsHandler::getCurrCommand() == Load){

			if (networkLoaded) {
				std::cout << "Network already loaded! Please restart program and load again!"
					<< std::endl;
				continue;
			}

			CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork());
			networkLoaded = true;
		}

		else if (CommandsHandler::getCurrCommand() != Load && networkLoaded) {
			CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork());
		}

		else if (CommandsHandler::getCurrCommand() != Exit){
			std::cout << "Please load a Social Network first!" << std::endl;
		}

	}

	PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove


	std::cout << "Opened Topic: " << std::endl;
	PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	std::cout << "Opened Discussion: " << std::endl;
	PrintHandler::printDiscussion(CurrentData::getCurrSocialNetwork().getOpenedDiscussion());

	return 0;
}
