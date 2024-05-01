#include "CustomString.h"

//constructors & destructor
CustomString::CustomString() : size(0), string(nullptr) {
}

CustomString::CustomString(const char* inputString) :
	size(0), string(nullptr) {

	if (inputString == nullptr) {
		return;
	}

	size = strlen(inputString) + 1;
	string = new char[size];
	strncpy_s(string, size, inputString, size - 1);
}

CustomString::CustomString(const CustomString& other) :
	size(other.size), string(nullptr) {

	if (other.string == nullptr)
		return;

	string = new char[size];
	strncpy_s(string, size, other.string, other.size - 1);
}

CustomString::CustomString(CustomString&& other) noexcept
	: CustomString()
{
	swap(*this, other);
}

CustomString::CustomString(const size_t size) //don't know if this is ok
{
	if (size == 0) {
		throw std::out_of_range("Trying allocate CustomString with 0 size");
	}

	//delete[] string; ?
	this->size = size;
	string = new char[size];
	string[size] = '\0';
}

CustomString::~CustomString() {
	delete[] string;
	string = nullptr;
}


void swap(CustomString& lhs, CustomString& rhs) noexcept
{
	using std::swap;
	swap(lhs.size, rhs.size);
	swap(lhs.string, rhs.string);
}


//methods
void CustomString::clearString() {

	delete[] string;
	string = nullptr;
	size = 0;

}

const size_t CustomString::length() const {
	return size;
}

const char* CustomString::getString() const {
	return string;
}

void CustomString::setLength(const size_t inputLenght) {
	size = inputLenght;
}

void CustomString::setString(const char* inputString) {
	delete[] string;
	string = nullptr; //QUESTION: should I do that?

	size_t newSize = strlen(inputString) + 1;

	string = new char[newSize];
	size = newSize;
	for (int i = 0; i < newSize; i++) {
		string[i] = inputString[i];
	}
}

bool CustomString::find(const char* substr) const //study this
{
	size_t sublen = strlen(substr);
	size_t len = size - 1;

	if (sublen > len)
		return false;

	for (size_t i = 0; i <= len - sublen; ++i) {
		size_t j;
		for (j = 0; j < sublen; ++j) {
			if (string[i + j] != substr[j]) {
				break;
			}
		}
		if (j == sublen) {
			return true; // substring found
		}
	}
	return false; // substring not found
}

bool CustomString::find(const CustomString& substr) const //TODO: study how this works
{

	size_t sublen = substr.length() - 1;
	size_t len = size - 1;

	if (sublen > len)
		return false;

	for (size_t i = 0; i <= len - sublen; ++i) {
		size_t j;
		for (j = 0; j < sublen; ++j) {
			if (string[i + j] != substr[j]) {
				break;
			}
		}
		if (j == sublen) {
			return true; // substring found
		}
	}
	return false; // substring not found
}

size_t CustomString::toNum() const
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

bool CustomString::isDigit() const
{
	if (size == 0) {
		return false;
	}

	for (int i = 0; i < size - 1; i++) {
		if (!isdigit(string[i]))
			return false;
	}

	return true; 
}

//operators
CustomString& CustomString::operator=(const CustomString& other) {

	if (other.string == nullptr) { // is this ok?
		return *this;
	}

	if (this != &other) {
		delete[] string;
		string = nullptr;

		size = other.size;
		string = new char[size];
		strncpy_s(string, size, other.string, other.size - 1);
	}

	return *this;
}

CustomString& CustomString::operator=(CustomString&& other) noexcept
{
	if (this != &other) {
		swap(*this, other);
	}
	return *this;
}

CustomString& CustomString::operator=(const char* str)
{
	size_t strSize = strlen(str) + 1;

	if (size < strSize) {
		delete[] string;
		string = nullptr;
		size = strSize;

		string = new char[size];
	}

	for (int i = 0; i < strSize; i++) {
		string[i] = str[i];
	}
	return *this;
}

CustomString& CustomString::operator+(const CustomString& other) {


	CustomString tempString(*this);

	delete[] string;

	size = tempString.size + other.size - 1; //removing one of the null terminator chars
	string = new char[size];

	size_t i = 0;

	if (size > 0) {
		for (i; i < tempString.size - 1; i++) { //-1 clearing the null terminator because we are not done yet
			string[i] = tempString.string[i];
		}
	}

	for (size_t j = 0; j < other.size; j++) {

		string[i] = other.string[j];
		i++;
	}


	return *this;
}

CustomString& CustomString::operator+(const char* str) {

	CustomString tempString(*this);

	delete[] string;

	size_t strLen = strlen(str) + 1;
	size = tempString.size + strLen - 1; //removing one of the null terminator chars
	string = new char[size];

	size_t i = 0;

	if (size > 0) {
		for (i; i < size - 1; i++) { //-1 clearing the null terminator because we are not done yet
			string[i] = tempString.string[i];
		}
	}

	for (size_t j = 0; j < strLen; j++) { //adding the null terminator

		string[i] = str[j];
		++i;
	}


	return *this;
}

CustomString& CustomString::operator+=(const CustomString& other) //NOT FINISHED
{
	return *this;
}

CustomString& CustomString::operator+=(const char* str) //NOT FINISHED
{
	return *this;
}

char& CustomString::operator[](const size_t index) {

	return string[index];
}

char CustomString::operator[](const size_t index) const {

	return string[index];
}


bool CustomString::operator==(const CustomString& other) const {
	if (size != other.size) return false;

	return strcmp(string, other.string) == 0;
}

bool CustomString::operator==(const char* str) const {

	if (str == nullptr) {
		if (string == nullptr)
			return true;
		else return false;
	}

	if (size != strlen(str) + 1) return false;

	return strcmp(string, str) == 0;
}

bool CustomString::operator!=(const CustomString& other) const
{
	return !(*this == other);
}

bool CustomString::operator!=(const char* str) const
{
	return !(*this == str);
}

std::ostream& operator<<(std::ostream& os, const CustomString& str)
{
	if (str.getString() != nullptr)
		os << str.getString();
	else
		throw std::runtime_error("Trying to output a nullptr CustomString");

}
