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
	std::cout << "\nTOPIC\nTitle:" << topic.getTitle() << std::endl
		<< "Description:" << topic.getDescription() << std::endl
		<< "Creator Id:" << topic.getCreatorId() << std::endl
		<< "ID:" << topic.getId() << std::endl
		<< "Posts:... " << std::endl;
	printPosts(topic.getPosts());
}

void PrintHandler::printPost(const Post& post)
{
	std::cout << "\nPOST\nTitle:" << post.getTitle() << std::endl
		<< "Content:" << post.getContent() << std::endl
		<< "Topic Id:" << post.getTopicId() << std::endl
		<< "Creator Id: " << post.getCreatorId() << std::endl
		<< "ID:" << post.getId() << std::endl
		<< "Comments:... " << std::endl;
	printComments(post.getComments());
}

void PrintHandler::printComment(const Comment& comment)
{
	std::cout << "\nCOMMENT\nAuthor:" << comment.getAuthor() << std::endl
		<< "Text:" << comment.getText() << std::endl
		<< "Score:" << comment.getScore() << std::endl
		<< "ID:" << comment.getId() << std::endl
		<< "Post ID: " << comment.getPostId() << std::endl
		<< "Replies..." << std::endl;
	printReplies(comment.getReplies());
}

void PrintHandler::printReply(const Reply& reply)
{
	std::cout << "\nREPLY\nAuthor:" << reply.getAuthor() << std::endl
		<< "Text:" << reply.getText() << std::endl
		<< "Score:" << reply.getScore() << std::endl
		<< "ID:" << reply.getId() << std::endl
		<< "Post ID: " << reply.getPostId() << std::endl
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

void PrintHandler::printPosts(const Vector<Post>& posts)
{

	size_t postsSize = posts.getSize();

	if (postsSize == 0) {
		std::cout << "No Posts!" << std::endl;
		return;
	}

	for (size_t i = 0; i < postsSize; i++) {
		printPost(posts[i]);
	}
}

void PrintHandler::printComments(const Vector<Comment>& comments)
{
	size_t commentsSize = comments.getSize();

	if (commentsSize == 0) {
		std::cout << "No Comments!" << std::endl;
		return;
	}

	for (size_t i = 0; i < commentsSize; i++) {
		printComment(comments[i]);
	}
}

void PrintHandler::printReplies(const Vector<Reply>& replies)
{
	size_t repliesCount = replies.getSize();

	if (repliesCount == 0) {
		std::cout << "No Replies!" << std::endl;
		return;
	}

	for (size_t i = 0; i < repliesCount; i++) {
		printReply(replies[i]);
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

void PrintHandler::printPostsForList(const Vector<Post>& posts)
{
	size_t postsSize = posts.getSize();

	if (postsSize == 0) {
		std::cout << "No posts available in this topic!" << std::endl;
	}

	for (size_t i = 0; i < postsSize; ++i) {

		std::cout << posts[i].getTitle() << " {id: "
			<< posts[i].getId() << "}" << std::endl;

	}
}