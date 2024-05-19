#include "String.h"

//constructors & destructor
String::String() : size(0), string(nullptr) {
}

String::String(const char* inputString) :
	size(0), string(nullptr) {

	if (inputString == nullptr) {
		return;
	}

	size = strlen(inputString) + 1;
	string = new char[size];
	strncpy_s(string, size, inputString, size - 1);
}

String::String(const String& other) :
	size(other.size), string(nullptr) {

	if (other.string == nullptr)
		return;

	string = new char[size];
	strncpy_s(string, size, other.string, other.size - 1);
}

String::String(String&& other) noexcept
	: String()
{
	swap(*this, other);
}

String::String(const size_t size) //TODO: don't know if this is ok
{
	if (size == 0) {
		throw std::out_of_range("Trying allocate String with 0 size");
	}

	this->size = size;
	string = new char[size];
	string[size] = '\0';
}

String::~String() {
	delete[] string;
	string = nullptr;
}


void swap(String& lhs, String& rhs) noexcept
{
	using std::swap;
	swap(lhs.size, rhs.size);
	swap(lhs.string, rhs.string);
}


//methods
void String::clearString() {

	delete[] string;
	string = nullptr;
	size = 0;

}

const size_t String::length() const {
	return size;
}

const char* String::getString() const {
	return string;
}

void String::setLength(const size_t inputLenght) {
	size = inputLenght;
}

void String::setString(const char* inputString) {
	delete[] string;
	string = nullptr; //QUESTION: should I do that?

	size_t newSize = strlen(inputString) + 1;

	string = new char[newSize];
	size = newSize;
	for (size_t i = 0; i < newSize; i++) {
		string[i] = inputString[i];
	}
}

bool String::find(const char* substr) const //Boyer Moore Horspool Algorithm
{
	size_t sublen = strlen(substr);
	size_t len = size - 1;

	if (sublen > len)
		return false;

	int bad_char[256];

	// Preprocessing: Initialize bad character array
	for (int i = 0; i < 256; ++i)
		bad_char[i] = -1;

	for (size_t i = 0; i < sublen; ++i)
		bad_char[(unsigned char)substr[i]] = i;

	size_t shift = 0;
	while (shift <= len - sublen) {
		int j = sublen - 1;

		while (j >= 0 && substr[j] == string[shift + j])
			--j;

		if (j < 0) {
			// Substring found
			return true;
		}
		else {
			// Shift based on bad character heuristic
			shift += std::max(1, static_cast<int>(j - bad_char[(unsigned char)string[shift + j]]));
		}
	}
	return false;
}

bool String::find(const String& substr) const //Boyer Moore Horspool Algorithm
{
	size_t sublen = substr.length() - 1;
	size_t len = size - 1;

	if (sublen > len)
		return false;

	int bad_char[256];

	// Preprocessing: Initialize bad character array
	for (int i = 0; i < 256; ++i)
		bad_char[i] = -1;

	for (size_t i = 0; i < sublen; ++i)
		bad_char[(unsigned char)substr[i]] = i;

	size_t shift = 0;
	while (shift <= len - sublen) {
		int j = sublen - 1;

		while (j >= 0 && substr[j] == string[shift + j])
			--j;

		if (j < 0) {
			// Substring found
			return true;
		}
		else {
			// Shift based on bad character heuristic
			shift += std::max(1, static_cast<int>(j - bad_char[(unsigned char)string[shift + j]]));
		}
	}
	return false;
}

size_t String::toNum() const
{
	size_t result = 0;
	for (size_t i = 0; i < size && string[i] != '\0'; ++i) {
		if (string[i] >= '0' && string[i] <= '9') {
			result = result * 10 + (string[i] - '0');
		}
		else {
			throw std::invalid_argument("String contains non-numeric characters.");
		}
	}
	return result;
}

bool String::isDigit() const
{
	if (size == 0) {
		return false;
	}

	for (size_t i = 0; i < size - 1; i++) {
		if (!isdigit(string[i]))
			return false;
	}

	return true; 
}

//operators
String& String::operator=(const String& other) {

	if (this != &other) {
		delete[] string;
		string = nullptr;

		size = other.size;

		if (other.string != nullptr) {
			string = new char[size];
			strncpy_s(string, size, other.string, other.size - 1);
		}
	}

	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other) {
		swap(*this, other);
	}
	return *this;
}

String& String::operator=(const char* str)
{
	size_t strSize = strlen(str) + 1;

	if (size != strSize) {
		delete[] string;
		string = nullptr;
		size = strSize;

		string = new char[size];
	}

	for (size_t i = 0; i < strSize; i++) {
		string[i] = str[i];
	}
	return *this;
}

char& String::operator[](const size_t index) {

	return string[index];
}

char String::operator[](const size_t index) const {

	return string[index];
}


bool String::operator==(const String& other) const {

	if (size != other.size) return false;

	return strcmp(string, other.string) == 0;
}

bool String::operator==(const char* str) const {

	if (str == nullptr) {
		if (string == nullptr)
			return true;
		else return false;
	}

	if (size != strlen(str) + 1) return false;

	return strcmp(string, str) == 0;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

bool String::operator!=(const char* str) const
{
	return !(*this == str);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	if (str.getString() != nullptr)
		os << str.getString();
	else
		throw std::runtime_error("Trying to output a nullptr String");

	return os;
}//TODO remove str
