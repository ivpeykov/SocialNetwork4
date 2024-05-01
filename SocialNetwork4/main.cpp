#include <iostream>
#include "Configuration.h"
#include "CommandsHandler.h"
#include "PrintHandler.h"

int main(){
	
	//Ensure a social network is loaded manually by user first !!!!
	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();
		CommandsHandler::runCommands();
	}

	//PrintHandler::printUsers(CurrentData::getCurrSocialNetwork().getCurrUsers()); //remove

	//PrintHandler::printTopics(CurrentData::getCurrSocialNetwork().getCurrTopics()); //remove


	std::cout << "Opened Topic: " << std::endl;
	PrintHandler::printTopic(CurrentData::getCurrSocialNetwork().getOpenedTopic());

	return 0;
}
