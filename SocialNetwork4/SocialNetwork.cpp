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

	//Moderator Status
	if (CurrentData::getCurrSocialNetwork().getCurrUsers().back().getFirstName() != nullptr) {
		newUser.setModeratorStatus(false);
		//ID
		unsigned lastUserId = CurrentData::getCurrSocialNetwork().getCurrUsers().back().getId();
		newUser.setId(lastUserId + 1);
	}

	CurrentData::getCurrSocialNetwork().getCurrUsers().pushBack(newUser);
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

void SocialNetwork::createTopic()
{
	//Ensure a logged in user creates the topic
	if (SocialNetwork::getLoggedInUser().getFirstName() == nullptr) {
		std::cout << "Only logged in users can create topics! Please login first!" << std::endl;
		return;
	}

	//get input for all the metadata and create a topic, then add it to the currTopics vector
	
	Topic newTopic;

	//Title
	ConsoleInputGetter::recieveTitleInput(newTopic);
	if (!InputValidator::isValidTitle(newTopic.getTitle())) {
		PrintHandler::printErrorCreateTitle();
		return;
	}

	//Description
	ConsoleInputGetter::recieveDescriptionInput(newTopic);
	if (!InputValidator::isValidDescription(newTopic.getDescription())) {
		PrintHandler::printErrorCreateDescription();
		return;
	}

	//CreatorId
	newTopic.setCreatorId(SocialNetwork::getLoggedInUser().getId());

	//id
	newTopic.setId(CurrentData::getCurrSocialNetwork().getCurrTopics().getSize());

	CurrentData::getCurrSocialNetwork().getCurrTopics().pushBack(newTopic);

	CurrentData::setChangesMadeStatus(true);

}

void SocialNetwork::searchTopic(const Vector<Topic>& topicsToSearch)
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

	size_t topicsToSearchSize = topicsToSearch.getSize();

	for (int i = 0; i < topicsToSearchSize; ++i) {

		lhsString = topicsToSearch[i].getTitle().getString();
		lhsStringLength = lhsString.length();


		if (lhsString.find(rhsString)) {
			foundTopics.pushBack(topicsToSearch[i]);
		}

	}

	PrintHandler::printTopicsForSearch(foundTopics);

}

void SocialNetwork::openTopic(const Vector<Topic>& topics){


	std::cout << "Enter full title name or title id (Note: If title name is a number, please use its id!): ";

	Topic tempTopic;

	ConsoleInputGetter::recieveTitleInput(tempTopic);
	if (!InputValidator::isValidTitle(tempTopic.getTitle())) {
		std::cout << "Could not open topic! Invalid title!" << std::endl;
		return;
	}

	CustomString query = tempTopic.getTitle();

	bool isQueryDigit = query.isDigit();

	size_t topicsSize = topics.getSize();

	if (isQueryDigit) {

		size_t queryId = query.toNum();

		for (int i = 0; i < topicsSize; ++i) {

			if (queryId == topics[i].getId()) {
				openedTopic = topics[i];
				return;
			}
		}

	}

	else {

		for (int i = 0; i < topicsSize; ++i) {

			if (query == topics[i].getTitle()) {
				openedTopic = topics[i];
				return;
			}
		}

	}

}
