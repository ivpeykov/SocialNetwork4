#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = 999;

const CustomString CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "login", "edit", "edit id", "create", "save", "save as", "search", "open", "post", "list", "exit" };

void CommandsHandler::runCommands(SocialNetwork& currSocialNetwork)
{
    //consider adding failed tries

    //add more commands here
    switch (currCommand) {

    case Load: // bring the input getting and avlidation into the load method
        //BUG: when loading a second time, clear the currentData so it is ready for the new data. Also ask user if he is sure he wants to load new data
       
        ConsoleInputGetter::recieveSocialNetworkDirectoryInput();
        if (!InputValidator::isValidSocialNetworkDirectoryInput(ConsoleInputGetter::getSocialNetworkDirectoryInput())) {

            ConsoleInputGetter::resetSocialNetworkDirectoryInput();

            ConsoleInputGetter::resetCommandInput();
            currCommand = 999;

            return;
        }

        currSocialNetwork.setDirectory(ConsoleInputGetter::getSocialNetworkDirectoryInput());
        FileHandler::loadSocialNetwork(currSocialNetwork);
        break;

    case Signup:
        currSocialNetwork.signup();
        break;

    case Login:
        currSocialNetwork.login();
        break;

    case Edit:
        currSocialNetwork.editLoggedInUser();
        break;
    case EditAsModerator:
        currSocialNetwork.editUserAsModerator();
        break;

    case Create:
        currSocialNetwork.createTopic();
        break;

    case Save:
        FileHandler::saveSocialNetwork(currSocialNetwork);
        break;
    case SaveAs:
        //FileHandler::saveAsSocialNetwork();
        break;

    case Search:
        currSocialNetwork.searchTopic();
        break;

    case Open:
        currSocialNetwork.openTopic();
        break;

    case Post:  
        try {
            currSocialNetwork.postDiscussion(currSocialNetwork.createDiscussion());
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
        break;

    case List:
        currSocialNetwork.listDiscussionsInOpenedTopic();
        break;

    case Exit:
        std::cout << "\nExiting program..." << std::endl; //send to printhandler
        //currSocialNetwork.exitNetwork();

        //Do you wish to exit application? Y/N ?
        //if Y exit(0)
        break;

    case 999:
        std::cerr << "\nCritical Error!\n Exiting..."; //send to printhandlr
        exit(0);
        break;

    default: break;
    }
}

void CommandsHandler::setCurrCommand(unsigned short newCommand) {
    currCommand = newCommand;
}

unsigned short CommandsHandler::getCurrCommand() {
    return currCommand;
}