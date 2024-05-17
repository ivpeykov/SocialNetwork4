#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = Undefined;

//Adjust COMMAND_INPUT_MAX_LENGTH in Configuration.h if adding longer commands.
const String CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "login", "logout", "edit", "edit id", "create", "save", "save as", "search", 
"open", "post", "list", "post_open", "comment", "reply", "post_quit", "quit", "help", "exit" }; //TODO: change order to be more grouped

const String CommandsHandler::commandsDescriptions[CommandsCount] = { "Load data from file into the program" , "Sign user up", "Log user in",
"Log user out", "Edit user data", "Edit selected user data",
"Create a topic", "Save data" , "Save data as",
"Search for a topic by title", "Open a topic", "Post a post",
"List available posts in a topic", "Open a post", "Comment on a post",
"Reply to a comment in a post", "Close opened post", "Close opened topic", "List available commands", "Exit from program" };

bool CommandsHandler::networkLoaded = false;

void CommandsHandler::runCommands(SocialNetwork& currSocialNetwork) //TODO :: ADD exception handling for all commands
{
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
        try {
            currSocialNetwork.signup(ObjectFactory::createUser(currSocialNetwork));
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
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

    case AddPost:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        try {
            currSocialNetwork.addPost(ObjectFactory::createPost(currSocialNetwork));
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
        currSocialNetwork.listPostsInOpenedTopic();
        break;

    case PostOpen:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.openPost();
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
        catch (std::exception error) { //TODO : is this needed?
            std::cerr << "Could not reply! " << error.what() << std::endl;
        }
        break;

    case QuitPost:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.quitOpenedPost();
        break;

    case QuitTopic:
        if (!networkLoaded) {
            std::cout << "Please load a Social Network first!" << std::endl;
            break;
        }
        currSocialNetwork.quitOpenedTopic();
        break;

    case Help:
        PrintHandler::printCommands(commandsList, CommandsHandler::commandsDescriptions, CommandsCount);
        break;

    case Exit: //TODO: ask if user wants to save changes if there are any
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