#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = 999;

const CustomString CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "login","logout", "edit", "edit id", "create", "save", "save as", "search", "open", "post", "list", "post_open", "help", "exit" };

bool CommandsHandler::networkLoaded = false;

void CommandsHandler::runCommands(SocialNetwork& currSocialNetwork)
{
    //consider adding failed tries

    //add more commands here
    switch (currCommand) {

    case Load:

        if (networkLoaded) {
            std::cout << "Network already loaded! Please restart program and load again!"
                << std::endl;
            return;
        }
      
        ConsoleInputGetter::recieveSocialNetworkDirectoryInput();
        if (!InputValidator::isValidSocialNetworkDirectoryInput(ConsoleInputGetter::getSocialNetworkDirectoryInput())) {

            ConsoleInputGetter::resetSocialNetworkDirectoryInput();

            ConsoleInputGetter::resetCommandInput();
            currCommand = 999;

            return;
        }

        currSocialNetwork.setDirectory(ConsoleInputGetter::getSocialNetworkDirectoryInput());
        FileHandler::loadSocialNetwork(currSocialNetwork, networkLoaded);
        break;

    case Signup:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.signup();
        break;

    case Login:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.login();
        break;

    case Logout:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.logout();
        break;

    case Edit:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.editLoggedInUser();
        break;

    case EditAsModerator:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.editUserAsModerator();
        break;

    case Create:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.createTopic();
        break;

    case Save: //TODO: print saved successfully message
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        FileHandler::saveSocialNetwork(currSocialNetwork);
        break;
    case SaveAs: //TODO: print saved successfully message
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        //FileHandler::saveAsSocialNetwork();
        break;

    case Search:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.searchTopic();

        break;

    case Open:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.openTopic();
        break;

    case Post:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        try {
            currSocialNetwork.postDiscussion(currSocialNetwork.createDiscussion());
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
        break;

    case List:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.listDiscussionsInOpenedTopic();
        break;

    case PostOpen:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.openDiscussion();
        break;

    case Help:
        PrintHandler::printCommands(commandsList, CommandsCount);
        break;

    case Exit: //TODO: all changes must be saved!
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