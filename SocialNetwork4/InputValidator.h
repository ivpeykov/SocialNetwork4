#pragma once
#include <iostream>
#include "CustomString.h"
#include "Configuration.h"
#include "CommandsHandler.h"

class InputValidator
{
public:

	static bool doesStringContainNonAsciiChars(const CustomString& string);

	static bool doesStringContainNonAsciiChars(const char* string);

	static bool isValidCommandInput(const CustomString& commandInput);

	static bool isValidSocialNetworkDirectoryInput(const CustomString& directoryInput);


	//User Data Validation
	static bool isValidFirstName(const CustomString& firstName);
	static bool isValidLastName(const CustomString& lastName);
	static bool isValidUserNameSignup(const CustomString& userName);
	static bool isValidUserNameLogin(const CustomString& userName);
	static bool isValidPassword(const CustomString& password);
	static bool isValidAnswerInputForEditing(const short answer, const short maxAnswerValue);

	//Topic Data Validation
	static bool isValidTitle(const CustomString& title);
	static bool isValidDescription(const CustomString& description);



	//Discussion Data Validation
	static bool isValidContent(const CustomString& content);



	//Comment Data Validation
	static bool isValidCommentTextInput(const CustomString& text);
};
