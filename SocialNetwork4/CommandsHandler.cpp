#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = Undefined;

const String CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "login", "logout", "edit", "edit id", "create", "save", "save as", "search", 
"open", "post", "list", "post_open", "comment", "reply", "help", "exit" }; //TODO: change order to be more grouped

const String CommandsHandler::commandsDescriptions[CommandsCount] = { "Load data from file into the program" , "Sign user up", "Log user in",
"Log user out", "Edit user data", "Edit selected user data",
"Create a topic", "Save data" , "Save data as",
"Search for a topic by title", "Open a topic", "Post a discussion",
"List posted discussions in a topic", "Open a discussion", "Comment on a discussion",
"Reply to a comment in a discussion", "List available commands", "Exit from program" };

bool CommandsHandler::networkLoaded = false;

void CommandsHandler::runCommands(SocialNetwork& currSocialNetwork) //TODO :: ADD exception handling for all commands
{
    //consider adding failed tries

    //add more commands here
    switch (currCommand) {

    case Load:

        if (networkLoaded) { //TODO: Extract this into its own method
            std::cout << "Network already loaded! Please restart program and load again!"
                << std::endl;
            return;
        }
      
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
        try {
            currSocialNetwork.addTopic(ObjectFactory::createTopic(currSocialNetwork));
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
        break;

    case Save:
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
            currSocialNetwork.postDiscussion(ObjectFactory::createDiscussion(currSocialNetwork));
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

    case AddComment:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }

        try {
            currSocialNetwork.addComment(ObjectFactory::createComment(currSocialNetwork));
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
        break;

    case ReplyToComment:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
            
        try { 
            currSocialNetwork.replyToComment(ConsoleInputGetter::recieveIdInputForCommentReply());
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Could not reply! " << error.what() << std::endl;
        }
        catch (std::exception error) {
            std::cerr << "Could not reply! " << error.what() << std::endl;
        }
        break;

    case Help:
        PrintHandler::printCommands(commandsList, CommandsHandler::commandsDescriptions, CommandsCount);
        break;

    case Exit: //TODO: all changes must be saved!
        std::cout << "\nExiting program..." << std::endl; //send to printhandler
        //currSocialNetwork.exitNetwork();

        //Do you wish to exit application? Y/N ?
        //if Y exit(0)
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