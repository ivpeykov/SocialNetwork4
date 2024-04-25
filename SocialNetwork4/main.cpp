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


	//PrintHandler::printCurrUsers(); //remove

	PrintHandler::printCurrTopics();


	return 0;
}
