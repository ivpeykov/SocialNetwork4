#include "InputValidator.h"

bool InputValidator::doesStringContainNonAsciiChars(const CustomString& string)
{
    size_t strLen = string.length();
    for (int i = 0; i < strLen; i++) {
        if (static_cast<unsigned char>(string[i]) > 127) {
            return true;
        }
    }
    return false;
}

bool InputValidator::doesStringContainNonAsciiChars(const char* string)
{
    size_t strLen = strlen(string) + 1;
    for (int i = 0; i < strLen; i++) {
        if (static_cast<unsigned char>(string[i]) > 127) {
            return true;
        }
    }
    return false;
}

bool InputValidator::isValidCommandInput(const CustomString& commandInput)
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

bool InputValidator::isValidSocialNetworkDirectoryInput(const CustomString& directoryInput)
{
    if (doesStringContainNonAsciiChars(directoryInput)) {
        std::cout << "Invalid directory!" << std::endl;
        return false;
    }

    if (directoryInput[0] == '\0') { //remove?
        return false;
    }

    return true;
}

bool InputValidator::isValidFirstName(const CustomString& firstName)
{
    if (doesStringContainNonAsciiChars(firstName))
        return false;

    if (firstName[0] == '\0') {
        return false;
    }

    for (int i = 0; i < firstName.length() - 1; i++) {
        if (!isalpha(firstName[i]))
            return false;
    }

    return true;
}

bool InputValidator::isValidLastName(const CustomString& lastName)
{
    if (doesStringContainNonAsciiChars(lastName))
        return false;

    if (lastName[0] == '\0') {
        return false;
    }

    for (int i = 0; i < lastName.length() - 1; i++) {
        if (!isalpha(lastName[i]))
            return false;
    }

    return true;
}

bool InputValidator::isValidUserNameSignup(const CustomString& userName)
{
    if (doesStringContainNonAsciiChars(userName))
        return false;

    if (userName[0] == '\0') {
        return false;
    }
   
    if (CurrentData::doesUsernameExist(userName))
        return false;
        
    return true;
}

bool InputValidator::isValidUserNameLogin(const CustomString& userName) //suggestion: check for existance elsewhere
{
    if (doesStringContainNonAsciiChars(userName))
        return false;

    if (userName[0] == '\0') {
        return false;
    }

    if (!CurrentData::doesUsernameExist(userName))
        return false;

    return true;
}

bool InputValidator::isValidPassword(const CustomString& password)
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


bool InputValidator::isValidTitle(const CustomString& title)
{
    if (doesStringContainNonAsciiChars(title))
        return false;

    if (title[0] == '\0') {
        return false;
    }

    return true;
}

bool InputValidator::isValidDescription(const CustomString& description)
{
    if (doesStringContainNonAsciiChars(description))
        return false;

    if (description[0] == '\0') {
        return false;
    }

    return true;
}
