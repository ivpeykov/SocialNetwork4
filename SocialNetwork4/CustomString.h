#pragma once
#include <iostream>
#include <stdexcept>

class CustomString
{

public:

	//constructors & destructor
	CustomString();

	CustomString(const char* const inputString);

	CustomString(const CustomString& other);

	CustomString(CustomString&& string) noexcept;

	CustomString(const size_t size);

	~CustomString();


	//methods
	friend void swap(CustomString& lhs, CustomString& rhs) noexcept;

	void clearString();

	const size_t length() const;

	const char* getString() const;

	void setLength(const size_t inputLenght);

	void setString(const char* inputString);


	//operators
	CustomString& operator=(const CustomString& other);
	CustomString& operator=(CustomString&& _other) noexcept;
	CustomString& operator=(const char* str);

	CustomString& operator+(const CustomString& other); //CustomString reference or no reference ?
	CustomString& operator+(const char* str);

	CustomString& operator+=(const CustomString& other); //not finished
	CustomString& operator+=(const char* str); //not finished

	//add += ; 

	char& operator[](const size_t index); //do we need both?

	char operator[](const size_t index) const;

	bool operator==(const CustomString& other) const;
	bool operator==(const char* str) const;

	bool operator!=(const CustomString& other) const;
	bool operator!=(const char* str) const;

	friend std::ostream& operator<<(std::ostream& os, const CustomString& str);

private:

	char* string;
	size_t size; //By default contains the null terminator

};
