#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = 999;

const CustomString CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "save", "save as", "exit" };

void CommandsHandler::runCommands()
{
    //consider adding failed tries

    ConsoleInputGetter::recieveCommandInput();
    if (!InputValidator::isValidCommandInput(ConsoleInputGetter::getCommandInput())) {
        ConsoleInputGetter::resetCommandInput();

        return;
    }

    //add more commands here
    switch (currCommand) {

    case Load:
       
        ConsoleInputGetter::recieveSocialNetworkDirectoryInput();
        if (!InputValidator::isValidSocialNetworkDirectoryInput(ConsoleInputGetter::getSocialNetworkDirectoryInput())) {

            ConsoleInputGetter::resetSocialNetworkDirectoryInput();

            ConsoleInputGetter::resetCommandInput();
            currCommand = 999;

            return;
        }

        CurrentData::getCurrSocialNetwork().setDirectory(ConsoleInputGetter::getSocialNetworkDirectoryInput());
        FileHandler::loadSocialNetwork(CurrentData::getCurrSocialNetwork().getDirectory());
        break;

    case Signup:
        SocialNetwork::signup();
        break;

    case Save:
        FileHandler::saveSocialNetwork();
        break;
    case SaveAs:
        //FileHandler::saveAsSocialNetwork();
        break;

    case Exit:
        std::cout << "\nExiting program..."; //send to printhandler
        //SocialNetwork::exitNetwork();

        //Do you wish to exit application? Y/N ?
        //if Y exit(0)
        break;

    case 999:
        std::cout << "\nCritical Error!\n Exiting..."; //send to printhandlr
        exit(0);

    default: break;
    }
}

void CommandsHandler::setCurrCommand(unsigned short newCommand) {
    currCommand = newCommand;
}

unsigned short CommandsHandler::getCurrCommand() {
    return currCommand;
}