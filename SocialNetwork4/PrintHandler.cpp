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

void PrintHandler::safePrint(const char* label, const String& value)
{
    if (!value.isEmpty()) {
        std::cout << label << value << std::endl;
    }
    else {
        std::cout << label << "[Not available]" << std::endl;
    }
}

void PrintHandler::printUser(const User& user)
{
    std::cout << "\nUser details:\n";
    safePrint("First name: ", user.getFirstName());
    safePrint("Last name: ", user.getLastName());
    safePrint("User name: ", user.getUserName());
    safePrint("Password: ", user.getPassword());

    std::cout << "ID: " << user.getId() << std::endl;
    std::cout << "Points: " << user.getPoints() << std::endl;
    std::cout << "Is moderator: " << std::boolalpha << user.getModeratorStatus() << std::endl;
}

void PrintHandler::printTopic(const Topic& topic)
{
    std::cout << "\nTOPIC\n";
    safePrint("Title: ", topic.getTitle());
    safePrint("Description: ", topic.getDescription());
    std::cout << "Creator Id: " << topic.getCreatorId() << std::endl;
    std::cout << "ID: " << topic.getId() << std::endl;
    std::cout << "Posts:... " << std::endl;
    printPosts(topic.getPosts());
}

void PrintHandler::printPost(const Post& post)
{
    std::cout << "\nPOST\n";
    safePrint("Title: ", post.getTitle());
    safePrint("Content: ", post.getContent());
    std::cout << "Topic Id: " << post.getTopicId() << std::endl;
    std::cout << "Creator Id: " << post.getCreatorId() << std::endl;
    std::cout << "ID: " << post.getId() << std::endl;
    std::cout << "Comments:... " << std::endl;
    printComments(post.getComments());
}

void PrintHandler::printComment(const Comment& comment)
{
    std::cout << "\nCOMMENT\n";
    safePrint("Author: ", comment.getAuthor());
    safePrint("Text: ", comment.getText());
    std::cout << "Score: " << comment.getScore() << std::endl;
    std::cout << "ID: " << comment.getId() << std::endl;
    std::cout << "Post ID: " << comment.getPostId() << std::endl;
    std::cout << "Replies:... " << std::endl;
    printReplies(comment.getReplies());
}

void PrintHandler::printReply(const Reply& reply)
{
    std::cout << "\nREPLY\n";
    safePrint("Author: ", reply.getAuthor());
    safePrint("Text: ", reply.getText());
    std::cout << "Score: " << reply.getScore() << std::endl;
    std::cout << "ID: " << reply.getId() << std::endl;
    std::cout << "Post ID: " << reply.getPostId() << std::endl;
    std::cout << "Parent comment ID: " << reply.getParentCommentId() << std::endl;
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