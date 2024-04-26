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

void FileHandler::loadSocialNetwork(const CustomString& filePath)
{
	std::fstream socialNetworkFile(filePath.getString(), std::ios::binary | std::ios::in);

	//If file doesn't exist, create it
	if (!socialNetworkFile.is_open()) {
		std::cout << "File does not exist! Creating..." << std::endl;
		socialNetworkFile.open(filePath.getString(), std::ios::binary | std::ios::out);
		if (!socialNetworkFile.is_open()) {
			std::cout << "Could not create file!" << std::endl;
			return;
		}
		CurrentData::getCurrSocialNetwork().setDirectory(filePath);
		return;
	}

	//If file exists, but is empty currSocialNetwork remains empty
	if (isFileEmpty(filePath.getString()))
		return;

	//If file exists and isnt empty, read it...
	CurrentData::getCurrSocialNetwork().getCurrUsers().clear();
	CurrentData::getCurrSocialNetwork().getCurrTopics().clear();


	//LOAD USERS....................................................//
	loadUsers(socialNetworkFile);


	//LOAD TOPICS.......................................................//
	loadTopics(socialNetworkFile);


	socialNetworkFile.close();
}

void FileHandler::loadUsers(std::fstream& socialNetworkFile)
{
	size_t usersCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&usersCount), sizeof(usersCount));
	CurrentData::getCurrSocialNetwork().getCurrUsers().resize(usersCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	unsigned id = 0, points = 0;
	bool isModerator = false;

	User newUser;
	char* string = nullptr;

	for (int i = 0; i < usersCount; i++) {

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

		CurrentData::getCurrSocialNetwork().getCurrUsers().pushBack(newUser);
	}
}

void FileHandler::loadTopics(std::fstream& socialNetworkFile)
{
	size_t topicsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&topicsCount), sizeof(topicsCount));
	CurrentData::getCurrSocialNetwork().getCurrTopics().resize(topicsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Topic newTopic;
	unsigned creatorId = 0, id = 0;

	char* string = nullptr;

	for (int i = 0; i < topicsCount; i++) {

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

		CurrentData::getCurrSocialNetwork().getCurrTopics().pushBack(newTopic);
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
	unsigned topicId = 0, creatorId = 0, id = 0;

	char* string = nullptr;

	for (int i = 0; i < discussionsCount; i++) {

		//load title
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newDiscussion.setTitle(string);
		delete[] string;

		//load description
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newDiscussion.setDescription(string);
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
	unsigned score = 0, id = 0, discussionId = 0;

	char* string = nullptr;

	for (int i = 0; i < commentsCount; i++) {

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


		discussion.addComment(newComment);
	}
}

void FileHandler::saveSocialNetwork()
{
	if (CurrentData::getChangesMadeStatus() == false) {
		std::cout << "No changes to save!" << std::endl;
		return;
	}

	const char* filepath = CurrentData::getCurrSocialNetwork().getDirectory().getString();

	std::ofstream socialNetworkFile(filepath, std::ios::binary | std::ios::trunc);
	if (!socialNetworkFile.is_open()) {
		std::cout << "Error opening users file for saving!" << std::endl;
		//exception? handle this somehow
		return;
	}

	//SAVE USERS
	saveUsers(socialNetworkFile);

	//SAVE TOPICS
	saveTopics(socialNetworkFile);

	socialNetworkFile.close();
}

void FileHandler::saveUsers(std::ofstream& socialNetworkFile)
{
	size_t usersCount = CurrentData::getCurrSocialNetwork().getCurrUsers().getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&usersCount), sizeof(usersCount));

	size_t strLength = 0;
	for (int i = 0; i < usersCount; i++) {

		User userToSave = CurrentData::getCurrSocialNetwork().getCurrUsers()[i];

		//save firstName
		strLength = userToSave.getFirstName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getFirstName().getString(), strLength);

		//save lastName
		strLength = userToSave.getLastName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getLastName().getString(), strLength);

		//save userName
		strLength = userToSave.getUserName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getUserName().getString(), strLength);

		//save password
		strLength = userToSave.getPassword().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getPassword().getString(), strLength);

		unsigned id = userToSave.getId();
		unsigned points = userToSave.getPoints();
		bool moderatorStatus = userToSave.getModeratorStatus();

		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&points), sizeof(points));
		socialNetworkFile.write(reinterpret_cast<const char*>(&moderatorStatus), sizeof(moderatorStatus));

	}
}

void FileHandler::saveTopics(std::ofstream& socialNetworkFile)
{
	size_t topicsCount = CurrentData::getCurrSocialNetwork().getCurrTopics().getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&topicsCount), sizeof(topicsCount));

	size_t strLength = 0;

	for (int i = 0; i < topicsCount; i++) {

		Topic topicToSave = CurrentData::getCurrSocialNetwork().getCurrTopics()[i];

		//save title
		strLength = topicToSave.getTitle().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(topicToSave.getTitle().getString(), strLength);

		//save description
		strLength = topicToSave.getDescription().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(topicToSave.getDescription().getString(), strLength);

		//save creatorId, id
		unsigned creatorId = topicToSave.getCreatorId();
		unsigned id = topicToSave.getId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

		//save discussions
		//saveDiscussions(socialNetworkFile, topicToSave.getDiscussions());
	}
}

void FileHandler::saveDiscussions(std::ofstream& socialNetworkFile, Vector<Discussion>& discussions)
{
	size_t discussionsCount = discussions.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&discussionsCount), sizeof(discussionsCount));

	size_t strLength = 0;

	for (int i = 0; i < discussionsCount; i++) {

		//save title
		strLength = discussions[i].getTitle().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(discussions[i].getTitle().getString(), strLength);

		//save description
		strLength = discussions[i].getDescription().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(discussions[i].getDescription().getString(), strLength);


		//save topicId, creatorId, id
		unsigned topicId = discussions[i].getTopicId();
		unsigned creatorId = discussions[i].getCreatorId();
		unsigned id = discussions[i].getId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&topicId), sizeof(topicId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

		//save comments
		saveComments(socialNetworkFile, discussions[i].getComments());
	}
}

void FileHandler::saveComments(std::ofstream& socialNetworkFile, Vector<Comment>& comments)
{

	size_t commentsCount = comments.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&commentsCount), sizeof(commentsCount));

	size_t strLength = 0;

	for (int i = 0; i < commentsCount; i++) {

		//save author
		strLength = comments[i].getAuthor().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(comments[i].getAuthor().getString(), strLength);

		//save text
		strLength = comments[i].getText().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(comments[i].getText().getString(), strLength);

		//save score, id, discussionId
		unsigned score = comments[i].getScore();
		unsigned id = comments[i].getId();
		unsigned discussionId = comments[i].getDiscussionId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&discussionId), sizeof(discussionId));
	}
}
