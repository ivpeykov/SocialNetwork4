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
    return true;
}

bool InputValidator::isValidFirstName(const CustomString& firstName)
{
    if (doesStringContainNonAsciiChars(firstName))
        return false;

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

    for (int i = 0; i < lastName.length() - 1; i++) {
        if (!isalpha(lastName[i]))
            return false;
    }

    return true;
}

bool InputValidator::isValidUserName(const CustomString& userName)
{
    if (doesStringContainNonAsciiChars(userName))
        return false;
   
    if (CurrentData::doesUsernameExist(userName))
        return false;
        
    return true;
}

bool InputValidator::isValidPassword(const CustomString& password)
{
    if (doesStringContainNonAsciiChars(password))
        return false;

    return true;
}