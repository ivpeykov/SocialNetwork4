#pragma once
#include "String.h"
#include "Vector.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "ConsoleInputGetter.h"
#include "CurrentData.h"
#include "PrintHandler.h"

class SocialNetwork
{
public:
	//constructors
	SocialNetwork(String& directory);
	SocialNetwork(const char* directory);

	//operators
	SocialNetwork& operator=(const SocialNetwork& other);

	//getters
	const String& getDirectory() const;
	Vector<User>& getCurrUsers();
	const Vector<User>& getCurrUsers() const;
	Vector<Topic>& getCurrTopics();
	const Vector<Topic>& getCurrTopics() const;

	static User& getLoggedInUser();
	static Topic& getOpenedTopic();
	static Post& getOpenedPost();

	//setters
	void setDirectory(const String& newDirectory);
	void setDirectory(const char* newDirectory);
	void setCurrUsers(const Vector<User>& newUsers);
	void setCurrTopics(const Vector<Topic>& newTopics);

	static void setLoggedInUser(const User& newUser);
	static void setOpenedTopic(const Topic& newTopic);
	static void setOpenedPost(const Post& newPost);

	//methods
	static bool isThereLoggedInUser();
	static bool isThereOpenedTopic();
	static bool isThereOpenedPost();

	size_t findCorrespondingUserPosition(const size_t searchedUserId);

	size_t findCorrespondingTopicPosition(const size_t searchedTopicId);

	size_t findCorrespondingPostPosition(const size_t searchedPostId, const size_t topicPos);

	bool isLoginSuccessful(User& user);

	size_t getUserPosition(const String& userName) const;
	size_t getCommentPosition(const size_t id, const Vector<Comment>& comments) const;

	const size_t chooseObject() const;

	//commands
	void signup(const User& newUser);

	void login();

	void logout();

	void editLoggedInUser();

	void editUserAsModerator();

	void addTopic(const Topic& newTopic);

	void searchTopic();

	void openTopic();

	void addPost(const Post& newPost);

	void listPostsInOpenedTopic() const;

	void openPost();

	const void printOpenedPostComments() const;

	void addComment(const Comment& newComment);

	void replyToComment(const size_t parentId);

	void upvoteComment(const size_t commentId);

	void downvoteComment(const size_t commentId);

	void deleteComment(const size_t commentId);

	void deletePost(const size_t postId);

	void deleteTopic(const size_t topicId);

	void quitOpenedPost();

	void quitOpenedTopic();

private:
	String directory;
	Vector<User> currUsers;
	Vector<Topic> currTopics;

	static User loggedInUser;
	static Topic openedTopic;
	static Post openedPost;

	static size_t loggedInUserPos;
	static size_t openedTopicPos;
	static size_t openedPostPos;
};