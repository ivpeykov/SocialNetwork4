#pragma once
#include <fstream>
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"
#include "Discussion.h"
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

	static void loadDiscussions(std::fstream& socialNetworkFile, Topic& topic);

	static void loadComments(std::fstream& socialNetworkFile, Discussion& discussion);

	static void loadReplies(std::fstream& socialNetworkFile, Comment& comment);

	static void saveSocialNetwork(const SocialNetwork& socialNetwork);

	static void saveUsers(std::ofstream& socialNetworkFile, const Vector<User>& users);

	static void saveTopics(std::ofstream& socialNetworkFile, const Vector<Topic>& topics);

	static void saveDiscussions(std::ofstream& socialNetworkFile,const Vector<Discussion>& discussions);

	static void saveComments(std::ofstream& socialNetworkFile, const Vector<Comment>& comments);

	static void saveReplies(std::ofstream& socialNetworkFile, const Vector<Reply>& replies);
};