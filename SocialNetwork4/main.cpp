#include <iostream>
#include "Configuration.h"
#include "CommandsHandler.h"
#include "PrintHandler.h"

int main(){
	
	//Ensure a social network is loaded manually by user first !!!!

	//BUG: spamming enter leads to unexpected call command signup

	while (CommandsHandler::getCurrCommand() != Command::Load) {
		PrintHandler::printEnterCommandPrompt();

		ConsoleInputGetter::recieveCommandInput();
		if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
			ConsoleInputGetter::resetCommandInput();
		}

		if (CommandsHandler::getCurrCommand() == Load) {
			CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork()); //change to FileHandler::load() after fixing methods
			CommandsHandler::setCurrCommand(999);
			break;
		}

		else {
			std::cout << "Please load a Social Network first!" << std::endl;
		} 
	}

	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();

		ConsoleInputGetter::recieveCommandInput();
		if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
			ConsoleInputGetter::resetCommandInput();
		}
		else {
			CommandsHandler::runCommands(CurrentData::getCurrSocialNetwork());
		}
	}

	PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove


	//std::cout << "Opened Topic: " << std::endl;
	//PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	return 0;
}
