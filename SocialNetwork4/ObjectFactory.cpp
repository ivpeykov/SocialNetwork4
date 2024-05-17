#include "ObjectFactory.h"

size_t ObjectFactory::lastSignedUpUserId = SIZE_MAX;
size_t ObjectFactory::lastCreatedTopicId = SIZE_MAX;

size_t ObjectFactory::getLastSignedUpUserId()
{
	return lastSignedUpUserId;
}

size_t ObjectFactory::getLastCreatedTopicId()
{
	return lastCreatedTopicId;
}

void ObjectFactory::setLastSignedUpUserId(const size_t newId)
{
	lastSignedUpUserId = newId;
}

void ObjectFactory::setLastCreatedTopicId(const size_t newId)
{
	lastCreatedTopicId = newId;
}

User ObjectFactory::createUser(const SocialNetwork& socialNetwork)
{
	User newUser;

	//UserName
	ConsoleInputGetter::recieveUserNameInput(newUser);
	size_t userNameStatus = InputValidator::isValidUserNameSignup(newUser.getUserName());

	switch (userNameStatus) {

	case 0:
		throw std::runtime_error("Error creating User! Invalid Username!!");
		break;
	case 1:
		break;
	case 2:
		throw std::runtime_error("Error creating User! User already exists!");
		break;
	default:
		throw std::exception("Error with usersStatus when signing up!");
	}

	//Password
	ConsoleInputGetter::recievePasswordInput(newUser);
	if (!InputValidator::isValidPassword(newUser.getPassword())) {
		throw std::runtime_error("Error creating User! Invalid Password!");
	}

	//FirstName
	ConsoleInputGetter::recieveFirstNameInput(newUser);
	if (!InputValidator::isValidFirstName(newUser.getFirstName())) {
		throw std::runtime_error("Error creating User! Invalid First Name!");
	}

	//LastName
	ConsoleInputGetter::recieveLastNameInput(newUser);
	if (!InputValidator::isValidLastName(newUser.getLastName())) {
		throw std::runtime_error("Error creating User! Invalid Last Name!");
	}

	//Moderator Status
	if (socialNetwork.getCurrUsers().back().getFirstName() != nullptr) {
		newUser.setModeratorStatus(false);
		//ID
		newUser.setId(lastSignedUpUserId + 1);
	}

	else {
		newUser.setId(0);
		lastSignedUpUserId = 0;
	}

	//Points are automatically 0 when creating a user

	return newUser;
}

Topic ObjectFactory::createTopic(const SocialNetwork& socialNetwork)
{
	//Ensure a logged in user creates the topic
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Topic could not be created! Please log in before creating!");
	}

	//advice recieved: get input for all the metadata and create a topic, then add it to the currTopics vector

	Topic newTopic;

	//Title
	ConsoleInputGetter::recieveTitleInput(newTopic);
	if (!InputValidator::isValidTitle(newTopic.getTitle())) {
		throw std::runtime_error("Topic could not be created! Invalid Title!");
	}

	//Description
	ConsoleInputGetter::recieveDescriptionInput(newTopic);
	if (!InputValidator::isValidDescription(newTopic.getDescription())) {
		throw std::runtime_error("Topic could not be created! Invalid Description!");
	}

	//CreatorId
	newTopic.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getCurrTopics().back().getTitle() != nullptr) {
		newTopic.setId(lastCreatedTopicId + 1);
	}

	else {
		newTopic.setId(0);
		lastCreatedTopicId = 0;
	}

	return newTopic;
}

Post ObjectFactory::createPost(const SocialNetwork& socialNetwork)
{
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Post could not be created! Please log in before posting!");
	}

	if (!socialNetwork.isThereOpenedTopic()) {
		throw std::runtime_error("Post could not be created! Please open a topic before posting!");
	}


	Post newPost; //optimisation: create an empty post ( no comments)

	//Title
	ConsoleInputGetter::recievePostTitleInput(newPost);
	if (!InputValidator::isValidTitle(newPost.getTitle())) {
		throw std::runtime_error("Post could not be created! Invalid Title!");
	}

	//Content
	ConsoleInputGetter::recievePostContentInput(newPost);
	if (!InputValidator::isValidContent(newPost.getContent())) {
		throw std::runtime_error("Post could not be created! Invalid Content!");
	}

	//topicId
	newPost.setTopicId(socialNetwork.getOpenedTopic().getId());

	//creatorId
	newPost.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getOpenedTopic().getPosts().back().getTitle() != nullptr) { 
		size_t lastPostId = socialNetwork.getOpenedTopic().getPosts().back().getId();
		newPost.setId(lastPostId + 1);
	}

	else {
		newPost.setId(0);
	}

	return newPost;
}

Comment ObjectFactory::createComment(const SocialNetwork& socialNetwork)
{
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Comment could not be created! Please log in before commenting!");
	}

	if (!socialNetwork.isThereOpenedTopic()) {
		throw std::runtime_error("Comment could not be created! Please open a topic before commenting!");
	}

	if (!socialNetwork.isThereOpenedPost()) {
		throw std::runtime_error("Comment could not be created! Please open a post before commenting!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setScore(0);
	newComment.setPostId(socialNetwork.getOpenedPost().getId());

	if (socialNetwork.getOpenedPost().getComments().back().getAuthor() != nullptr) {
		size_t lastCommentId = socialNetwork.getOpenedPost().getComments().back().getId();
		newComment.setId(lastCommentId + 1);
	}

	else {
		newComment.setId(0);
	}

	return newComment;
}

Reply ObjectFactory::createReply(const SocialNetwork& socialNetwork, const Reply& parentCommentLastReply, const size_t parentCommentId)
{
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Reply could not be created! Please log in before replying!");
	}

	if (!socialNetwork.isThereOpenedTopic()) {
		throw std::runtime_error("Reply could not be created! Please open a topic before replying!");
	}

	if (!socialNetwork.isThereOpenedPost()) {
		throw std::runtime_error("Comment could not be created! Please open a post before replying!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setScore(0);
	newComment.setPostId(socialNetwork.getOpenedPost().getId());

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
