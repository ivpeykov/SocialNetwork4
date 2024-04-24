#pragma once
#include <iostream>
#include "CustomString.h"
#include "Configuration.h"
#include "CommandsHandler.h"

class InputValidator
{
public:

	static bool doesStringContainNonAsciiChars(const CustomString& string);

	static bool isValidCommandInput(const CustomString& commandInput);

	static bool isValidSocialNetworkDirectoryInput(const CustomString& directoryInput); // not implemented?


	//User Data Validation
	static bool isValidFirstName(const CustomString& firstName);
	static bool isValidLastName(const CustomString& lastName);
	static bool isValidUserName(const CustomString& userName);
	static bool isValidPassword(const CustomString& password);


	//Topic Data Validation
	//...



	//Discussion Data Validation
	//...



	//Comment Data Validation
	//...
};
