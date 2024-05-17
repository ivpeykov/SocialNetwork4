#include "FileHandler.h"

bool FileHandler::isFileEmpty(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "\nError opening !" << fileName << " by isFileEmpty";
		return true;
	}


	return file.peek() == std::ifstream::traits_type::eof();
}

void FileHandler::loadSocialNetwork(SocialNetwork& socialNetworkToLoad, bool& loadedStatus)
{

	ConsoleInputGetter::recieveSocialNetworkDirectoryInput();
	if (!InputValidator::isValidSocialNetworkDirectoryInput(ConsoleInputGetter::getSocialNetworkDirectoryInput())) { // TODO : move this code into the load method

		ConsoleInputGetter::resetSocialNetworkDirectoryInput();

		return;
	}

	socialNetworkToLoad.setDirectory(ConsoleInputGetter::getSocialNetworkDirectoryInput());

	const char* filePath = ConsoleInputGetter::getSocialNetworkDirectoryInput().getString();

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
		std::cout << "Successfully opened " << socialNetworkToLoad.getDirectory();
		return;
	}

	//If file exists, but is empty currSocialNetwork remains empty
	if (isFileEmpty(filePath)) {
		loadedStatus = true;
		std::cout << "Successfully opened " << socialNetworkToLoad.getDirectory();
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

	std::cout << "Successfully opened " << socialNetworkToLoad.getDirectory();
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
	ObjectFactory::setLastSignedUpUserId(newUser.getId());
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

		if (i != 0) {
			newTopic.getPosts().clear();
		}

		//load posts into topic
		loadPosts(socialNetworkFile, newTopic);

		topics.pushBack(newTopic);
	}
	ObjectFactory::setLastCreatedTopicId(newTopic.getId());
}

void FileHandler::loadPosts(std::fstream& socialNetworkFile, Topic& topic)
{
	size_t postsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&postsCount), sizeof(postsCount));

	if (postsCount == 0) {
		return;
	}

	topic.getPosts().resize(postsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Post newPost;
	size_t topicId = 0, creatorId = 0, id = 0;

	char* string = nullptr;

	for (size_t i = 0; i < postsCount; i++) {

		//load title
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newPost.setTitle(string);
		delete[] string;

		//load Content
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		newPost.setContent(string);
		delete[] string;


		//load topicId, creatorId, id
		socialNetworkFile.read(reinterpret_cast<char*>(&topicId), sizeof(topicId));
		socialNetworkFile.read(reinterpret_cast<char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		newPost.setTopicId(topicId);
		newPost.setCreatorId(creatorId);
		newPost.setId(id);

		if (i != 0) { //This is done because we don't want to drag the posts from the previous iteration
			newPost.getComments().clear();
		}
		//load comments
		loadComments(socialNetworkFile, newPost);

		topic.addPost(newPost);
	}
}

void FileHandler::loadComments(std::fstream& socialNetworkFile, Post& post)
{
	size_t commentsCount = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&commentsCount), sizeof(commentsCount));

	if (commentsCount == 0) return;

	post.getComments().resize(commentsCount + 10);
	//add 10 more places to save some time/resources

	size_t strLength = 0;

	Comment newComment;
	int score = 0;
	size_t id = 0, postId = 0;

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

		//load score, id, postsId
		socialNetworkFile.read(reinterpret_cast<char*>(&score), sizeof(score));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&postId), sizeof(postId));
		newComment.setScore(score);
		newComment.setId(id);
		newComment.setPostId(postId);

		if (i != 0) {
			newComment.getReplies().clear();
		}
		//load Replies
		loadReplies(socialNetworkFile, newComment);

		post.addComment(newComment);
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
	size_t id = SIZE_MAX, postId = SIZE_MAX, parentCommentId = SIZE_MAX; //TOOD: Iinitialise with SIZE_MAX everywhere

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

		//load score, id, postsId, parentCommentId
		socialNetworkFile.read(reinterpret_cast<char*>(&score), sizeof(score));
		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&postId), sizeof(postId));
		socialNetworkFile.read(reinterpret_cast<char*>(&parentCommentId), sizeof(parentCommentId));
		newReply.setScore(score);
		newReply.setId(id);
		newReply.setPostId(postId);
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
		//TODO: exception? handle this somehow
		return;
	}

	//SAVE USERS
	saveUsers(socialNetworkFile, socialNetwork.getCurrUsers());

	//SAVE TOPICS

	saveTopics(socialNetworkFile, socialNetwork.getCurrTopics());

	socialNetworkFile.close();

	std::cout << "Successfully saved " << socialNetwork.getDirectory() << std::endl;
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

		//save posts
		savePosts(socialNetworkFile, topics[i].getPosts());
	}
}

void FileHandler::savePosts(std::ofstream& socialNetworkFile, const Vector<Post>& posts)
{
	size_t postsCount = posts.getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&postsCount), sizeof(postsCount));

	size_t strLength = 0;

	for (size_t i = 0; i < postsCount; i++) {

		//save title
		strLength = posts[i].getTitle().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(posts[i].getTitle().getString(), strLength);

		//save content
		strLength = posts[i].getContent().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(posts[i].getContent().getString(), strLength);


		//save topicId, creatorId, id
		size_t topicId = posts[i].getTopicId();
		size_t creatorId = posts[i].getCreatorId();
		size_t id = posts[i].getId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&topicId), sizeof(topicId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&creatorId), sizeof(creatorId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

		//save comments
		saveComments(socialNetworkFile, posts[i].getComments());
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

		//save score, id, postId
		int score = comments[i].getScore();
		size_t id = comments[i].getId();
		size_t postId = comments[i].getPostId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&postId), sizeof(postId));

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

		//save score, id, postId, parentCommentId
		int score = replies[i].getScore();
		size_t id = replies[i].getId();
		size_t postId = replies[i].getPostId();
		size_t parentCommentId = replies[i].getParentCommentId();

		socialNetworkFile.write(reinterpret_cast<const char*>(&score), sizeof(score));
		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&postId), sizeof(postId));
		socialNetworkFile.write(reinterpret_cast<const char*>(&parentCommentId), sizeof(parentCommentId));

	}
}
