#include <iostream>
#include "Configuration.h"
#include "CommandsHandler.h"
#include "PrintHandler.h"

int main(){

	while (CommandsHandler::getCurrCommand() != Command::Exit) {
		PrintHandler::printEnterCommandPrompt();
		CommandsHandler::runCommands();
	}


	PrintHandler::printCurrUsers(); //remove


	return 0;
}
