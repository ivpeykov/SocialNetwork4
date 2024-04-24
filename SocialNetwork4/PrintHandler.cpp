#include "PrintHandler.h"

void PrintHandler::printEnterCommandPrompt() {
	std::cout << "\nEnter command: ";
}

void PrintHandler::printUser(const User& user)
{
	std::cout << "\nFirst name:" << user.getFirstName() << std::endl
		<< "Last name:" << user.getLastName() << std::endl
		<< "User name:" << user.getUserName() << std::endl
		<< "Password:" << user.getPassword() << std::endl
		<< "ID:" << user.getId() << std::endl
		<< "Points:" << user.getPoints() << std::endl
		<< "Is moderator:" << std::boolalpha << user.getModeratorStatus() << std::endl;
}

void PrintHandler::printCurrUsers()
{
	size_t usersSize = CurrentData::getCurrSocialNetwork().getCurrUsers().getSize();

	for (int i = 0; i < usersSize; i++) {
		printUser(CurrentData::getCurrSocialNetwork().getCurrUsers()[i]);
	}
}

void PrintHandler::printErrorSignupFirstName()
{
	std::cerr << "\nError creating Account! Invalid First Name!" << std::endl;
}

void PrintHandler::printErrorSignupLastName()
{
	std::cerr << "\nError creating Account! Invalid Last Name!" << std::endl;
}

void PrintHandler::printErrorSignupUserName()
{
	std::cerr << "\nError creating Account! Invalid Username!" << std::endl;
}

void PrintHandler::printErrorSignupPassword()
{
	std::cerr << "\nError creating Account! Invalid Password!" << std::endl;
}

