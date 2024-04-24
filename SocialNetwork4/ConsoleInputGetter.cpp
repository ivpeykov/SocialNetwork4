#include "ConsoleInputGetter.h"

CustomString ConsoleInputGetter::commandInput;
CustomString ConsoleInputGetter::socialNetworkDirectoryInput;

bool ConsoleInputGetter::isBufferOverfilled()
{
    return std::cin.rdbuf()->in_avail() > 0;
}

void ConsoleInputGetter::flushInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleInputGetter::recieveCommandInput()
{
    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }


    char tempCommandInput[Configuration::COMMAND_INPUT_MAX_LENGTH];
    char c = std::cin.get();
    unsigned i = 0;

    while (c != '\n' && i < Configuration::COMMAND_INPUT_MAX_LENGTH - 1) {
        tempCommandInput[i] = c;
        i++;
        c = std::cin.get();
    }

    tempCommandInput[i] = '\0';

    commandInput.setString(tempCommandInput);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        resetCommandInput();
        ConsoleInputGetter::flushInputBuffer();
    }
}


void ConsoleInputGetter::recieveSocialNetworkDirectoryInput()
{
    std::cout << "Enter social network directory: ";

    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }


    char input[128];
    std::cin.getline(input, 128, '\n');

    //null char at end?

    socialNetworkDirectoryInput.setString(input);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        resetSocialNetworkDirectoryInput();
        ConsoleInputGetter::flushInputBuffer();
    }

}

void ConsoleInputGetter::recieveFirstNameInput(User& newUser)
{
    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    std::cout << "\nEnter user first name: "; //prnthndler

    char newName[Configuration::FIRST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::FIRST_NAME_MAX_LENGTH);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    newUser.setFirstName(newName);
}

void ConsoleInputGetter::recieveLastNameInput(User& newUser)
{
    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    std::cout << "\nEnter user last name: "; //prnthndler

    char newName[Configuration::LAST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::LAST_NAME_MAX_LENGTH);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    newUser.setLastName(newName);
}

void ConsoleInputGetter::recieveUserNameInput(User& newUser)
{
    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    std::cout << "\nEnter username: "; //prnthndler

    char newName[Configuration::USER_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::USER_NAME_MAX_LENGTH);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    newUser.setUserName(newName);
}

void ConsoleInputGetter::recievePasswordInput(User& newUser)
{
    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    std::cout << "\nEnter user password: "; //prnthndler

    char newPass[Configuration::PASSWORD_MAX_LENGTH];

    std::cin.getline(newPass, Configuration::PASSWORD_MAX_LENGTH);

    if (ConsoleInputGetter::isBufferOverfilled()) {
        ConsoleInputGetter::flushInputBuffer();
    }

    newUser.setPassword(newPass);
}

CustomString& ConsoleInputGetter::getSocialNetworkDirectoryInput()
{
    return socialNetworkDirectoryInput;
}

CustomString& ConsoleInputGetter::getCommandInput()
{
    return commandInput;
}

void ConsoleInputGetter::resetCommandInput()
{
    commandInput.clearString();
}

void ConsoleInputGetter::resetSocialNetworkDirectoryInput()
{
    socialNetworkDirectoryInput.clearString();
}
