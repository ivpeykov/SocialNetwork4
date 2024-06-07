#include "User.h"

//constructors and destructor
User::User() : firstName(nullptr), lastName(nullptr),
userName(nullptr), password(nullptr), id(SIZE_MAX), points(0), isModerator(false) {} //for initialisation

User::User(const String& firstName, const String& lastName,
	const String& userName, const String& password,
	const size_t id) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(0), isModerator(id == 0) {}

User::User(const char* firstName, const char*
	lastName, const char* userName, const char* password,
	const size_t id) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(0), isModerator(id == 0) {}

User::User(const String& firstName,
	const String& lastName, const String& userName,
	const String& password, const size_t id,
	const int points, const bool isModerator) :
	firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(points), isModerator(isModerator) {} //for reading from files


User::User(const char* firstName, const char* lastName,
	const char* userName, const char* password, const size_t id,
	const int points, const bool isModerator) : firstName(firstName), lastName(lastName),
	userName(userName), password(password), id(id), points(points), isModerator(isModerator) {} //for reading from files

User::User(const User& other) :
	firstName(other.firstName), lastName(other.lastName),
	userName(other.userName), password(other.password), id(other.id), points(other.points), isModerator(other.isModerator) {}

User::~User()
{
}

//operators
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

//methods tied to operators
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

//getters
const String& User::getFirstName() const
{
	return firstName;
}

const String& User::getLastName() const
{
	return lastName;
}

const String& User::getUserName() const
{
	return userName;
}

const String& User::getPassword() const
{
	return password;
}

const size_t User::getId() const
{
	return id;
}

const int User::getPoints() const
{
	return points;
}

const bool User::getModeratorStatus() const
{
	return isModerator;
}

//setters
void User::setFirstName(const String& newFirstName)
{
	firstName = newFirstName;
}

void User::setFirstName(const char* newFirstName)
{
	firstName = newFirstName;
}

void User::setLastName(const String& newLastName)
{
	lastName = newLastName;
}

void User::setLastName(const char* newLastName)
{
	lastName = newLastName;
}

void User::setUserName(const String& newUserName)
{
	userName = newUserName;
}

void User::setUserName(const char* newUserName)
{
	userName = newUserName;
}

void User::setPassword(const String& newPassword)
{
	password = newPassword;
}

void User::setPassword(const char* newPassword)
{
	password = newPassword;
}

void User::setId(const size_t newId)
{
	id = newId;
}

void User::setPoints(const int newPoints)
{
	points = newPoints;
}

void User::setModeratorStatus(const bool newStatus)
{
	isModerator = newStatus;
}

//methods
void User::clearUser()
{
	firstName.clearString();
	lastName.clearString();
	userName.clearString();
	password.clearString();

	id = 0;
	points = 0;
	isModerator = false;
}

void User::incrementPoints(int amount)
{
	points += amount;
}

void User::decrementPoints(int amount)
{
	points -= amount;
}