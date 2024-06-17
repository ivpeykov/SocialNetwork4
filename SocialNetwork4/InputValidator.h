#pragma once
#include <iostream>
#include "String.h"
#include "Configuration.h"
#include "CommandsHandler.h"

class InputValidator
{
public:

	static bool doesStringContainNonAsciiChars(const String& string);

	static bool doesStringContainNonAsciiChars(const char* string);

	static bool isValidCommandInput(const String& commandInput);

	static bool isValidSocialNetworkDirectoryInput(const String& directoryInput);


	//User Data Validation
	static bool isValidFirstName(const String& firstName);
	static bool isValidLastName(const String& lastName);
	static size_t isValidUserNameSignup(const String& userName);
	static bool isValidUserNameLogin(const String& userName);
	static bool isValidPassword(const String& password);
	static bool isValidAnswerInputForEditing(const short answer, const short maxAnswerValue);

	//Topic Data Validation
	static bool isValidTitle(const String& title);
	static bool isValidDescription(const String& description);



	//Post Data Validation
	static bool isValidContent(const String& content);



	//Comment Data Validation
	static bool isValidCommentTextInput(const String& text);

private:
	InputValidator();
};


