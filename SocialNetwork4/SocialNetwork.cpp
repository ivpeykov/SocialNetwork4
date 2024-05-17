#include "SocialNetwork.h"

User SocialNetwork::loggedInUser;
Topic SocialNetwork::openedTopic;
Post SocialNetwork::openedPost;

SocialNetwork::SocialNetwork(String& directory) : directory(directory),
currUsers(1), currTopics(1) {}

SocialNetwork::SocialNetwork(const char* directory) : directory(directory),
currUsers(1), currTopics(1) {}

const String& SocialNetwork::getDirectory() const
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

const Post& SocialNetwork::getOpenedPost() const
{
	return openedPost;
}


void SocialNetwork::setDirectory(const String& newDirectory)
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

bool SocialNetwork::isThereOpenedPost() const
{
	return openedPost.getTitle() != nullptr;
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

size_t SocialNetwork::doesUsernameExist(const String& userName) const
{
	size_t usersSize = currUsers.getSize();

	for (size_t i = 0; i < usersSize; i++) {
		if (userName == currUsers[i].getUserName())
			return i;
	}
	return SIZE_MAX;
}

size_t SocialNetwork::doesCommentExist(const size_t id, const Vector<Comment>& comments) const
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
		std::cerr << "\nError creating Account! Invalid Last Name!" << std::endl;
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
		
		try {
			ConsoleInputGetter::recieveAnswerInputForEditing(answer, 4);
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
			ConsoleInputGetter::recieveAnswerInputForEditing(answer, 5);
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

	String rhsString = tempTopic.getTitle().getString();
	size_t rhsStringLength = rhsString.length();

	String lhsString;
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

	Topic tempTopic; //optimisation: create an empty topic (no posts, no comments)

	ConsoleInputGetter::recieveTitleInput(tempTopic);
	if (!InputValidator::isValidTitle(tempTopic.getTitle())) {
		std::cout << "Could not open topic! Invalid title or id!" << std::endl;
		return;
	}

	String query = tempTopic.getTitle();

	bool isQueryDigit = query.isDigit();

	size_t topicsSize = currTopics.getSize();

	if (isQueryDigit) {

		size_t queryId = query.toNum();

		for (size_t i = 0; i < topicsSize; ++i) {

			if (queryId == currTopics[i].getId()) {
				openedTopic = currTopics[i];
				openedPost.clear();
				std::cout << "Opened Topic:\nName: "
					<< currTopics[i].getTitle() << "\nID: " << currTopics[i].getId() << std::endl;
				return;
			}
		}

	}

	else {

		for (size_t i = 0; i < topicsSize; ++i) {

			if (query == currTopics[i].getTitle()) {
				openedTopic = currTopics[i];
				openedPost.clear();
				std::cout << "Opened Topic:\nName: "
					<< query << "\nID: " << currTopics[i].getId() << std::endl;
				return;
			}
		}

	}

	std::cout << "Could not open topic! Invalid title or id!" << std::endl;
}

void SocialNetwork::addPost(const Post& newPost)
{
	size_t topicId = openedTopic.getId();
	size_t topicsSize = currTopics.getSize();
	bool addSuccessful = false;

	size_t i = 0;
	for (i; i < topicsSize; ++i) {

		if (topicId == currTopics[i].getId()) {
			currTopics[i].addPost(newPost); //update currTopics vector
			addSuccessful = true;
			break;
		}
	}

	if (addSuccessful) {
		CurrentData::setChangesMadeStatus(true);
		openedTopic.addPost(newPost); //update static object openedTopic
		std::cout << "Added Post: ''" << newPost.getTitle() << "'' successfully!" << std::endl;

	}
	else {
		throw std::runtime_error("Topic not found");
	}
}

void SocialNetwork::listPostsInOpenedTopic() const
{
	if (!isThereOpenedTopic()) {
		std::cout << "Topic not opened! Please open a topic before listing!"
			<< std::endl;
		return;
	}

	std::cout << "Posts in Topic - " << openedTopic.getTitle() << ":" << std::endl;

	PrintHandler::printPostsForList(openedTopic.getPosts());
}

void SocialNetwork::openPost()
{
	if (!isThereOpenedTopic()) {
		std::cout << "Could not open post! Please open a topic first!"
			<< std::endl;
		return;
	}

	//remove...
	std::cout << "Current opened Topic: " << openedTopic.getTitle() << std::endl;

	size_t id = 0;

	try {
		ConsoleInputGetter::recieveOpenPostIdInput(id);
	}

	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "Could not open post!" << std::endl;
		return;
	}

	size_t postsSize = openedTopic.getPosts().getSize();
	bool postOpened = false;

	for (size_t i = 0; i < postsSize; ++i) {

		if (id == openedTopic.getPosts()[i].getId()) {
			openedPost = openedTopic.getPosts()[i];
			postOpened = true;
			std::cout << "Successfully opened post ''" << openedPost.getTitle() << "''!" << std::endl
				<< openedPost.getContent() << std::endl
				<< "Number of answers: " << openedPost.getComments().getSize() << std::endl;
			
			return;
		}

	}

	if (!postOpened) {
		std::cout << "Could not open post! No post with such id exists!" << std::endl;
	}
}

void SocialNetwork::addComment(const Comment& newComment)
{

	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Could not comment! Please log in before commenting!");
	}

	if (!isThereOpenedTopic()) {
		throw std::runtime_error("Could not comment! Please open a topic before commenting!");
	}

	if (!isThereOpenedPost()) {
		throw std::runtime_error("Could not comment! Please open a post before commenting!");
	}

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

	//Find corresponding post
	size_t searchedPostId = openedPost.getId();
	size_t postsSize = currTopics[topicPos].getPosts().getSize();
	bool postFound = false;

	size_t postPos = 0;
	for (postPos; postPos < postsSize; ++postPos) {
		if (searchedPostId == currTopics[topicPos].getPosts()[postPos].getId()) {
			currTopics[topicPos].getPosts()[postPos].addComment(newComment); // update currTopics vector
			CurrentData::setChangesMadeStatus(true);
			postFound = true;
		}
	}

	if (postFound == false) {
		throw std::runtime_error("Post not found");
	}

	openedPost.addComment(newComment); //update static object openedPost
	openedTopic.getPosts()[postPos - 1].addComment(newComment); //update static object openedTopic

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

	if (!isThereOpenedPost()) {
		throw std::runtime_error("Could not reply! Please open a post before replying!");
	}

	size_t commentPosition = doesCommentExist(parentId, openedPost.getComments());

	if (commentPosition == SIZE_MAX) {
		throw std::runtime_error("Comment not found!");
	}
	
	Reply parentCommentLastReply = openedPost.getComments()[commentPosition].getReplies().back();
	Reply newReply = ObjectFactory::createReply(*this, parentCommentLastReply, parentId);


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


	//Find corresponding post
	size_t searchedPostId = openedPost.getId();
	size_t postsSize = currTopics[topicPos].getPosts().getSize();
	bool postFound = false;

	size_t postPos = 0;
	for (postPos; postPos < postsSize; ++postPos) {
		if (searchedPostId == currTopics[topicPos].getPosts()[postPos].getId()) {
			currTopics[topicPos].getPosts()[postPos].getComments()[commentPosition].addReply(newReply); //update currTopics vector
			CurrentData::setChangesMadeStatus(true);
			postFound = true;
		}
	}

	if (postFound == false) {
		throw std::runtime_error("Post not found");
	}

	openedPost.getComments()[commentPosition].addReply(newReply); //update static object openedPost
	openedTopic.getPosts()[postPos - 1].getComments()[commentPosition].addReply(newReply); //update static object openedTopic

	std::cout << "Successfully replied!" << std::endl;
}

void SocialNetwork::quitOpenedPost() 
{
	if (!isThereOpenedPost()) {
		std::cout << "There is no opened post to close!" << std::endl;
		return;
	}

	std::cout << "Post with title: " << openedPost.getTitle() << " - closed!" << std::endl;
	openedPost.clear();
	
}
