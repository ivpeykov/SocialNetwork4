#pragma once
#include <fstream>
#include "PrintHandler.h"
#include "CurrentData.h"
#include "User.h"
#include "Topic.h"
#include "Discussion.h"
#include "Comment.h"
#include "Vector.h"


class FileHandler
{
public:

	static bool isFileEmpty(const char* fileName); 

	static void loadSocialNetwork(const CustomString& filePath);

	static void loadUsers(std::fstream& socialNetworkFile);

	static void loadTopics(std::fstream& socialNetworkFile);

	static void loadDiscussions(std::fstream& socialNetworkFile, Topic& topic);

	static void loadComments(std::fstream& socialNetworkFile, Discussion& discussion);

	static void saveSocialNetwork();

	static void saveUsers(std::ofstream& socialNetworkFile);

	static void saveTopics(std::ofstream& socialNetworkFile);

	static void saveDiscussions(std::ofstream& socialNetworkFile, Vector<Discussion>& discussions);

	static void saveComments(std::ofstream& socialNetworkFile, Vector<Comment>& comments);
};