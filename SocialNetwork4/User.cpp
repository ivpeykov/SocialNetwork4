#include "User.h"

User::User() : firstName(nullptr), lastName(nullptr),
userName(nullptr), password(nullptr), id(0), points(0), isModerator(true) {} //for initialisation

User::User(const CustomString& firstName, const CustomString& lastName,
	const CustomString& userName, const CustomString& password,
	const unsigned id) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(0), isModerator(id == 0) {}

User::User(const char* firstName, const char*
	lastName, const char* userName, const char* password,
	const unsigned id) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(0), isModerator(id == 0) {}

User::User(const CustomString& firstName,
	const CustomString& lastName, const CustomString& userName,
	const CustomString& password, const unsigned id,
	const unsigned points, const bool isModerator) :
	firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(points), isModerator(isModerator) {} //for reading from files


User::User(const char* firstName, const char* lastName,
	const char* userName, const char* password, const unsigned id,
	const unsigned points, const bool isModerator) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(points), isModerator(isModerator) {} //for reading from files

User::User(const User& other) :
	firstName(other.firstName), lastName(other.lastName),
	userName(other.userName), password(other.password), id(other.id), points(other.points), isModerator(other.isModerator) {}

User::~User()
{
}


const CustomString& User::getFirstName() const
{
	return firstName;
}

const CustomString& User::getLastName() const
{
	return lastName;
}

const CustomString& User::getUserName() const
{
	return userName;
}

const CustomString& User::getPassword() const
{
	return password;
}

const unsigned User::getId() const
{
	return id;
}

const unsigned User::getPoints() const
{
	return points;
}

const bool User::getModeratorStatus() const
{
	return isModerator;
}

void User::setFirstName(const CustomString& newFirstName)
{
	firstName = newFirstName;
}

void User::setFirstName(const char* newFirstName)
{
	firstName = newFirstName;
}

void User::setLastName(const CustomString& newLastName)
{
	lastName = newLastName;
}

void User::setLastName(const char* newLastName)
{
	lastName = newLastName;
}

void User::setUserName(const CustomString& newUserName)
{
	userName = newUserName;
}

void User::setUserName(const char* newUserName)
{
	userName = newUserName;
}

void User::setPassword(const CustomString& newPassword)
{
	password = newPassword;
}

void User::setPassword(const char* newPassword)
{
	password = newPassword;
}

void User::setId(const unsigned newId)
{
	id = newId;
}

void User::setPoints(const unsigned newPoints)
{
	points = newPoints;
}

void User::setModeratorStatus(const bool newStatus)
{
	isModerator = newStatus;
}

bool User::isEqualWithoutId(const User& other) const
{
	return (firstName == other.firstName &&
		lastName == other.lastName &&
		userName == other.userName &&
		password == other.password &&
		points == other.points &&
		isModerator == other.isModerator);
}

bool User::isNotEqualWithoutId(const User& other) const
{
	return !isEqualWithoutId(other);
}

User& User::operator=(const User& other)
{
	if (this != &other) {

		firstName = other.firstName;
		lastName = other.lastName;
		userName = other.userName;
		password = other.password;
		id = other.id;
		points = other.points;
		isModerator = other.isModerator;
	}
	return *this;
}

bool User::operator==(const User& other) const
{
	return (id == other.id && isEqualWithoutId(other));
}

bool User::operator!=(const User& other) const
{
	return !(*this == other);
}