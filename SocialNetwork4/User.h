#pragma once
#include "CustomString.h"

class User
{
public:
	User(); //for initialisation

	User(const CustomString& firstName, const CustomString& lastName,
		const CustomString& userName, const CustomString& password,
		const size_t id);

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const size_t id);

	User(const CustomString& firstName, const CustomString& lastName,
		const CustomString& userName, const CustomString& password,
		const size_t id, const int points, const bool isModerator); //for reading files

	User(const char* firstName, const char* lastName,
		const char* userName, const char* password,
		const size_t id, const int points, const bool isModerator); //for reading files

	User(const User& other);

	~User();

	const CustomString& getFirstName() const;
	const CustomString& getLastName() const;
	const CustomString& getUserName() const;
	const CustomString& getPassword() const;
	const size_t getId() const;
	const int getPoints() const;
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

	void setId(const size_t newId);
	void setPoints(const int newPoints);
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
	size_t id;
	int points;
	bool isModerator;
};