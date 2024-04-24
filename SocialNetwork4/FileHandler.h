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

	//generic methods
	// 
	//static bool isFileEmpty(const char* fileName); not needed for now

	static void loadSocialNetwork(const CustomString& filePath);

	static void saveSocialNetwork();


};