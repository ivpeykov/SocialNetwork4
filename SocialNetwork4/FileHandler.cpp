#include "FileHandler.h"

bool FileHandler::isFileEmpty(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		//printHandler cries error!
		std::cout << "\nError opening !" << fileName << " by isFileEmpty"; //remove
		return true;
	}


	return file.peek() == std::ifstream::traits_type::eof();
}

void FileHandler::loadSocialNetwork(SocialNetwork& socialNetworkToLoad, bool& loadedStatus)
{
	const char* filePath = socialNetworkToLoad.getDirectory().getString();

	std::fstream socialNetworkFile(filePath, std::ios::binary | std::ios::in);

	//If file doesn't exist, create it
	if (!socialNetworkFile.is_open()) {
		std::cout << "File does not exist! Creating..." << std::endl;
		socialNetworkFile.open(filePath, std::ios::binary | std::ios::out);
		if (!socialNetworkFile.is_open()) {
			std::cout << "Could not create file!" << std::endl;
			return;
		}
		socialNetworkToLoad.setDirectory(filePath);
		loadedStatus = true;
		return;
	}

	//If file exists, but is empty currSocialNetwork remains empty
	if (isFileEmpty(filePath)) {
		loadedStatus = true;
		return;
	}

	//If file exists and isnt empty, read it...
	socialNetworkToLoad.getCurrUsers().clear();
	socialNetworkToLoad.getCurrTopics().clear();


	//LOAD USERS....................................................//
	loadUsers(socialNetworkFile, socialNetworkToLoad.getCurrUsers());


	//LOAD TOPICS.......................................................//
	loadTopics(socialNetworkFile, socialNetworkToLoad.getCurrTopics());

	socialNetworkFile.close();

	loadedStatus = true;
}

void FileHandler::loadUsers(std::fstream& socialNetworkFile, Vector<User>& users)
{
	size_t usersCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&usersCount), sizeof(usersCount));
	users.resize(usersCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	size_t id = 0;
	int points = 0;
	bool isModerator = false;

	User newUser;
	char* string = nullptr;

	for (size_t i = 0; i < usersCount; i++) {

		//load firstName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newUser.setFirstName(string);
		delete[] string;

		//load lastName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newUser.setLastName(string);
		delete[] string;

		//load userName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newUser.setUserName(string);
		delete[] string;

		//load password
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newUser.setPassword(string);
		delete[] string;

		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&points), sizeof(points));
		socialNetworkFile.read(reinterpret_cast<char*>(&isModerator), sizeof(isModerator));

		newUser.setId(id);
		newUser.setPoints(points);
		newUser.setModeratorStatus(isModerator);

		users.pushBack(newUser);
	}
}

void FileHandler::loadTopics(std::fstream& socialNetworkFile, Vector<Topic>& topics)
{
	size_t topicsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&topicsCount), sizeof(topicsCount));
	topics.resize(topicsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Topic newTopic;
	size_t creatorId = 0, id = 0;

	char* string = nullptr;

	for (size_t i = 0; i < topicsCount; i++) {

		//load title
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newTopic.setTitle(string);
		delete[] string;

		//load description
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newTopic.setDescription(string);
		delete[] string;

		//load creatorId, id
		socialNetworkFile.read(reinterpret_cast<char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		newTopic.setCreatorId(creatorId);
		newTopic.setId(id);

		//load discussions into topic
		loadDiscussions(socialNetworkFile, newTopic);

		topics.pushBack(newTopic);
	}
}

void FileHandler::loadDiscussions(std::fstream& socialNetworkFile, Topic& topic)
{
	size_t discussionsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&discussionsCount), sizeof(discussionsCount));

	if (discussionsCount == 0) {
		return;
	}

	topic.getDiscussions().resize(discussionsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Discussion newDiscussion;
	size_t topicId = 0, creatorId = 0, id = 0;

	char* string = nullptr;

	for (size_t i = 0; i < discussionsCount; i++) {

		//load title
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newDiscussion.setTitle(string);
		delete[] string;

		//load Content
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newDiscussion.setContent(string);
		delete[] string;


		//load topicId, creatorId, id
		socialNetworkFile.read(reinterpret_cast<char*>(&topicId), sizeof(topicId));
		socialNetworkFile.read(reinterpret_cast<char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		newDiscussion.setTopicId(topicId);
		newDiscussion.setCreatorId(creatorId);
		newDiscussion.setId(id);

		//load comments
		loadComments(socialNetworkFile, newDiscussion);

		topic.addDiscussion(newDiscussion);
	}
}

void FileHandler::loadComments(std::fstream& socialNetworkFile, Discussion& discussion)
{
	size_t commentsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&commentsCount), sizeof(commentsCount));

	if (commentsCount == 0) return;

	discussion.getComments().resize(commentsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Comment newComment;
	int score = 0;
	size_t id = 0, discussionId = 0;

	char* string = nullptr;

	for (size_t i = 0; i < commentsCount; i++) {

		//load author
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newComment.setAuthor(string);
		delete[] string;

		//load text
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newComment.setText(string);
		delete[] string;

		//load score, id, discussionsId
		socialNetworkFile.read(reinterpret_cast<char*>(&score), sizeof(score));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&discussionId), sizeof(discussionId));
		newComment.setScore(score);
		newComment.setId(id);
		newComment.setDiscussionId(discussionId);

		//load Replies
		loadReplies(socialNetworkFile, newComment);

		discussion.addComment(newComment);
	}
}

void FileHandler::loadReplies(std::fstream& socialNetworkFile, Comment& comment)
{
	size_t repliesCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&repliesCount), sizeof(repliesCount));


	if (repliesCount == 0) return;

	comment.getReplies().resize(repliesCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Reply newReply;
	int score = 0;
	size_t id = 0, discussionId = 0, parentCommentId = 0; //TOOD: Iinitialise with SIZE_MAX everywhere

	char* string = nullptr;


	for (size_t i = 0; i < repliesCount; i++) {
		//load author
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newReply.setAuthor(string);
		delete[] string;

		//load text
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newReply.setText(string);
		delete[] string;

		//load score, id, discussionsId, parentCommentId
		socialNetworkFile.read(reinterpret_cast<char*>(&score), sizeof(score));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&discussionId), sizeof(discussionId));
		socialNetworkFile.read(reinterpret_cast<char*>(&parentCommentId), sizeof(parentCommentId));
		newReply.setScore(score);
		newReply.setId(id);
		newReply.setDiscussionId(discussionId);
		newReply.setParentCommentId(parentCommentId);

		comment.addReply(newReply);
	}
}

void FileHandler::saveSocialNetwork(const SocialNetwork& socialNetwork)
{
	if (CurrentData::getChangesMadeStatus() == false) {
		std::cout << "No changes to save!" << std::endl;
		return;
	}
	
	const char* filepath = socialNetwork.getDirectory().getString();

	std::ofstream socialNetworkFile(filepath, std::ios::binary | std::ios::trunc);
	if (!socialNetworkFile.is_open()) {
		std::cout << "Error opening users file for saving!" << std::endl;
		//exception? handle this somehow
		return;
	}

	//SAVE USERS
	saveUsers(socialNetworkFile, socialNetwork.getCurrUsers());

	//SAVE TOPICS
	saveTopics(socialNetworkFile, socialNetwork.getCurrTopics());

	socialNetworkFile.close();

	std::cout << "Successfully saved social network data!" << std::endl;
}

void FileHandler::saveUsers(std::ofstream& socialNetworkFile, const Vector<User>& users)
{
	size_t usersCount = users.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&usersCount), sizeof(usersCount));

	size_t strLength = 0;
	for (size_t i = 0; i < usersCount; i++) {

		//save firstName
		strLength = users[i].getFirstName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(users[i].getFirstName().getString(), strLength);

		//save lastName
		strLength = users[i].getLastName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(users[i].getLastName().getString(), strLength);

		//save userName
		strLength = users[i].getUserName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(users[i].getUserName().getString(), strLength);

		//save password
		strLength = users[i].getPassword().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(users[i].getPassword().getString(), strLength);

		size_t id = users[i].getId();
		int points = users[i].getPoints();
		bool moderatorStatus = users[i].getModeratorStatus();

		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&points), sizeof(points));
		socialNetworkFile.write(reinterpret_cast<const char*>(&moderatorStatus), sizeof(moderatorStatus));

	}
}

void FileHandler::saveTopics(std::ofstream& socialNetworkFile, const Vector<Topic>& topics)
{
	size_t topicsCount = topics.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&topicsCount), sizeof(topicsCount));

	size_t strLength = 0;

	for (size_t i = 0; i < topicsCount; i++) {

		//save title
		strLength = topics[i].getTitle().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(topics[i].getTitle().getString(), strLength);

		//save description
		strLength = topics[i].getDescription().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(topics[i].getDescription().getString(), strLength);

		//save creatorId, id
		size_t creatorId = topics[i].getCreatorId();
		size_t id = topics[i].getId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

		//save discussions
		saveDiscussions(socialNetworkFile, topics[i].getDiscussions());
	}
}

void FileHandler::saveDiscussions(std::ofstream& socialNetworkFile, const Vector<Discussion>& discussions)
{
	size_t discussionsCount = discussions.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&discussionsCount), sizeof(discussionsCount));

	size_t strLength = 0;

	for (size_t i = 0; i < discussionsCount; i++) {

		//save title
		strLength = discussions[i].getTitle().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(discussions[i].getTitle().getString(), strLength);

		//save content
		strLength = discussions[i].getContent().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(discussions[i].getContent().getString(), strLength);


		//save topicId, creatorId, id
		size_t topicId = discussions[i].getTopicId();
		size_t creatorId = discussions[i].getCreatorId();
		size_t id = discussions[i].getId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&topicId), sizeof(topicId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

		//save comments
		saveComments(socialNetworkFile, discussions[i].getComments());
	}
}

void FileHandler::saveComments(std::ofstream& socialNetworkFile, const Vector<Comment>& comments)
{

	size_t commentsCount = comments.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&commentsCount), sizeof(commentsCount));

	size_t strLength = 0;

	for (size_t i = 0; i < commentsCount; i++) {

		//save author
		strLength = comments[i].getAuthor().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(comments[i].getAuthor().getString(), strLength);

		//save text
		strLength = comments[i].getText().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(comments[i].getText().getString(), strLength);

		//save score, id, discussionId
		int score = comments[i].getScore();
		size_t id = comments[i].getId();
		size_t discussionId = comments[i].getDiscussionId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&discussionId), sizeof(discussionId));

		//save replies
		saveReplies(socialNetworkFile, comments[i].getReplies());
	}

	
}

void FileHandler::saveReplies(std::ofstream& socialNetworkFile, const Vector<Reply>& replies)
{

	size_t repliesCount = replies.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&repliesCount), sizeof(repliesCount));

	size_t strLength = 0;

	for (size_t i = 0; i < repliesCount; i++) {

		//save author
		strLength = replies[i].getAuthor().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(replies[i].getAuthor().getString(), strLength);

		//save text
		strLength = replies[i].getText().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(replies[i].getText().getString(), strLength);

		//save score, id, discussionId, parentCommentId
		int score = replies[i].getScore();
		size_t id = replies[i].getId();
		size_t discussionId = replies[i].getDiscussionId();
		size_t parentCommentId = replies[i].getParentCommentId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&discussionId), sizeof(discussionId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&parentCommentId), sizeof(parentCommentId));

	}

}
