#include "SocialNetwork.h"

User SocialNetwork::loggedInUser;
Topic SocialNetwork::openedTopic;

SocialNetwork::SocialNetwork(CustomString& directory) : directory(directory),
currUsers(1), currTopics(1) {}

SocialNetwork::SocialNetwork(const char* directory) : directory(directory),
currUsers(1), currTopics(1) {}

const CustomString& SocialNetwork::getDirectory() const
{
	return directory;
}

Vector<User>& SocialNetwork::getCurrUsers()
{
	return currUsers;
}

const Vector<User>& SocialNetwork::getCurrUsers() const
{
	return currUsers;
}

Vector<Topic>& SocialNetwork::getCurrTopics()
{
	return currTopics;
}

const Vector<Topic>& SocialNetwork::getCurrTopics() const
{
	return currTopics;
}

User& SocialNetwork::getLoggedInUser()
{
	return loggedInUser;
}

Topic& SocialNetwork::getOpenedTopic()
{
	return openedTopic;
}


void SocialNetwork::setDirectory(const CustomString& newDirectory)
{
	directory = newDirectory;
}

void SocialNetwork::setDirectory(const char* newDirectory)
{
	directory = newDirectory;
}

void SocialNetwork::setCurrUsers(const Vector<User>& newUsers)
{
	currUsers = newUsers;
}

void SocialNetwork::setCurrTopics(const Vector<Topic>& newTopics)
{
	currTopics = newTopics;
}

void SocialNetwork::setLoggedInUser(const User& newUser)
{
	loggedInUser = newUser;
}

void SocialNetwork::setOpenedTopic(const Topic& newTopic)
{
	openedTopic = newTopic;
}

bool SocialNetwork::isThereLoggedInUser()
{
	return loggedInUser.getFirstName() != nullptr;
}

SocialNetwork& SocialNetwork::operator=(const SocialNetwork& other) {
	if (this != &other) {

		directory = other.directory;
		currUsers = other.currUsers;
		currTopics = other.currTopics;
	}

	return *this;
}

void SocialNetwork::signup()
{
	User newUser;

	//UserName
	ConsoleInputGetter::recieveUserNameInput(newUser);
	if (!InputValidator::isValidUserNameSignup(newUser.getUserName())) {
		PrintHandler::printErrorSignupUserName();
		return;
	}

	//Password
	ConsoleInputGetter::recievePasswordInput(newUser);
	if (!InputValidator::isValidPassword(newUser.getPassword())) {
		PrintHandler::printErrorSignupPassword();
		return;
	}

	//FirstName
	ConsoleInputGetter::recieveFirstNameInput(newUser);
	if (!InputValidator::isValidFirstName(newUser.getFirstName())) {
		PrintHandler::printErrorSignupFirstName();
		return;
	}

	//LastName
	ConsoleInputGetter::recieveLastNameInput(newUser);
	if (!InputValidator::isValidLastName(newUser.getLastName())) {
		PrintHandler::printErrorSignupLastName();
		return;
	}

	//Moderator Status
	if (currUsers.back().getFirstName() != nullptr) {
		newUser.setModeratorStatus(false);
		//ID
		unsigned lastUserId = currUsers.back().getId();
		newUser.setId(lastUserId + 1); 
	}

	//Points are automatically 0 when creating a user

	currUsers.pushBack(newUser);
	CurrentData::setChangesMadeStatus(true);
}

void SocialNetwork::login()
{
	std::cout << std::endl << "Enter login data:" << std::endl;

	User newUser;

	//UserName
	ConsoleInputGetter::recieveUserNameInput(newUser);
	if (!InputValidator::isValidUserNameLogin(newUser.getUserName())) {
		PrintHandler::printErrorLoginUserName();
		return;
	}

	//Password
	ConsoleInputGetter::recievePasswordInput(newUser);
	if (!InputValidator::isValidPassword(newUser.getPassword())) {
		PrintHandler::printErrorLoginPassword();
		return;
	}

	if (CurrentData::isLoginSuccessful(newUser)) {
		loggedInUser = newUser;
		std::cout << "Login Successful!" << std::endl;
		return;
	}

	else {
		std::cout << "Wrong password!" << std::endl;
	}
}

void SocialNetwork::logout()
{
	if (!isThereLoggedInUser()) {
		std::cout << "Couldn't log out! No user is logged in!" << std::endl;
		return;
	}

	loggedInUser.clearUser();

	std::cout << "Logged out successfully!" << std::endl;
}

void SocialNetwork::editLoggedInUser() //BUG: Everywhere where we iterate through users we need to do it with size_t i not int i
{
	if (!isThereLoggedInUser()) {
		std::cout << "Only logged in users can edit their profiles! Please login first!" << std::endl;
		return;
	}

	size_t userPos = 0;
	bool userFound = false;
	size_t usersSize = currUsers.getSize();
	
	unsigned loggedInUserId = loggedInUser.getId();
	for (userPos; userPos < usersSize; ++userPos) {
		if (loggedInUserId == currUsers[userPos].getId()) {
			userFound = true;
			break;
		}
	}

	if (!userFound) {
		throw std::exception("Logged in user isn't in loaded data!"); //TODO: catch it somewhere
	}

	short answer = -1;

	std::cout << "Options for editing:\n0 - Username\n1 - Password\n"
		<< "2 - First Name\n3 - Last Name\n4 - Exit editing menu" << std::endl;

	while (answer != 4) {
		
		std::cout << "Please enter number from 0 to 4 to edit: ";
		try {
			ConsoleInputGetter::recieveAnswerInputForEditing(answer);
		}
		catch (std::exception e) {
			std::cout << e.what() << "\nExiting menu!" << std::endl;
			return;
		}
		if (!InputValidator::isValidAnswerInputForEditing(answer, 4)) {
			std::cout << "Invalid answer! Exiting menu!";
			return;
		}

		User newUser;

		switch (answer) {

		case 0:
			//UserName
			ConsoleInputGetter::recieveUserNameInput(newUser);
			if (!InputValidator::isValidUserNameSignup(newUser.getUserName())) {
				std::cout << "Could not edit user! Invalid username!"; //suggestion: specify if username already exists
				return;
			}
			loggedInUser.setUserName(newUser.getUserName());
			currUsers[userPos].setUserName(newUser.getUserName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 1:
			//Password
			ConsoleInputGetter::recievePasswordInput(newUser);
			if (!InputValidator::isValidPassword(newUser.getPassword())) {
				std::cout << "Could not edit user! Invalid password!";
				return;
			}
			loggedInUser.setPassword(newUser.getPassword());
			currUsers[userPos].setPassword(newUser.getPassword());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 2:
			//FirstName
			ConsoleInputGetter::recieveFirstNameInput(newUser);
			if (!InputValidator::isValidFirstName(newUser.getFirstName())) {
				std::cout << "Could not edit user! Invalid first name!";
				return;
			}
			loggedInUser.setFirstName(newUser.getFirstName());
			currUsers[userPos].setFirstName(newUser.getFirstName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 3:
			//LastName
			ConsoleInputGetter::recieveLastNameInput(newUser);
			if (!InputValidator::isValidLastName(newUser.getLastName())) {
				std::cout << "Could not edit user! Invalid last name!";
				return;
			}
			loggedInUser.setLastName(newUser.getLastName());
			currUsers[userPos].setLastName(newUser.getLastName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 4:
			std::cout << "Exited edit menu!" << std::endl;
			break;

		default:
			break;
		}
	}
}

void SocialNetwork::editUserAsModerator()
{
	if (!isThereLoggedInUser()) {
		std::cout << "Only logged in moderators can edit profiles! Please login first!" << std::endl;
		return;
	}

	if (!loggedInUser.getModeratorStatus()) { //check if user is moderator
		std::cout << "You are not a moderator! Please use command 'edit' instead!" << std::endl;
		return;
	}

	size_t id = 0;

	try {
		ConsoleInputGetter::recieveIdInputForEditUserAsModerator(id);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return;
	}

	size_t userPos = 0;
	bool userFound = false;
	bool newModeratorStatus = false;
	size_t usersSize = currUsers.getSize();

	for (userPos; userPos < usersSize; ++userPos) {
		if (id == currUsers[userPos].getId()) {
			userFound = true;
			break;
		}
	}

	if (!userFound) {
		std::cout << "No user with such id!" << std::endl; //or throw exception
		return;
	}

	short answer = -1;

	std::cout << "Options for editing:\n0 - Username\n1 - Password\n"
		<< "2 - First Name\n3 - Last Name\n4 - Moderator status\n5 - Exit editing menu" << std::endl;

	while (answer != 5) {

		if (!loggedInUser.getModeratorStatus()) { //second check after changes from first iteration
			return;
		}

		std::cout << "Please enter number from 0 to 5 to edit: ";
		try {
			ConsoleInputGetter::recieveAnswerInputForEditing(answer);
		}
		catch (std::exception e) {
			std::cout << e.what() << "\nExiting menu!" << std::endl;
			return;
		}
		if (!InputValidator::isValidAnswerInputForEditing(answer, 5)) {
			std::cout << "Invalid answer! Exiting menu!";
			return;
		}

		User newUser;

		switch (answer) {

		case 0:
			//UserName
			ConsoleInputGetter::recieveUserNameInput(newUser);
			if (!InputValidator::isValidUserNameSignup(newUser.getUserName())) {
				std::cout << "Could not edit user! Invalid username!"; //suggestion: specify if username already exists
				return;
			}
			loggedInUser.setUserName(newUser.getUserName());
			currUsers[userPos].setUserName(newUser.getUserName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 1:
			//Password
			ConsoleInputGetter::recievePasswordInput(newUser);
			if (!InputValidator::isValidPassword(newUser.getPassword())) {
				std::cout << "Could not edit user! Invalid password!";
				return;
			}
			loggedInUser.setPassword(newUser.getPassword());
			currUsers[userPos].setPassword(newUser.getPassword());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 2:
			//FirstName
			ConsoleInputGetter::recieveFirstNameInput(newUser);
			if (!InputValidator::isValidFirstName(newUser.getFirstName())) {
				std::cout << "Could not edit user! Invalid first name!";
				return;
			}
			loggedInUser.setFirstName(newUser.getFirstName());
			currUsers[userPos].setFirstName(newUser.getFirstName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 3:
			//LastName
			ConsoleInputGetter::recieveLastNameInput(newUser);
			if (!InputValidator::isValidLastName(newUser.getLastName())) {
				std::cout << "Could not edit user! Invalid last name!";
				return;
			}
			loggedInUser.setLastName(newUser.getLastName());
			currUsers[userPos].setLastName(newUser.getLastName());
			CurrentData::setChangesMadeStatus(true);
			break;

		case 4:
			try {
				ConsoleInputGetter::recieveModeratorStatusInputForEditUserAsModerator(newModeratorStatus);
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
				return;
			}
			loggedInUser.setModeratorStatus(newModeratorStatus);
			currUsers[userPos].setModeratorStatus(newModeratorStatus);
			CurrentData::setChangesMadeStatus(true);
			break;

		case 5:
			std::cout << "Exited edit menu!" << std::endl;
			break;

		default:
			break;
		}


	}

}

void SocialNetwork::createTopic()
{
	//Ensure a logged in user creates the topic
	if (!isThereLoggedInUser()) {
		std::cout << "Only logged in users can create topics! Please login first!" << std::endl;
		return;
	}

	//advice recieved: get input for all the metadata and create a topic, then add it to the currTopics vector
	
	Topic newTopic;

	//Title
	ConsoleInputGetter::recieveTitleInput(newTopic);
	if (!InputValidator::isValidTitle(newTopic.getTitle())) {
		PrintHandler::printErrorCreateTitleTopic();
		return;
	}

	//Description
	ConsoleInputGetter::recieveDescriptionInput(newTopic);
	if (!InputValidator::isValidDescription(newTopic.getDescription())) {
		PrintHandler::printErrorCreateDescriptionTopic();
		return;
	}

	//CreatorId
	newTopic.setCreatorId(loggedInUser.getId());

	//id
	if (currTopics.back().getTitle() != nullptr) {
		unsigned lastTopicId = currTopics.back().getId();
		newTopic.setId(lastTopicId + 1);
	}

	currTopics.pushBack(newTopic);

	CurrentData::setChangesMadeStatus(true);

}

void SocialNetwork::searchTopic()
{
	Vector<Topic> foundTopics;

	Topic tempTopic;

	ConsoleInputGetter::recieveTitleInput(tempTopic);
	if (!InputValidator::isValidTitle(tempTopic.getTitle())) {
		std::cout << "Invalid input! Could not search topics!" << std::endl;
		return;
	}

	CustomString rhsString = tempTopic.getTitle().getString();
	size_t rhsStringLength = rhsString.length();

	CustomString lhsString;
	size_t lhsStringLength = 0;

	size_t topicsToSearchSize = currTopics.getSize();

	for (int i = 0; i < topicsToSearchSize; ++i) {

		lhsString = currTopics[i].getTitle().getString();
		lhsStringLength = lhsString.length();


		if (lhsString.find(rhsString)) {
			foundTopics.pushBack(currTopics[i]);
		}

	}

	PrintHandler::printTopicsForSearch(foundTopics);

}

void SocialNetwork::openTopic(){


	std::cout << "Enter full title name or title id (Note: If title name is a number, please use its id!): ";

	Topic tempTopic; //optimisation: create an empty topic (no discussions, no comments)

	ConsoleInputGetter::recieveTitleInput(tempTopic);
	if (!InputValidator::isValidTitle(tempTopic.getTitle())) {
		std::cout << "Could not open topic! Invalid title!" << std::endl;
		return;
	}

	CustomString query = tempTopic.getTitle();

	bool isQueryDigit = query.isDigit();

	size_t topicsSize = currTopics.getSize();

	if (isQueryDigit) {

		size_t queryId = query.toNum();

		for (int i = 0; i < topicsSize; ++i) {

			if (queryId == currTopics[i].getId()) {
				openedTopic = currTopics[i];
				std::cout << "Opened Topic:\n"
					<< currTopics[i].getTitle() << std::endl;
			}
		}

	}

	else {

		for (int i = 0; i < topicsSize; ++i) {

			if (query == currTopics[i].getTitle()) {
				openedTopic = currTopics[i];
				std::cout << "Opened Topic:\n"
					<< query << std::endl;
				return;
			}
		}

	}

}

Discussion SocialNetwork::createDiscussion()
{

	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Discussion could not be created! Please log in before posting!");
	}

	if (openedTopic.getTitle() == nullptr) { //is this method of checking ok?
		throw std::runtime_error("Discussion could not be created! Please open a topic before posting!");
	}

	
	Discussion newDiscussion; //optimisation: create an empty discussion ( no comments)

	//Title
	ConsoleInputGetter::recieveTitleInput(newDiscussion);
	if (!InputValidator::isValidTitle(newDiscussion.getTitle())) {
		throw std::runtime_error("Discussion could not be created! Invalid Title!");
	}

	//Description
	ConsoleInputGetter::recieveDescriptionInput(newDiscussion);
	if (!InputValidator::isValidDescription(newDiscussion.getDescription())) {
		PrintHandler::printErrorCreateDescriptionDiscussion();
		throw std::runtime_error("Discussion could not be created! Invalid Description!");
	}

	//topicId
	newDiscussion.setTopicId(openedTopic.getId());

	//creatorId
	newDiscussion.setCreatorId(loggedInUser.getId());

	//id
	if (openedTopic.getDiscussions().back().getTitle() != nullptr) {
		unsigned lastDiscussionId = openedTopic.getDiscussions().back().getId();
		newDiscussion.setId(lastDiscussionId + 1);
	}

	return newDiscussion;
}

void SocialNetwork::postDiscussion(const Discussion& newDiscussion)
{
	size_t topicId = openedTopic.getId();
	size_t topicsSize = currTopics.getSize();
	bool addSuccessful = false;

	int i = 0;
	for (i; i < topicsSize; ++i) {

		if (topicId == currTopics[i].getId()) {
			currTopics[i].addDiscussion(newDiscussion);
			addSuccessful = true;
			break;
		}
	}

	if (addSuccessful) {
		CurrentData::setChangesMadeStatus(true);
		openedTopic.addDiscussion(newDiscussion);
		std::cout << "Posted Discussion: ''" << newDiscussion.getTitle() << "'' successfully!" << std::endl;

	}
	else {
		throw std::runtime_error("Topic not found");
	}
}

void SocialNetwork::listDiscussionsInOpenedTopic()
{
	if (openedTopic.getTitle() == nullptr) { //is this method of checking ok?
		std::cout << "Topic not opened! Please open a topic before listing!"
			<< std::endl;
		return;
	}

	PrintHandler::printDiscussionsForList(openedTopic.getDiscussions());
}
