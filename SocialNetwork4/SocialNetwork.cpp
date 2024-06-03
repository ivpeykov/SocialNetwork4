#include "SocialNetwork.h"

User SocialNetwork::loggedInUser;
Topic SocialNetwork::openedTopic;
Post SocialNetwork::openedPost;

size_t SocialNetwork::loggedInUserPos = SIZE_MAX;
size_t SocialNetwork::openedTopicPos = SIZE_MAX;
size_t SocialNetwork::openedPostPos = SIZE_MAX;

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

User& SocialNetwork::getLoggedInUser()
{
	return loggedInUser;
}

Topic& SocialNetwork::getOpenedTopic()
{
	return openedTopic;
}

 Post& SocialNetwork::getOpenedPost()
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

void SocialNetwork::setOpenedPost(const Post& newPost)
{
	openedPost = newPost;
}

bool SocialNetwork::isThereLoggedInUser()
{
	return loggedInUser.getFirstName() != nullptr;
}

bool SocialNetwork::isThereOpenedTopic()
{
	return openedTopic.getTitle() != nullptr;
}

bool SocialNetwork::isThereOpenedPost()
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

size_t SocialNetwork::getUserPosition(const String& userName) const 
{
	size_t usersSize = currUsers.getSize();

	for (size_t i = 0; i < usersSize; i++) {
		if (userName == currUsers[i].getUserName())
			return i;
	}
	return SIZE_MAX;
}

size_t SocialNetwork::getCommentPosition(const size_t id, const Vector<Comment>& comments) const 
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

size_t SocialNetwork::findCorrespondingUserPosition(const size_t searchedUserId)
{
	size_t usersSize = currUsers.getSize();
	for (size_t userPos = 0; userPos < usersSize; ++userPos) {
		if (searchedUserId == currUsers[userPos].getId()) {
			return userPos;
		}
	}

	throw std::runtime_error("User not found");
}

size_t SocialNetwork::findCorrespondingTopicPosition(const size_t searchedTopicId)
{
	//Find corresponding topic

	size_t topicsSize = currTopics.getSize();

	
	for (size_t topicPos = 0; topicPos < topicsSize; ++topicPos) {

		if (searchedTopicId == currTopics[topicPos].getId()) {
			return topicPos;
		}
	}
	throw std::runtime_error("Topic not found");
}

size_t SocialNetwork::findCorrespondingPostPosition(const size_t searchedPostId, const size_t topicPos)
{
	//Find corresponding post
	size_t postsSize = currTopics[topicPos].getPosts().getSize();

	for (size_t postPos = 0; postPos < postsSize; ++postPos) {
		if (searchedPostId == currTopics[topicPos].getPosts()[postPos].getId()) {
			return postPos;
		}
	}
	throw std::runtime_error("Post not found");
}

const size_t SocialNetwork::chooseObject() const
{
	size_t objectId = SIZE_MAX;
	try {
		objectId = ConsoleInputGetter::recieveIdInput();
	}
	catch (const std::exception& e) {
		std::cout << "Could not choose object! " << e.what() << std::endl;
		throw;
	}
	return objectId;
}

void SocialNetwork::signup(const User& newUser)
{
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
		loggedInUserPos = findCorrespondingUserPosition(loggedInUser.getId());
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
	loggedInUserPos = SIZE_MAX;

	std::cout << "Logged out successfully!" << std::endl;
}

void SocialNetwork::editLoggedInUser()
{
	if (!isThereLoggedInUser()) {
		std::cout << "Only logged in users can edit their profiles! Please login first!" << std::endl;
		return;
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
			currUsers[loggedInUserPos].setUserName(newUser.getUserName());
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
			currUsers[loggedInUserPos].setPassword(newUser.getPassword());
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
			currUsers[loggedInUserPos].setFirstName(newUser.getFirstName());
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
			currUsers[loggedInUserPos].setLastName(newUser.getLastName());
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
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	size_t userPos = 0;
	try{
		userPos = findCorrespondingUserPosition(id);
	}
	catch (const std::runtime_error& e) {
		std::cout << "Could not edit user! " << e.what();
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
		bool newModeratorStatus = false;

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

	Topic tempTopic; //optimisation: create an empty topic (no posts, no comments) TODO : create new ctor with size_t PostsSize so it can be 0

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
				openedPostPos = SIZE_MAX;
				openedTopicPos = findCorrespondingTopicPosition(openedTopic.getId());
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
				openedPostPos = SIZE_MAX;
				openedTopicPos = findCorrespondingTopicPosition(openedTopic.getId());
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

	std::cout << "Current opened Topic: " << openedTopic.getTitle() << std::endl;

	size_t id = SIZE_MAX;

	try {
		id = ConsoleInputGetter::recieveIdInput();
	}

	catch (const std::exception&) {
		//std::cout << e.what() << std::endl;
		std::cout << "Could not open post! Invalid ID input!" << std::endl;
		return;
	}

	size_t postsSize = openedTopic.getPosts().getSize();
	bool postOpened = false;

	for (size_t i = 0; i < postsSize; ++i) {

		if (id == openedTopic.getPosts()[i].getId()) {
			openedPost = openedTopic.getPosts()[i];
			openedPostPos = findCorrespondingPostPosition(openedPost.getId(), openedTopicPos);
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


	currTopics[openedTopicPos].getPosts()[openedPostPos].addComment(newComment); // update currTopics vector
	openedPost.addComment(newComment); //update static object openedPost
	openedTopic.getPosts()[openedPostPos].addComment(newComment); //update static object openedTopic
	CurrentData::setChangesMadeStatus(true);

	std::cout << "Successfully commented!" << std::endl;
}

void SocialNetwork::replyToComment(const size_t parentId)
{
	if (!isThereLoggedInUser()) {
		throw std::runtime_error("Could not reply! Please log in before replying!");
	}

	if (!isThereOpenedTopic()) { //TOOD: remove? because we can't have an opened topic if we have an opened post. Remove everywhere else where we don't need this
		throw std::runtime_error("Could not reply! Please open a topic before replying!");
	}

	if (!isThereOpenedPost()) {
		throw std::runtime_error("Could not reply! Please open a post before replying!");
	}

	size_t commentPosition = getCommentPosition(parentId, openedPost.getComments());

	if (commentPosition == SIZE_MAX) {
		throw std::runtime_error("Comment not found!");
	}
	
	Reply parentCommentLastReply = openedPost.getComments()[commentPosition].getReplies().back();
	Reply newReply = ObjectFactory::createReply(*this, parentCommentLastReply, parentId);


	currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].addReply(newReply); //update currTopics vector
	openedPost.getComments()[commentPosition].addReply(newReply); //update static object openedPost
	openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].addReply(newReply); //update static object openedTopic
	CurrentData::setChangesMadeStatus(true);

	std::cout << "Successfully replied!" << std::endl;
}

const void SocialNetwork::printOpenedPostComments() const
{
	if (!isThereOpenedPost()) {
		std::cout << "Could not print comments and replies! Please open a post first!" << std::endl;
		return;
	}

	PrintHandler::printComments(openedPost.getComments());
}

void SocialNetwork::upvoteComment(const size_t commentId)
{
	if (!isThereLoggedInUser()) {
		std::cout << "Could not upvote comment! Please log in first!" << std::endl;
		return;
	}

	if (!isThereOpenedPost()) {
		std::cout << "Could not upvote comment! Please open a topic first!" << std::endl;
		return;
	}

	//check if comment exists

	size_t commentPosition = getCommentPosition(commentId, openedPost.getComments());

	if (commentPosition == SIZE_MAX) {
		std::cout << "Could not upvote comment! Comment doesn't exist!" << std::endl;
		return;
	}

	// check if comment is already reacted to, if downvoted or not reacted - continue, if upvoted - reject operation
	const Reaction* userReaction = openedPost.getComments()[commentPosition].getUserReaction(loggedInUser.getId());
	ReactionType reactionType = undefined;
	if (userReaction != nullptr) { //case 0.0: reaction exists
		reactionType = userReaction->getReactionType();
		if (reactionType == upvote) { //case 0.1: reaction is upvote - reject
			std::cout << "Could not upvote comment! You have already upvoted it!" << std::endl;
			return;
		}

		//case 0.2: reaction is downvote - continue
	}

	size_t authorId = currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].getAuthorId();
	size_t userPos = findCorrespondingUserPosition(authorId);

	if (reactionType == downvote) { //Increment by two to compensate for the change from downvote to upvote
		//update author points
		currUsers[userPos].incrementPoints(2);
		if (currUsers[userPos] == loggedInUser) {
			loggedInUser.incrementPoints(2);
		}


		//update currTopics
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].incrementScore(2);
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].changeReactionType(userReaction->getPosition(), upvote);

		//update openedTopic
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].incrementScore(2);
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].changeReactionType(userReaction->getPosition(), upvote);


		//update openedPost
		openedPost.getComments()[commentPosition].incrementScore(2);
		openedPost.getComments()[commentPosition].changeReactionType(userReaction->getPosition(), upvote);
	}

	else if(reactionType == undefined) { //case 1: reaction doesn't exist

		//update author points
		if (currUsers[userPos] == loggedInUser) {
			loggedInUser.incrementPoints(1);
		}
		currUsers[userPos].incrementPoints(1);

		Reaction newReaction(loggedInUser.getId(), upvote);

		//update currTopics
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].addReaction(newReaction);
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].incrementScore();

		//update openedTopic
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].addReaction(newReaction);
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].incrementScore();

		//update openedPost
		openedPost.getComments()[commentPosition].addReaction(newReaction);
		openedPost.getComments()[commentPosition].incrementScore();
	}

	CurrentData::setChangesMadeStatus(true);
	std::cout << "Upvoted successfully!" << std::endl;
}

void SocialNetwork::downvoteComment(const size_t commentId)
{
	if (!isThereLoggedInUser()) {
		std::cout << "Could not downvote comment! Please log in first!" << std::endl;
		return;
	}

	if (!isThereOpenedPost()) {
		std::cout << "Could not downvote comment! Please open a topic first!" << std::endl;
		return;
	}

	//check if comment exists

	size_t commentPosition = getCommentPosition(commentId, openedPost.getComments());

	if (commentPosition == SIZE_MAX) {
		std::cout << "Could not downvote comment! Comment doesn't exist!" << std::endl;
		return;
	}

	// check if comment is already reacted to, if upvoted or not reacted - continue, if downvoted - reject operation
	const Reaction* userReaction = openedPost.getComments()[commentPosition].getUserReaction(loggedInUser.getId());
	ReactionType reactionType = undefined;
	if (userReaction != nullptr) { //case 0.0: reaction exists
		reactionType = userReaction->getReactionType();
		if (reactionType == downvote) { //case 0.1: reaction is upvote - reject
			std::cout << "Could not downvoted comment! You have already downvoted it!" << std::endl;
			return;
		}

		//case 0.2: reaction is upvoted - continue
	}

	size_t authorId = currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].getAuthorId();
	size_t userPos = findCorrespondingUserPosition(authorId);

	if (reactionType == upvote) { //decrement by two to compensate for the change from upvote to downvote
		//update author points
		if (currUsers[userPos] == loggedInUser) {
			loggedInUser.decrementPoints(2);
		}
		currUsers[userPos].decrementPoints(2);


		//update currTopics
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].decrementScore(2);
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].changeReactionType(userReaction->getPosition(), downvote);

		//update openedTopic
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].decrementScore(2);
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].changeReactionType(userReaction->getPosition(), downvote);


		//update openedPost
		openedPost.getComments()[commentPosition].decrementScore(2);
		openedPost.getComments()[commentPosition].changeReactionType(userReaction->getPosition(), downvote);
	}


	else if(reactionType == undefined){ //case 1 reaction doesn't exist

		//update author points
		if (currUsers[userPos] == loggedInUser) {
			loggedInUser.decrementPoints(1);
		}
		currUsers[userPos].decrementPoints(1);

		Reaction newReaction(loggedInUser.getId(), downvote);

		//update currTopics
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].addReaction(newReaction);
		currTopics[openedTopicPos].getPosts()[openedPostPos].getComments()[commentPosition].decrementScore();

		//update openedTopic
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].addReaction(newReaction);
		openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].decrementScore();

		//update openedPost
		openedPost.getComments()[commentPosition].addReaction(newReaction);
		openedPost.getComments()[commentPosition].decrementScore();
	}

	CurrentData::setChangesMadeStatus(true);
	std::cout << "Downvoted successfully!" << std::endl;
}

void SocialNetwork::deleteComment(const size_t commentId) //TODO: this needs refactoring
{
	//check if comment exists

	size_t commentPosition = getCommentPosition(commentId, openedPost.getComments());

	if (commentPosition == SIZE_MAX) {
		std::cout << "Could not delete comment! Comment doesn't exist!" << std::endl;
		return;
	}

	bool isAuthor = (loggedInUser.getId() == openedPost.getComments()[commentPosition].getAuthorId());
	bool isModerator = loggedInUser.getModeratorStatus();
	
	if (!isAuthor && !isModerator) {
		std::cout << "Could not delete comment! Only author or moderators can delete comments!" << std::endl;

		return;
	}

	//update currUsers	
	int commentScore = openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].getScore(); //TODO: refactor method to not use get.get.get...
	size_t userPos = findCorrespondingUserPosition(openedTopic.getPosts()[openedPostPos].getComments()[commentPosition].getAuthorId());
	currUsers[userPos].decrementPoints(commentScore);

	//update loggedinuser
	if (isAuthor) {
		loggedInUser.decrementPoints(commentScore);
	}

	//update currTopics
	currTopics[openedTopicPos].getPosts()[openedPostPos].getComments().erase(commentPosition);

	//update openedTopic
	openedTopic.getPosts()[openedPostPos].getComments().erase(commentPosition);

	//update openedPost
	openedPost.getComments().erase(commentPosition);

	CurrentData::setChangesMadeStatus(true);
	std::cout << "Successfully deleted comment!" << std::endl;
}

void SocialNetwork::deletePost(const size_t postId)
{
	//check if post exists
	size_t postPosition = SIZE_MAX;

	try {
		postPosition = findCorrespondingPostPosition(postId, openedTopicPos);
	}
	catch (const std::runtime_error&) {
		std::cout << "Could not delete post! Post doesn't exist!" << std::endl;
		return;
	}
	
	if (openedPostPos == postPosition) {
		openedPost.clear();
		openedPostPos = SIZE_MAX;
	}

	//calculate comments Scores
	size_t commentsSize = currTopics[openedTopicPos].getPosts()[postPosition].getComments().getSize(); //TOOD : shouldnt we just use i instead of commentPosition?
	for (size_t i = 0; i < commentsSize; ++i) {
		
		//update currUsers
		int commentScore = openedTopic.getPosts()[postPosition].getComments()[i].getScore(); //TODO: refactor method to not use get.get.get...
		size_t userPos = findCorrespondingUserPosition(openedTopic.getPosts()[postPosition].getComments()[i].getAuthorId());
		currUsers[userPos].decrementPoints(commentScore);

		//update loggedinuser
		bool isAuthor = (loggedInUser.getId() == openedTopic.getPosts()[postPosition].getComments()[i].getAuthorId());
		if (isAuthor) {
			loggedInUser.decrementPoints(commentScore);
		}
	}

	//delete Post

	//update currTopics
	currTopics[openedTopicPos].getPosts().erase(postPosition);

	//update openedTopic
	openedTopic.getPosts().erase(postPosition);

	CurrentData::setChangesMadeStatus(true);
	std::cout << "Post deleted successfully!" << std::endl;
}

void SocialNetwork::deleteTopic(const size_t topicId)
{
	//check if topic exists
	size_t topicPosition = SIZE_MAX;

	try {
		topicPosition = findCorrespondingTopicPosition(topicId);
	}
	catch (const std::runtime_error&) {
		std::cout << "Could not delete topic! Topic doesn't exist!" << std::endl;
		return;
	}

	if (openedTopicPos == topicPosition) {

		if (openedPost.getTopicId() == openedTopic.getId()) {
			openedPost.clear();
			openedPostPos = SIZE_MAX;
		}

		openedTopic.clear();
		openedTopicPos = SIZE_MAX;	
	}
	
	size_t postsSize = currTopics[topicPosition].getPosts().getSize();
	for (size_t i = 0; i < postsSize; ++i) {

		//calculate commentsScores
		size_t commentsSize = currTopics[topicPosition].getPosts()[i].getComments().getSize();
		for (size_t j = 0; j < commentsSize; ++j) {
			int commentScore = currTopics[topicPosition].getPosts()[i].getComments()[j].getScore();
			size_t userPos = findCorrespondingUserPosition(currTopics[topicPosition].getPosts()[i].getComments()[j].getAuthorId());

			//update currUsers
			currUsers[userPos].decrementPoints(commentScore);

			//update loggedinuser
			bool isAuthor = (loggedInUser.getId() == currTopics[topicPosition].getPosts()[i].getComments()[j].getAuthorId());
			if (isAuthor) {
				loggedInUser.decrementPoints(commentScore);
			}
		}
	}
	//delete topic
	currTopics.erase(topicPosition);

	CurrentData::setChangesMadeStatus(true);
	std::cout << "Topic deleted successfully!" << std::endl;
}

void SocialNetwork::quitOpenedPost() 
{
	if (!isThereOpenedPost()) {
		std::cout << "There is no opened post to close!" << std::endl;
		return;
	}

	std::cout << "Post with title: " << openedPost.getTitle() << " - closed!" << std::endl;
	openedPost.clear();
	openedPostPos = SIZE_MAX;
}

void SocialNetwork::quitOpenedTopic()
{
	if (!isThereOpenedTopic()) {
		std::cout << "There is no opened topic to close!" << std::endl;
		return;
	}

	std::cout << "Topic with title: " << openedTopic.getTitle() << " - closed!" << std::endl;
	openedTopic.clear();
	openedTopicPos = SIZE_MAX;
	openedPost.clear();
	openedPostPos = SIZE_MAX;
}

const void SocialNetwork::exitProgram() const
{
	if (CurrentData::getChangesMadeStatus() == true) {

		bool answer = ConsoleInputGetter::getExitSavingAnswer();

		if (answer == true) {
			FileHandler::saveSocialNetwork(*this);
		}

		else {
			std::cout << "Exiting without saving." << std::endl;
			exit(0);
		}
	}
}