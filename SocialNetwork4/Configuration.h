#pragma once
#include "CustomString.h"


//Try configuring the COMMAND_INPUT_MAX_LENGTH at compile time

class Configuration
{

public:

	

	static const unsigned short FIRST_NAME_MAX_LENGTH = 128; //contains \0 char
	static const unsigned short LAST_NAME_MAX_LENGTH = 128; //contains \0 char
	static const unsigned short USER_NAME_MAX_LENGTH = 128; //contains \0 char
	static const unsigned short PASSWORD_MAX_LENGTH = 64; //contains \0 char
	static const unsigned short TOPIC_TITLE_MAX_LENGTH = 128;
	static const unsigned TOPIC_DESCRIPTION_MAX_LENGTH = 512;
	static const unsigned DISCUSSION_TITLE_MAX_LENGTH = 64;
	static const unsigned DISCUSSION_DESCRIPTION_MAX_LENGTH = 2048;
	static const unsigned COMMENT_AUTHOR_NAME_MAX_LENGTH = 128;
	static const unsigned COMMENT_TEXT_MAX_LENGTH = 512;
	static const unsigned short COMMAND_INPUT_MAX_LENGTH = 10; // Longest command + \0 length. Adjust if more commands are added
	static const short MAX_DIGITS_INPUT;

	static constexpr short calculate_MAX_DIGITS_INPUT();
};

