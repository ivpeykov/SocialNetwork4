#include "CommandsHandler.h"

unsigned short CommandsHandler::currCommand = Undefined;

//Adjust COMMAND_INPUT_MAX_LENGTH in Configuration.h if adding longer commands.
const String CommandsHandler::commandsList[CommandsCount] = { "load", "signup", "login", "logout", "edit", "edit id", "create", "search",
"open", "post", "list", "post_open", "print_comments", "comment", "reply", "upvote", "downvote", "delete_comment", "delete_post", "delete_topic",
"post_quit", "quit", "help","save", "save as", "exit" };

const String CommandsHandler::commandsDescriptions[CommandsCount] = { "Load data from file into the program", "Sign user up", "Log user in",
"Log user out", "Edit user data", "Edit selected user data", "Create a topic",
"Search for a topic by title", "Open a topic", "Post a discussion",
"List available posts in a topic", "Open a post", "Print comments and replies of an opened post", "Comment on a post",
"Reply to a comment in a post", "Upvote a selected comment", "Downvote a selected comment", "Delete a selected comment", "Delete a selected post", "Delete a selected topic",
"Close opened post", "Close opened topic", "List available commands", "Save data" , "Save data as", "Exit from program" };

bool CommandsHandler::networkLoaded = false;

void CommandsHandler::runCommands(SocialNetwork& currSocialNetwork)
{
	switch (currCommand) {

	case Load:
		if (networkLoaded) {
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
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}
		break;

	case Login:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		try {
			currSocialNetwork.login();
		}
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}
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
		try {
			currSocialNetwork.editLoggedInUser();
		}

		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}
		break;

	case EditAsModerator:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		try {
			currSocialNetwork.editUserAsModerator();
		}
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}
		break;

	case Create:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		try {
			currSocialNetwork.addTopic(ObjectFactory::createTopic(currSocialNetwork));
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
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
		try {
			currSocialNetwork.openTopic();
		}
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}
		break;

	case AddPost:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		try {
			currSocialNetwork.addPost(ObjectFactory::createPost(currSocialNetwork));
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
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

	case PrintPostComments:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		currSocialNetwork.printOpenedPostComments();
		break;

	case AddComment:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		try {
			currSocialNetwork.addComment(ObjectFactory::createComment(currSocialNetwork));
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		break;


	case ReplyToComment:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		try {
			currSocialNetwork.replyToComment(ConsoleInputGetter::recieveIdInput());
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Could not reply! " << e.what() << std::endl;
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Could not reply! " << e.what() << std::endl;
		}
		break;

	case Upvote: {
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		//choose which comment to upvote
		size_t commentId = SIZE_MAX;
		try {
			commentId = currSocialNetwork.chooseObject();
		}
		catch (const std::invalid_argument&) {
			std::cout << "Could not upvote comment! " << std::endl;
			return;
		}

		try {
			currSocialNetwork.upvoteComment(commentId);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Could not upvote!" << e.what() << std::endl;
		}
		break;
	}

	case Downvote: {
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		//choose which comment to downvote
		size_t commentId = SIZE_MAX;
		try {
			commentId = currSocialNetwork.chooseObject();
		}
		catch (const std::invalid_argument&) {
			std::cout << "Could not downvote comment! " << std::endl;
			return;
		}

		try {
			currSocialNetwork.downvoteComment(commentId);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Could not downvote!" << e.what() << std::endl;
		}
		break;
	}

	case DeleteComment: {
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		if (!currSocialNetwork.isThereOpenedPost()) {
			std::cout << "Could not delete comment! Please open a post first!" << std::endl;
			return;
		}

		if (!currSocialNetwork.isThereLoggedInUser()) {
			std::cout << "Could not delete comment! Please login first!" << std::endl;
			return;
		}

		//choose comment
		size_t commentId = SIZE_MAX;
		try {
			commentId = currSocialNetwork.chooseObject();
		}
		catch (const std::invalid_argument&) {
			std::cout << "Could not delete comment! " << std::endl;
			return;
		}

		try {
			currSocialNetwork.deleteComment(commentId);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Could not delete comment!" << e.what() << std::endl;
		}
		catch (const std::logic_error& e) {
			std::cout << "Could not delete comment!" << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}

		break;
	}

	case DeletePost: {
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}

		if (!currSocialNetwork.isThereOpenedTopic()) {
			std::cout << "Could not delete post! Please open a topic first!" << std::endl;
			break;
		}

		if (!currSocialNetwork.isThereLoggedInUser()) {
			std::cout << "Could not delete post! Please login first!" << std::endl;
			break;
		}

		if (SocialNetwork::getLoggedInUser().getModeratorStatus() == false) {
			std::cout << "Could not delete Post! No admin privileges!";
			return;
		}

		//choose post
		size_t postId = SIZE_MAX;
		try {
			postId = currSocialNetwork.chooseObject();
		}
		catch (const std::invalid_argument&) {
			std::cout << "Could not delete post! " << std::endl;
			return;
		}

		try {
			currSocialNetwork.deletePost(postId);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Could not delete post!" << e.what() << std::endl;
		}
		catch (const std::logic_error& e) {
			std::cout << "Could not delete post!" << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}

		break;
	}


	case DeleteTopic: {
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		if (!currSocialNetwork.isThereLoggedInUser()) {
			std::cout << "Could not delete Topic! Please login first!" << std::endl;
			break;
		}

		if (SocialNetwork::getLoggedInUser().getModeratorStatus() == false) {
			std::cout << "Could not delete Topic! No admin privileges!";
			return;
		}

		//choose topic
		size_t topicId = SIZE_MAX;
		try {
			topicId = currSocialNetwork.chooseObject();
		}
		catch (const std::invalid_argument&) {
			std::cout << "Could not delete topic! " << std::endl;
			return;
		}

		try {
			currSocialNetwork.deleteTopic(topicId);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Could not delete topic!" << e.what() << std::endl;
		}
		catch (const std::logic_error& e) {
			std::cout << "Could not delete topic!" << e.what() << std::endl;
			FileHandler::saveSocialNetworkPostCriticalError(e, currSocialNetwork);
			exit(0);
		}

		break;
	}


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


	case Save:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		FileHandler::saveSocialNetwork(currSocialNetwork);
		break;
	case SaveAs:
		if (!networkLoaded) {
			std::cout << "Please load a Social Network first!" << std::endl;
			break;
		}
		FileHandler::saveSocialNetworkAs(currSocialNetwork);
		break;

	case Exit:
		currSocialNetwork.exitProgram();
		break;
	}
}

void CommandsHandler::setCurrCommand(unsigned short newCommand) {
	currCommand = newCommand;
}

unsigned short CommandsHandler::getCurrCommand() {
	return currCommand;
}