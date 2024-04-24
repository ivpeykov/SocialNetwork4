#pragma once
#include "User.h"
#include "CurrentData.h"

class PrintHandler
{
public:

	static void printEnterCommandPrompt();

	static void printUser(const User& user);

	static void printCurrUsers();

	static void printErrorSignupFirstName();
	static void printErrorSignupLastName();
	static void printErrorSignupUserName();
	static void printErrorSignupPassword();

};