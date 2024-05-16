#include "ObjectFactory.h"

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
		size_t lastTopicId = socialNetwork.getCurrTopics().back().getId();
		newTopic.setId(lastTopicId + 1);
	}

	else {
		newTopic.setId(0);
	}

	return newTopic;
}

Discussion ObjectFactory::createDiscussion(const SocialNetwork& socialNetwork)
{
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Discussion could not be created! Please log in before posting!");
	}

	if (!socialNetwork.isThereOpenedTopic()) {
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
	newDiscussion.setTopicId(socialNetwork.getOpenedTopic().getId());

	//creatorId
	newDiscussion.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getOpenedTopic().getDiscussions().back().getTitle() != nullptr) {
		size_t lastDiscussionId = socialNetwork.getOpenedTopic().getDiscussions().back().getId();
		newDiscussion.setId(lastDiscussionId + 1);
	}

	else {
		newDiscussion.setId(0);
	}

	return newDiscussion;
}

Comment ObjectFactory::createComment(const SocialNetwork& socialNetwork)
{
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Comment could not be created! Please log in before commenting!");
	}

	if (!socialNetwork.isThereOpenedTopic()) {
		throw std::runtime_error("Comment could not be created! Please open a topic before commenting!");
	}

	if (!socialNetwork.isThereOpenedDiscussion()) {
		throw std::runtime_error("Comment could not be created! Please open a discussion before commenting!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setScore(0);
	newComment.setDiscussionId(socialNetwork.getOpenedDiscussion().getId());

	if (socialNetwork.getOpenedDiscussion().getComments().back().getAuthor() != nullptr) {
		size_t lastCommentId = socialNetwork.getOpenedDiscussion().getComments().back().getId();
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

	if (!socialNetwork.isThereOpenedDiscussion()) {
		throw std::runtime_error("Comment could not be created! Please open a discussion before replying!");
	}

	Comment newComment;

	ConsoleInputGetter::recieveCommentTextInput(newComment);
	if (!InputValidator::isValidCommentTextInput(newComment.getText())) {
		throw std::runtime_error("Comment could not be created! Invalid input!");
	}

	newComment.setAuthor(socialNetwork.getLoggedInUser().getUserName());
	newComment.setScore(0);
	newComment.setDiscussionId(socialNetwork.getOpenedDiscussion().getId());

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
