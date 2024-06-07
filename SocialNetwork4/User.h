#pragma once
#include "String.h"

class User
{
public:


	//constructors and destructor
	User(); //for initialisation

	User(const String& firstName, const String& lastName,
		const String& userName, const String& password,
		const size_t id);

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const size_t id);

	User(const String& firstName, const String& lastName,
		const String& userName, const String& password,
		const size_t id, const int points, const bool isModerator); //for reading files

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const size_t id, const int points, const bool isModerator); //for reading files

	User(const User& other);

	~User();

	//operators
	User& operator=(const User& other);
	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;

	//methods tied to operators
	bool isEqualWithoutId(const User& other) const;
	bool isNotEqualWithoutId(const User& other) const;

	//getters
	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getUserName() const;
	const String& getPassword() const;
	const size_t getId() const;
	const int getPoints() const;
	const bool getModeratorStatus() const;

	//setters
	void setFirstName(const String& newFirstName);
	void setFirstName(const char* newFirstName);

	void setLastName(const String& newLastName);
	void setLastName(const char* newLastName);

	void setUserName(const String& newUserName);
	void setUserName(const char* newUserName);

	void setPassword(const String& newPassword);
	void setPassword(const char* newPassword);

	void setId(const size_t newId);
	void setPoints(const int newPoints);
	void setModeratorStatus(const bool newStatus);

	//methods
	void clearUser();
	void incrementPoints(int amount);
	void decrementPoints(int amount);

private:
	String firstName;
	String lastName;
	String userName;
	String password;
	size_t id;
	int points;
	bool isModerator;
};

