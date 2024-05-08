#pragma once
#include "CustomString.h"

class User
{
public:
	User(); //for initialisation

	User(const CustomString& firstName, const CustomString& lastName,
		const CustomString& userName, const CustomString& password,
		const unsigned id);

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const unsigned id);

	User(const CustomString& firstName, const CustomString& lastName,
		const CustomString& userName, const CustomString& password,
		const unsigned id, const unsigned points, const bool isModerator); //for reading files

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const unsigned id, const unsigned points, const bool isModerator); //for reading files

	User(const User& other);

	~User();

	const CustomString& getFirstName() const;
	const CustomString& getLastName() const;
	const CustomString& getUserName() const;
	const CustomString& getPassword() const;
	const unsigned getId() const;
	const unsigned getPoints() const;
	const bool getModeratorStatus() const;

	void clearUser();

	void setFirstName(const CustomString& newFirstName);
	void setFirstName(const char* newFirstName);

	void setLastName(const CustomString& newLastName);
	void setLastName(const char* newLastName);

	void setUserName(const CustomString& newUserName);
	void setUserName(const char* newUserName);

	void setPassword(const CustomString& newPassword);
	void setPassword(const char* newPassword);

	void setId(const unsigned newId);
	void setPoints(const unsigned newPoints);
	void setModeratorStatus(const bool newStatus);


	bool isEqualWithoutId(const User& other) const;
	bool isNotEqualWithoutId(const User& other) const;

	User& operator=(const User& other);
	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;

private:
	CustomString firstName;
	CustomString lastName;
	CustomString userName;
	CustomString password;
	unsigned id;
	unsigned points;
	bool isModerator;
};