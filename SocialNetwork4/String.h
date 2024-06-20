#pragma once
#include <iostream>
#include <stdexcept>

class String
{

public:

	//constructors and destructor
	String();

	String(const char* const inputString);

	String(const String& other);

	String(const size_t size);

	~String();

	//operators
	String& operator=(const String& other);
	String& operator=(const char* str);
	
	char operator[](const size_t index) const;

	bool operator==(const String& other) const;
	bool operator==(const char* str) const;

	bool operator!=(const String& other) const;
	bool operator!=(const char* str) const;

	friend std::ostream& operator<<(std::ostream& os, const String& str);

	//getters and setters
	const size_t length() const;

	const char* getString() const;

	void setLength(const size_t inputLenght);

	void setString(const char* inputString);

	//methods
	friend void swap(String& lhs, String& rhs) noexcept;

	void clearString();

	bool find(const char* substr) const;

	bool find(const String& substr) const;

	size_t toNum() const;

	bool isDigit() const;

	bool isEmpty() const;

private:

	char* string;
	size_t size; //contains the null terminator
};

