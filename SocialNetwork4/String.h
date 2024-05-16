#pragma once
#include <iostream>
#include <stdexcept>

class String
{

public:

	//constructors & destructor
	String();

	String(const char* const inputString);

	String(const String& other);

	String(String&& string) noexcept;

	String(const size_t size);

	~String();


	//methods
	friend void swap(String& lhs, String& rhs) noexcept;

	void clearString();

	const size_t length() const;

	const char* getString() const;

	void setLength(const size_t inputLenght);

	void setString(const char* inputString);

	bool find(const char* substr) const;

	bool find(const String& substr) const;

	size_t toNum() const;

	bool isDigit() const;

	//operators
	String& operator=(const String& other);
	String& operator=(String&& _other) noexcept;
	String& operator=(const char* str);

	String& operator+(const String& other); //String reference or no reference ?
	String& operator+(const char* str);

	String& operator+=(const String& other); //not finished
	String& operator+=(const char* str); //not finished

	//add += ; 

	char& operator[](const size_t index); //do we need both?

	char operator[](const size_t index) const;

	bool operator==(const String& other) const;
	bool operator==(const char* str) const;

	bool operator!=(const String& other) const;
	bool operator!=(const char* str) const;

	friend std::ostream& operator<<(std::ostream& os, const String& str);

private:

	char* string;
	size_t size; //By default contains the null terminator

};
