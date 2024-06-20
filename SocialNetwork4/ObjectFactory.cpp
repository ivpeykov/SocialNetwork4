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
	String userName;

	//UserName
	ConsoleInputGetter::recieveUserNameInput(userName);
	size_t userNameStatus = InputValidator::isValidUserNameSignup(userName);

	switch (userNameStatus) {

	case 0:
		throw std::runtime_error("Error creating User! Invalid Username!");
		break;
	case 1:
		break;
	case 2:
		throw std::runtime_error("Error creating User! User already exists!");
		break;
	default:
		throw std::logic_error("Error with usersStatus when signing up!");
	}

	//Password
	String password;

	ConsoleInputGetter::recievePasswordInput(password);
	if (!InputValidator::isValidPassword(password)) {
		throw std::runtime_error("Error creating User! Invalid Password!");
	}

	//FirstName
	String firstName;

	ConsoleInputGetter::recieveFirstNameInput(firstName);
	if (!InputValidator::isValidFirstName(firstName)) {
		throw std::runtime_error("Error creating User! Invalid First Name!");
	}

	//LastName
	String lastName;

	ConsoleInputGetter::recieveLastNameInput(lastName);
	if (!InputValidator::isValidLastName(lastName)) {
		throw std::runtime_error("Error creating User! Invalid Last Name!");
	}

	User newUser(firstName, lastName, userName, password, 0);

	//Moderator Status
	if (socialNetwork.getCurrUsers().back().getFirstName() != nullptr) {
		//ID
		newUser.setId(lastSignedUpUserId + 1);
		++lastSignedUpUserId;
	}

	else {		
		newUser.setModeratorStatus(true);
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

	//Title
	String title;
	ConsoleInputGetter::recieveTitleInput(title);
	if (!InputValidator::isValidTitle(title)) {
		throw std::runtime_error("Topic could not be created! Invalid Title!");
	}

	//Description
	String description;
	ConsoleInputGetter::recieveDescriptionInput(description);
	if (!InputValidator::isValidDescription(description)) {
		throw std::runtime_error("Topic could not be created! Invalid Description!");
	}

	Topic newTopic(title, description, 0, 0);

	//CreatorId
	newTopic.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getCurrTopics().back().getTitle() != nullptr) {
		newTopic.setId(lastCreatedTopicId + 1);
		++lastCreatedTopicId;
	}

	else {		
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

	//Title
	String title;
	ConsoleInputGetter::recievePostTitleInput(title);
	if (!InputValidator::isValidTitle(title)) {
		throw std::runtime_error("Post could not be created! Invalid Title!");
	}

	//Content
	String content;
	ConsoleInputGetter::recievePostContentInput(content);
	if (!InputValidator::isValidContent(content)) {
		throw std::runtime_error("Post could not be created! Invalid Content!");
	}

	Post newPost(title, content, 0, 0, 0);

	//topicId
	newPost.setTopicId(socialNetwork.getOpenedTopic().getId());

	//creatorId
	newPost.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getOpenedTopic().getPosts().back().getTitle() != nullptr) {
		size_t lastPostId = socialNetwork.getOpenedTopic().getPosts().back().getId();
		newPost.setId(lastPostId + 1);
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

	//text
	String text;

	ConsoleInputGetter::recieveCommentTextInput(text);
	if (!InputValidator::isValidCommentTextInput(text)) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	Comment newComment;

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setText(text);
	newComment.setScore(0);
	newComment.setPostId(socialNetwork.getOpenedPost().getId());
	newComment.setAuthorId(socialNetwork.getLoggedInUser().getId());

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
		throw std::runtime_error("Reply could not be created! Please open a post before replying!");
	}

	String text;

	ConsoleInputGetter::recieveCommentTextInput(text);
	if (!InputValidator::isValidCommentTextInput(text)) {
		throw std::runtime_error("Reply could not be created! Invalid input!");
	}

	Comment newComment;

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setText(text);
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
