#include "PrintHandler.h"

void PrintHandler::printEnterCommandPrompt() {
	std::cout << "\nEnter command: ";
}

void PrintHandler::printCommands(const String* commandsList, const String* commandsDescriptions, const size_t commandsCount)
{
	std::cout << "Available commands:" << std::endl;
	for (int i = 0; i < commandsCount; ++i) {
		std::cout << commandsList[i] << " - " << commandsDescriptions[i] << std::endl;
	}
}

void PrintHandler::printUser(const User& user)
{
	std::cout << "\nFirst name:" << user.getFirstName() << std::endl
		<< "Last name:" << user.getLastName() << std::endl
		<< "User name:" << user.getUserName() << std::endl
		<< "Password:" << user.getPassword() << std::endl
		<< "ID:" << user.getId() << std::endl
		<< "Points:" << user.getPoints() << std::endl
		<< "Is moderator:" << std::boolalpha << user.getModeratorStatus() << std::endl;
}

void PrintHandler::printTopic(const Topic& topic)
{
	std::cout << "\nTitle:" << topic.getTitle() << std::endl
		<< "Description:" << topic.getDescription() << std::endl
		<< "Creator Id:" << topic.getCreatorId() << std::endl
		<< "ID:" << topic.getId() << std::endl
		<< "Discussions:... " << std::endl;
	printDiscussions(topic);
}

void PrintHandler::printDiscussion(const Discussion& discussion)
{
	std::cout << "\nTitle:" << discussion.getTitle() << std::endl
		<< "Content:" << discussion.getContent() << std::endl
		<< "Topic Id:" << discussion.getTopicId() << std::endl
		<< "Creator Id: " << discussion.getCreatorId() << std::endl
		<< "ID:" << discussion.getId() << std::endl
		<< "Comments:... " << std::endl;
	printComments(discussion);
}

void PrintHandler::printComment(const Comment& comment)
{
	std::cout << "\nAuthor:" << comment.getAuthor() << std::endl
		<< "Text:" << comment.getText() << std::endl
		<< "Score:" << comment.getScore() << std::endl
		<< "ID:" << comment.getId() << std::endl
		<< "Discussion ID: " << comment.getDiscussionId() << std::endl
		<< "Replies..." << std::endl;
	printReplies(comment);
}

void PrintHandler::printReply(const Reply& reply)
{
	std::cout << "\nAuthor:" << reply.getAuthor() << std::endl
		<< "Text:" << reply.getText() << std::endl
		<< "Score:" << reply.getScore() << std::endl
		<< "ID:" << reply.getId() << std::endl
		<< "Discussion ID: " << reply.getDiscussionId() << std::endl
		<< "Parent comment ID: " << reply.getParentCommentId() << std::endl;
}

void PrintHandler::printUsers(const Vector<User>& users)
{
	std::cout << std::endl << "Printing users..." << std::endl;

	size_t usersSize = users.getSize();

	if (usersSize == 0) {
		std::cout << "No users!" << std::endl;
		return;
	}

	for (size_t i = 0; i < usersSize; i++) {
		printUser(users[i]);
	}
}

void PrintHandler::printTopics(const Vector<Topic>& topics)
{

	size_t topicsSize = topics.getSize();

	if (topicsSize == 0) {
		std::cout << "No topics!" << std::endl;
		return;
	}

	for (size_t i = 0; i < topicsSize; i++) {
		printTopic(topics[i]);
	}
}

void PrintHandler::printDiscussions(const Topic& topic)
{

	size_t discussionsSize = topic.getDiscussions().getSize();

	if (discussionsSize == 0) {
		std::cout << "No Discussions!" << std::endl;
		return;
	}

	for (size_t i = 0; i < discussionsSize; i++) {
		printDiscussion(topic.getDiscussions()[i]);
	}
}

void PrintHandler::printComments(const Discussion& discussion)
{
	size_t commentsSize = discussion.getComments().getSize();

	if (commentsSize == 0) {
		std::cout << "No Comments!" << std::endl;
		return;
	}

	for (size_t i = 0; i < commentsSize; i++) {
		printComment(discussion.getComments()[i]);
	}
}

void PrintHandler::printReplies(const Comment& comment)
{
	size_t repliesCount = comment.getReplies().getSize();

	if (repliesCount == 0) {
		std::cout << "No Replies!" << std::endl;
		return;
	}

	for (size_t i = 0; i < repliesCount; i++) {
		printReply(comment.getReplies()[i]);
	}

}

void PrintHandler::printTopicsForSearch(const Vector<Topic>& topics)
{
	size_t topicsSize = topics.getSize();

	if (topicsSize == 0) {
		std::cout << "No topics found containing that title!" << std::endl;
	}


	for (size_t i = 0; i < topicsSize; i++) {
		std::cout << topics[i].getTitle() << " {id: " << topics[i].getId() << "}" << std::endl;
	}

}

void PrintHandler::printDiscussionsForList(const Vector<Discussion>& discussions)
{
	size_t discussionsSize = discussions.getSize();

	if (discussionsSize == 0) {
		std::cout << "No discussions available in this topic!" << std::endl;
	}

	for (size_t i = 0; i < discussionsSize; ++i) {

		std::cout << discussions[i].getTitle() << " {id: "
			<< discussions[i].getId() << "}" << std::endl;

	}
}