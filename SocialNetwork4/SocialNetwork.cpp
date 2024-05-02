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

void SocialNetwork::editLoggedInUser()
{
	//Ensure a logged in user edits
	if (loggedInUser.getFirstName() == nullptr) { //best practice: make this a function isThereLoggedInUser();
		std::cout << "Only logged in users can edit their profiles! Please login first!" << std::endl;
		return;
	}

	unsigned short answer = 3;

	std::cout << "What to edit?\n0 - Username\n1 - Password\n2 - both\n3 - Exit edit menu" << std::endl;
	ConsoleInputGetter::recieveEditAnswerInput(answer);
	if (!InputValidator::isValidEditAnswerInput(answer)) {
		std::cout << "Invalid answer! Exiting menu";
		answer = 3;
	}

	User newUser;

	switch (answer) {

	case 0:
		//UserName
		ConsoleInputGetter::recieveUserNameInput(newUser);
		if (!InputValidator::isValidUserNameLogin(newUser.getUserName())) {
			std::cout << "Could not edit user! Invalid username!"; //suggestion: specify if username already															exists
			return;
		}
		break;

	case 1:
		//Password
		ConsoleInputGetter::recievePasswordInput(newUser);
		if (!InputValidator::isValidPassword(newUser.getPassword())) {
			std::cout << "Could not edit user! Invalid password!";
			return;
		}
		break;

	case 2:
		ConsoleInputGetter::recieveUserNameInput(newUser);
		if (!InputValidator::isValidUserNameLogin(newUser.getUserName())) {
			std::cout << "Could not edit user! Invalid username!"; //suggestion: specify if username already															exists
			return;
		}
		ConsoleInputGetter::recievePasswordInput(newUser);
		if (!InputValidator::isValidPassword(newUser.getPassword())) {
			std::cout << "Could not edit user! Invalid password!";
			return;
		}
		break;

	case 3:
		std::cout << "Exited edit menu!" << std::endl;
		break;
	default:
		break;
	}


	
}

void SocialNetwork::createTopic()
{
	//Ensure a logged in user creates the topic
	if (loggedInUser.getFirstName() == nullptr) {
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

	if (loggedInUser.getFirstName() == nullptr) {
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
