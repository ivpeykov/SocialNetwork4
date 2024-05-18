#include "InputValidator.h"

bool InputValidator::doesStringContainNonAsciiChars(const String& string)
{
    size_t strLen = string.length();
    for (size_t i = 0; i < strLen; i++) {
        if (static_cast<unsigned char>(string[i]) > 127) {
            return true;
        }
    }
    return false;
}

bool InputValidator::doesStringContainNonAsciiChars(const char* string)
{
    size_t strLen = strlen(string) + 1;
    for (size_t i = 0; i < strLen; i++) {
        if (static_cast<unsigned char>(string[i]) > 127) {
            return true;
        }
    }
    return false;
}

bool InputValidator::isValidCommandInput(const String& commandInput)
{
    if (commandInput == nullptr) {
        std::cout << "\nInvalid command! Try again." << std::endl;
        return false;
    }

    if (doesStringContainNonAsciiChars(commandInput)) {
        std::cout << "\nInvalid command! Try again." << std::endl;
        return false;
    };

    //Quickly elimanate easy to spot invalid commands
    if (!isalpha(commandInput[0]) || commandInput[0] == '\n') {
        std::cout << "\nInvalid command! Try again: " << std::endl;
        return false;
    }

    for (int i = 0; i < Command::CommandsCount; i++) {

        if (commandInput == CommandsHandler::commandsList[i]) {
            CommandsHandler::setCurrCommand(i);
            return true;
        }
    }

    std::cout << "\nInvalid command! Try again: " << std::endl;
    return false;
}

bool InputValidator::isValidSocialNetworkDirectoryInput(const String& directoryInput)
{
    if (doesStringContainNonAsciiChars(directoryInput)) {
        std::cout << "Invalid directory!" << std::endl;
        return false;
    }

    if (directoryInput[0] == '\0') {
        std::cout << "Invalid directory!" << std::endl;
        return false;
    }

    return true;
}

bool InputValidator::isValidFirstName(const String& firstName)
{
    if (doesStringContainNonAsciiChars(firstName))
        return false;

    if (firstName[0] == '\0') {
        return false;
    }

    for (size_t i = 0; i < firstName.length() - 1; i++) {
        if (!isalpha(firstName[i]))
            return false;
    }

    return true;
}

bool InputValidator::isValidLastName(const String& lastName)
{
    if (doesStringContainNonAsciiChars(lastName))
        return false;

    if (lastName[0] == '\0') {
        return false;
    }

    for (size_t i = 0; i < lastName.length() - 1; i++) {
        if (!isalpha(lastName[i]))
            return false;
    }

    return true;
}

size_t InputValidator::isValidUserNameSignup(const String& userName)
{
    if (doesStringContainNonAsciiChars(userName))
        return 0;

    if (userName[0] == '\0') {
        return 0;
    }
   
    if (CurrentData::getCurrSocialNetwork().getUserPosition(userName) != SIZE_MAX)
        return 2; //userName Exists
        
    return 1;
}

bool InputValidator::isValidUserNameLogin(const String& userName) //suggestion: check for existance elsewhere
{
    if (doesStringContainNonAsciiChars(userName))
        return false;

    if (userName[0] == '\0') {
        return false;
    }

    if (CurrentData::getCurrSocialNetwork().getUserPosition(userName) == SIZE_MAX)
        return false;

    return true;
}

bool InputValidator::isValidPassword(const String& password)
{
    if (doesStringContainNonAsciiChars(password))
        return false;

    if (password[0] == '\0') {
        return false;
    }

    return true;
}

bool InputValidator::isValidAnswerInputForEditing(const short answer, const short maxAnswerValue)
{
    return answer >= 0 && answer <= maxAnswerValue;
}


bool InputValidator::isValidTitle(const String& title)
{
    if (doesStringContainNonAsciiChars(title))
        return false;

    if (title[0] == '\0') {
        return false;
    }

    return true;
}

bool InputValidator::isValidDescription(const String& description)
{
    if (doesStringContainNonAsciiChars(description))
        return false;

    if (description[0] == '\0') {
        return false;
    }

    return true;
}

bool InputValidator::isValidContent(const String& content)
{
    if (doesStringContainNonAsciiChars(content))
        return false;

    if (content[0] == '\0') {
        return false;
    }

    return true;
}

bool InputValidator::isValidCommentTextInput(const String& text)
{
    if (doesStringContainNonAsciiChars(text))
        return false;

    if (text[0] == '\0') {
        return false;
    }

    return true;
}
