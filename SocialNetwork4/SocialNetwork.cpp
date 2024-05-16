#include "SocialNetwork.h"

User SocialNetwork::loggedInUser;
Topic SocialNetwork::openedTopic;
Discussion SocialNetwork::openedDiscussion;

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

const User& SocialNetwork::getLoggedInUser() const
{
	return loggedInUser;
}

const Topic& SocialNetwork::getOpenedTopic() const
{
	return openedTopic;
}

const Discussion& SocialNetwork::getOpenedDiscussion() const
{
	return openedDiscussion;
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

bool SocialNetwork::isThereLoggedInUser() const
{
	return loggedInUser.getFirstName() != nullptr;
}

bool SocialNetwork::isThereOpenedTopic() const
{
	return openedTopic.getTitle() != nullptr;
}

bool SocialNetwork::isThereOpenedDiscussion() const
{
	return openedDiscussion.getTitle() != nullptr;
}

bool SocialNetwork::isLoginSuccessful(User& user)
{
	size_t usersSize = currUsers.getSize();

	for (size_t i = 0; i < usersSize; i++) {

		if (user.getUserName() == currUsers[i].getUserName()
			&& user.getPassword() == currUsers[i].getPassword()) {
			user = currUsers[i];
			return true;
		}
	}
	return false;

}

size_t SocialNetwork::doesUsernameExist(const CustomString& userName)
{
	size_t usersSize = currUsers.getSize();

	for (size_t i = 0; i < usersSize; i++) {
		if (userName == currUsers[i].getUserName())
			return i;
	}
	return SIZE_MAX;
}

size_t SocialNetwork::doesCommentExist(const size_t id, const Vector<Comment>& comments)
{
	size_t commentsSize = comments.getSize();

	for (size_t i = 0; i < commentsSize; ++i) {
		if (id == comments[i].getId())
			return i;
	}

	return SIZE_MAX;
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
	size_t userNameStatus = InputValidator::isValidUserNameSignup(newUser.getUserName());

	switch (userNameStatus) {

	case 0:
		std::cerr << "\nError creating Account! Invalid Username!" << std::endl;
		return;
	case 1:
		break;
	case 2:
		std::cout << "User already exists!" << std::endl;
		return;
	default:
		throw std::exception("Error with usersStatus when signing up!");
	}

	//Password
	ConsoleInputGetter::recievePasswordInput(newUser);
	if (!InputValidator::isValidPassword(newUser.getPassword())) {
		std::cerr << "\nError creating Account! Invalid Password!" << std::endl;
		return;
	}

	//FirstName
	ConsoleInputGetter::recieveFirstNameInput(newUser);
	if (!InputValidator::isValidFirstName(newUser.getFirstName())) {
		std::cerr << "\nError creating Account! Invalid First Name!" << std::endl;
		return;
	}

	//LastName
	ConsoleInputGetter::recieveLastNameInput(newUser);
	if (!InputValidator::isValidLastName(newUser.getLastName())) {
		std::cerr << "\nError creating Account! Invalid Last Name!" << std::endl;;
		return;
	}

	//Moderator Status
	if (currUsers.back().getFirstName() != nullptr) {
		newUser.setModeratorStatus(false);
		//ID
		size_t lastUserId = currUsers.back().getId();
		newUser.setId(lastUserId + 1); 
	}

	else {
		newUser.setId(0);
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
		std::cerr << "\nInvalid Username!" << std::endl;
		return;
	}

	//Password
	ConsoleInputGetter::recievePasswordInput(newUser);
	if (!InputValidator::isValidPassword(newUser.getPassword())) {
		std::cerr << "\nInvalid Password!" << std::endl;
		return;
	}

	if (isLoginSuccessful(newUser)) {
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

void SocialNetwork::editLoggedInUser()
{
	if (!isThereLoggedInUser()) {
		std::cout << "Only logged in users can edit their profiles! Please login first!" << std::endl;
		return;
	}

	size_t userPos = 0;
	bool userFound = false;
	size_t usersSize = currUsers.getSize();
	
	size_t loggedInUserId = loggedInUser.getId();
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

		size_t userNameStatus = SIZE_MAX;
		switch (answer) {

		case 0:
			//UserName
			ConsoleInputGetter::recieveUserNameInput(newUser);
			userNameStatus = InputValidator::isValidUserNameSignup(newUser.getUserName());
			if (userNameStatus == 0) {
				std::cout << "Could not edit user! Invalid username!" << std::endl;
				return;
			}

			else if (userNameStatus == 2) {
				std::cout << "Could not edit user! Username already exists!" << std::endl;
				return;
			}

			else if (userNameStatus != 1) {
				throw std::exception("Unknown problem with username status by editing user!");
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

		try {
			ConsoleInputGetter::recieveAnswerInputForEditing(answer);
		}
		catch (std::exception e) {
			std::cout << e.what() << "\nExiting menu!" << std::endl;
			return;
		}
		if (!InputValidator::isValidAnswerInputForEditing(answer, 5)) {
			std::cout << "Invalid answer! Exiting menu!" << std::endl;
			return;
		}

		User newUser;
		size_t userNameStatus = SIZE_MAX;

		switch (answer) {

		case 0:
			//UserName
			ConsoleInputGetter::recieveUserNameInput(newUser);
			userNameStatus = InputValidator::isValidUserNameSignup(newUser.getUserName());
			if (userNameStatus == 0) {
				std::cout << "Could not edit user! Invalid username!" << std::endl;
				return;
			}

			else if (userNameStatus == 2) {
				std::cout << "Could not edit user! username already exists!" << std::endl;
				return;
			}

			else if (userNameStatus != 1) {
				throw std::exception("Unknown problem with username status by editing user (moderator)!");
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

void SocialNetwork::addTopic(const Topic& newTopic)
{
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

	for (size_t i = 0; i < topicsToSearchSize; ++i) {

		lhsString = currTopics[i].getTitle().getString();
		lhsStringLength = lhsString.length();


		if (lhsString.find(rhsString)) {
			foundTopics.pushBack(currTopics[i]);
		}

	}

	PrintHandler::printTopicsForSearch(foundTopics);

}

void SocialNetwork::openTopic(){

	std::cout << "Enter full title name or topic id (Note: If title name is a number, please use its id!): ";

	Topic tempTopic; //optimisation: create an empty topic (no discussions, no comments)

	ConsoleInputGetter::recieveTitleInput(tempTopic);
	if (!InputValidator::isValidTitle(tempTopic.getTitle())) {
		std::cout << "Could not open topic! Invalid title or id!" << std::endl;
		return;
	}

	CustomString query = tempTopic.getTitle();

	bool isQueryDigit = query.isDigit();

	size_t topicsSize = currTopics.getSize();

	if (isQueryDigit) {

		size_t queryId = query.toNum();

		for (size_t i = 0; i < topicsSize; ++i) {

			if (queryId == currTopics[i].getId()) {
				openedTopic = currTopics[i];
				std::cout << "Opened Topic:\n"
					<< currTopics[i].getTitle() << std::endl;
				return;
			}
		}

	}

	else {

		for (size_t i = 0; i < topicsSize; ++i) {

			if (query == currTopics[i].getTitle()) {
				openedTopic = currTopics[i];
				std::cout << "Opened Topic:\n"
					<< query << std::endl;
				return;
			}
		}

	}

	std::cout << "Could not open topic! Invalid title or id!" << std::endl;
}

Discussion SocialNetwork::createDiscussion()
{

	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Discussion could not be created! Please log in before posting!");
	}

	if (!isThereOpenedTopic()) {
		throw std::runtime_error("Discussion could not be created! Please open a topic before posting!");
	}

	
	Discussion newDiscussion; //optimisation: create an empty discussion ( no comments)

	//Title
	ConsoleInputGetter::recieveDiscussionTitleInput(newDiscussion);
	if (!InputValidator::isValidTitle(newDiscussion.getTitle())) {
		throw std::runtime_error("Discussion could not be created! Invalid Title!");
	}

	//Content
	ConsoleInputGetter::recieveDiscussionContentInput(newDiscussion);
	if (!InputValidator::isValidContent(newDiscussion.getContent())) {
		throw std::runtime_error("Discussion could not be created! Invalid Content!");
	}

	//topicId
	newDiscussion.setTopicId(openedTopic.getId());

	//creatorId
	newDiscussion.setCreatorId(loggedInUser.getId());

	//id
	if (openedTopic.getDiscussions().back().getTitle() != nullptr) {
		size_t lastDiscussionId = openedTopic.getDiscussions().back().getId();
		newDiscussion.setId(lastDiscussionId + 1);
	}

	else {
		newDiscussion.setId(0);
	}

	return newDiscussion;
}

void SocialNetwork::postDiscussion(const Discussion& newDiscussion)
{
	size_t topicId = openedTopic.getId();
	size_t topicsSize = currTopics.getSize();
	bool addSuccessful = false;

	size_t i = 0;
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
	if (!isThereOpenedTopic()) {
		std::cout << "Topic not opened! Please open a topic before listing!"
			<< std::endl;
		return;
	}

	PrintHandler::printDiscussionsForList(openedTopic.getDiscussions());
}

void SocialNetwork::openDiscussion()
{
	if (!isThereOpenedTopic()) {
		std::cout << "Could not open discussion! Please open a topic first!"
			<< std::endl;
		return;
	}

	size_t id = 0;

	try {
		ConsoleInputGetter::recieveOpenDiscussionIdInput(id);
	}

	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "Could not open discussion!" << std::endl;
		return;
	}

	size_t discussionsSize = openedTopic.getDiscussions().getSize();
	bool discussionOpened = false;

	for (size_t i = 0; i < discussionsSize; ++i) {

		if (id == openedTopic.getDiscussions()[i].getId()) {
			openedDiscussion = openedTopic.getDiscussions()[i];
			discussionOpened = true;
			std::cout << "Successfully opened discussion ''" << openedDiscussion.getTitle() << "''!" << std::endl
				<< openedDiscussion.getContent() << std::endl
				<< "Number of answers: " << openedDiscussion.getComments().getSize() << std::endl;
			
			return;
		}

	}

	if (!discussionOpened) {
		std::cout << "Could not open discussion! No discussion with such id exists!" << std::endl;
	}
}

Comment SocialNetwork::createComment() 
{
	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Comment could not be created! Please log in before commenting!");
	}

	if (!isThereOpenedTopic()) {
		throw std::runtime_error("Comment could not be created! Please open a topic before commenting!");
	}

	if (!isThereOpenedDiscussion()) {
		throw std::runtime_error("Comment could not be created! Please open a discussion before commenting!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(loggedInUser.getUserName());
	newComment.setScore(0);
	newComment.setDiscussionId(openedDiscussion.getId());

	if (openedDiscussion.getComments().back().getAuthor() != nullptr) {
		size_t lastCommentId = openedDiscussion.getComments().back().getId();
		newComment.setId(lastCommentId + 1);
	}

	else {
		newComment.setId(0);
	}
	
	return newComment;
}


void SocialNetwork::addComment(const Comment& newComment)
{
	//Find corresponding topic
	size_t searchedTopicId = openedTopic.getId();
	size_t topicsSize = currTopics.getSize();
	bool topicFound = false;

	size_t topicPos = 0;
	for (topicPos; topicPos < topicsSize; ++topicPos) {

		if (searchedTopicId == currTopics[topicPos].getId()) {
			topicFound = true;
			break;
		}
	}

	if (topicFound == false) {
		throw std::runtime_error("Topic not found");
	}

	//Find corresponding discussion
	size_t searchedDiscussionId = openedDiscussion.getId();
	size_t discussionsSize = currTopics[topicPos].getDiscussions().getSize();
	bool discussionFound = false;

	size_t discussionPos = 0;
	for (discussionPos; discussionPos < discussionsSize; ++discussionPos) {
		if (searchedDiscussionId == currTopics[topicPos].getDiscussions()[discussionPos].getId()) {
			currTopics[topicPos].getDiscussions()[discussionPos].addComment(newComment);
			CurrentData::setChangesMadeStatus(true);
			discussionFound = true;
		}
	}

	if (discussionFound == false) {
		throw std::runtime_error("Discussion not found");
	}

	openedDiscussion.addComment(newComment);

	std::cout << "Successfully commented!" << std::endl;
}

void SocialNetwork::replyToComment(const size_t parentId)
{
	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Could not reply! Please log in before replying!");
	}

	if (!isThereOpenedTopic()) {
		throw std::runtime_error("Could not reply! Please open a topic before replying!");
	}

	if (!isThereOpenedDiscussion()) {
		throw std::runtime_error("Could not reply! Please open a discussion before replying!");
	}

	size_t commentPosition = doesCommentExist(parentId, openedDiscussion.getComments());

	if (commentPosition == SIZE_MAX) {
		throw std::runtime_error("Comment not found!");
	}
	
	Reply parentCommentLastReply = openedDiscussion.getComments()[commentPosition].getReplies().back();
	Reply newReply = createReply(parentCommentLastReply, parentId);


	//Find corresponding topic
	size_t searchedTopicId = openedTopic.getId();
	size_t topicsSize = currTopics.getSize();
	bool topicFound = false;

	size_t topicPos = 0;
	for (topicPos; topicPos < topicsSize; ++topicPos) {

		if (searchedTopicId == currTopics[topicPos].getId()) {
			topicFound = true;
			break;
		}
	}

	if (topicFound == false) {
		throw std::runtime_error("Topic not found");
	}


	//Find corresponding discussion
	size_t searchedDiscussionId = openedDiscussion.getId();
	size_t discussionsSize = currTopics[topicPos].getDiscussions().getSize();
	bool discussionFound = false;

	size_t discussionPos = 0;
	for (discussionPos; discussionPos < discussionsSize; ++discussionPos) {
		if (searchedDiscussionId == currTopics[topicPos].getDiscussions()[discussionPos].getId()) {
			currTopics[topicPos].getDiscussions()[discussionPos].getComments()[commentPosition].addReply(newReply);
			CurrentData::setChangesMadeStatus(true);
			discussionFound = true;
		}
	}

	if (discussionFound == false) {
		throw std::runtime_error("Discussion not found");
	}

	openedDiscussion.getComments()[commentPosition].addReply(newReply);

	std::cout << "Successfully replied!" << std::endl;
}

Reply SocialNetwork::createReply(const Reply& parentCommentLastReply, const size_t parentCommentId)
{
	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Reply could not be created! Please log in before replying!");
	}

	if (!isThereOpenedTopic()) {
		throw std::runtime_error("Reply could not be created! Please open a topic before replying!");
	}

	if (!isThereOpenedDiscussion()) {
		throw std::runtime_error("Comment could not be created! Please open a discussion before replying!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(loggedInUser.getUserName());
	newComment.setScore(0);
	newComment.setDiscussionId(openedDiscussion.getId());

	if (parentCommentLastReply.getAuthor() != nullptr) {
		newComment.setId(parentCommentLastReply.getId() + 1);
	}

	else {
		newComment.setId(0);
	}

	Reply newReply = newComment;

	newReply.setParentCommentId(parentCommentId);

	return newReply;
}
