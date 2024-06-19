#include "Application.h"

Application& Application::getInstance()
{
	static Application instance;
	return instance;
}

void Application::run()
{
	try {
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
	}
	catch (const std::bad_alloc& e) {
		std::cout << "Critical error! " << std::endl << "Memory allocation fail! Saving and terminating program...." << std::endl;
		FileHandler::saveSocialNetworkPostCriticalError(e, CurrentData::getCurrSocialNetwork());
		exit(0);
	}
}

Application::Application() {}
