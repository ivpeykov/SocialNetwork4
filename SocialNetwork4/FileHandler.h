#pragma once
#include <fstream>
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "Comment.h"
#include "Vector.h"
 
class SocialNetwork;

class FileHandler
{
public:

	static bool isFileEmpty(const char* fileName); 

	static void loadSocialNetwork(SocialNetwork& socialNetworkToLoad, bool& loadedStatus);

	static void loadUsers(std::fstream& socialNetworkFile, Vector<User>& users);

	static void loadTopics(std::fstream& socialNetworkFile, Vector<Topic>& topics);

	static void loadPosts(std::fstream& socialNetworkFile, Topic& topic);

	static void loadComments(std::fstream& socialNetworkFile, Post& post);

	static void loadReplies(std::fstream& socialNetworkFile, Comment& comment);

	static void loadReactions(std::fstream& socialNetworkFile, Comment& comment);

	static void saveSocialNetwork(const SocialNetwork& socialNetwork);

	static void saveUsers(std::ofstream& socialNetworkFile, const Vector<User>& users);

	static void saveTopics(std::ofstream& socialNetworkFile, const Vector<Topic>& topics);

	static void savePosts(std::ofstream& socialNetworkFile,const Vector<Post>& posts);

	static void saveComments(std::ofstream& socialNetworkFile, const Vector<Comment>& comments);

	static void saveReplies(std::ofstream& socialNetworkFile, const Vector<Reply>& replies);

	static void saveReactions(std::ofstream& socialNetworkFile, const Vector<Reaction>& reactions);

private:
	FileHandler();
};