#pragma once
#include "String.h"

class Configuration
{

public:

	
	//all contain \0 char
	static const unsigned short FIRST_NAME_MAX_LENGTH = 128;
	static const unsigned short LAST_NAME_MAX_LENGTH = 128; 
	static const unsigned short USER_NAME_MAX_LENGTH = 128; 
	static const unsigned short PASSWORD_MAX_LENGTH = 64;
	static const unsigned short TOPIC_TITLE_MAX_LENGTH = 128;
	static const unsigned TOPIC_DESCRIPTION_MAX_LENGTH = 2048;
	static const unsigned POST_TITLE_MAX_LENGTH = 64;
	static const unsigned POST_CONTENT_MAX_LENGTH = 40000;
	static const unsigned COMMENT_AUTHOR_NAME_MAX_LENGTH = 128;
	static const unsigned COMMENT_TEXT_MAX_LENGTH = 10000;
	static const unsigned short COMMAND_INPUT_MAX_LENGTH = 15; // Longest command + \0 length. Adjust if more commands are added
	static const short MAX_DIGITS_INPUT;

	static constexpr short calculate_MAX_DIGITS_INPUT();

private:
	Configuration();
};

