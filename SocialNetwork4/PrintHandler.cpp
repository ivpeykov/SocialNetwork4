#include "PrintHandler.h"

void PrintHandler::printEnterCommandPrompt() {
	std::cout << "\nEnter command: ";
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
		<< "Description:" << discussion.getDescription() << std::endl
		<< "Topic Id:" << discussion.getTopicId() << std::endl
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
		<< "Discussion ID: " << comment.getDiscussionId() << std::endl;
}

void PrintHandler::printUsers(const Vector<User>& users)
{
	std::cout << std::endl << "Printing users..." << std::endl;

	size_t usersSize = users.getSize();

	for (int i = 0; i < usersSize; i++) {
		printUser(users[i]);
	}
}

void PrintHandler::printTopics(const Vector<Topic>& topics)
{
	std::cout <<  std::endl << "Printing Topics..." << std::endl;

	size_t topicsSize = topics.getSize();

	for (int i = 0; i < topicsSize; i++) {
		printTopic(topics[i]);
	}

}

void PrintHandler::printDiscussions(const Topic& topic)
{
	std::cout << std::endl << "Printing Discussions..." << std::endl;

	size_t discussionsSize = topic.getDiscussions().getSize();

	if (discussionsSize == 0) {
		return;
	}

	for (int i = 0; i < discussionsSize; i++) {
		printDiscussion(topic.getDiscussions()[i]);
	}

}

void PrintHandler::printComments(const Discussion& discussion)
{
	size_t commentsSize = discussion.getComments().getSize();

	for (int i = 0; i < commentsSize; i++) {
		printComment(discussion.getComments()[i]);
	}
}

void PrintHandler::printTopicsForSearch(const Vector<Topic>& topics)
{
	size_t topicsSize = topics.getSize();

	if (topicsSize == 0) {
		std::cout << "No strings found containing that string!" << std::endl;
	}


	for (int i = 0; i < topicsSize; i++) {
		std::cout << topics[i].getTitle() << " {id: " << topics[i].getId() << "}" << std::endl;
	}

}

void PrintHandler::printDiscussionsForList(const Vector<Discussion>& discussions)
{
	size_t discussionsSize = discussions.getSize();

	if (discussionsSize == 0) {
		std::cout << "No discussions avalible in this topic!" << std::endl;
	}

	for (int i = 0; i < discussionsSize; ++i) {

		std::cout << discussions[i].getTitle() << " {id: "
			<< discussions[i].getId() << "}" << std::endl;

	}

}

void PrintHandler::printErrorSignupFirstName()
{
	std::cerr << "\nError creating Account! Invalid First Name!" << std::endl;
}

void PrintHandler::printErrorSignupLastName()
{
	std::cerr << "\nError creating Account! Invalid Last Name!" << std::endl;
}

void PrintHandler::printErrorSignupUserName()
{
	std::cerr << "\nError creating Account! Invalid Username!" << std::endl;
}

void PrintHandler::printErrorSignupPassword()
{
	std::cerr << "\nError creating Account! Invalid Password!" << std::endl;
}

void PrintHandler::printErrorLoginUserName()
{
	std::cerr << "\nInvalid Username!" << std::endl;
}

void PrintHandler::printErrorLoginPassword()
{
	std::cerr << "\nInvalid Password!" << std::endl;
}

void PrintHandler::printErrorCreateTitle()
{
	std::cerr << "\nError creating Topic! Invalid Title!" << std::endl;
}

void PrintHandler::printErrorCreateDescription()
{
	std::cerr << "\nError creating Topic! Invalid Description!" << std::endl;
}
