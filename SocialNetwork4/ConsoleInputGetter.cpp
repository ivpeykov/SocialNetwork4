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
    if (isBufferOverfilled()) {
        flushInputBuffer();
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

    if (isBufferOverfilled()) {
        resetCommandInput();
        flushInputBuffer();
    }
}


void ConsoleInputGetter::recieveSocialNetworkDirectoryInput()
{
    std::cout << "Enter social network directory: ";

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }


    char input[128];
    std::cin.getline(input, 128, '\n');

    socialNetworkDirectoryInput.setString(input);

    if (isBufferOverfilled()) {
        resetSocialNetworkDirectoryInput();
        flushInputBuffer();
    }

}

void ConsoleInputGetter::recieveFirstNameInput(User& newUser)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user first name: "; //prnthndler

    char newName[Configuration::FIRST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::FIRST_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newUser.setFirstName(newName);
}

void ConsoleInputGetter::recieveLastNameInput(User& newUser)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user last name: "; //prnthndler

    char newName[Configuration::LAST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::LAST_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newUser.setLastName(newName);
}

void ConsoleInputGetter::recieveUserNameInput(User& newUser)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter username: "; //prnthndler

    char newName[Configuration::USER_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::USER_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newUser.setUserName(newName);
}

void ConsoleInputGetter::recievePasswordInput(User& newUser)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user password: "; //prnthndler

    char newPass[Configuration::PASSWORD_MAX_LENGTH];

    std::cin.getline(newPass, Configuration::PASSWORD_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newUser.setPassword(newPass);
}

void ConsoleInputGetter::recieveAnswerInputForEditing(short& answer)
{
    short failedTries = 0;

    while (!(std::cin >> answer)) {
        failedTries++;
        if (failedTries == 3) {
            flushInputBuffer();
            throw std::exception("Invalid input! Too many failed tries!");
        }
        std::cout << "\nInvalid input! Please enter a valid number: ";
        flushInputBuffer();
    }
}

void ConsoleInputGetter::recieveIdInputForEditUserAsModerator(size_t& id) ///BUG : THIS ALLOWS BUFFER OVERFLOW BECAUSE OF \n or \t spam
{
    short failedTries = 0;

    std::cout << "Enter ID: ";
    while (!(std::cin >> id) || id == 0) {
        failedTries++;
        if (failedTries == 3) {
            flushInputBuffer();
            throw std::exception("Invalid input! Too many failed tries!");
        }

        if (id == 0 && std::cin.good()) {
            std::cout << "Invalid input! Cannot change moderator status of the root admin! \nPlease enter a valid number: " << std::endl;
            flushInputBuffer();
            continue;
        }

        std::cout << "\nInvalid input! Please enter a valid number: ";
        flushInputBuffer();
    }

}

void ConsoleInputGetter::recieveModeratorStatusInputForEditUserAsModerator(bool& newModeratorStatus) //BUG : THIS ALLOWS BUFFER OVERFLOW BECAUSE OF \n or \t spam
{
    
    short failedTries = 0;

    std::cout << "Enter status number (0 - Normal user ; 1 - Moderator): ";
    while (!(std::cin >> newModeratorStatus)) {
        failedTries++;
        if (failedTries == 3) {
            flushInputBuffer();
            throw std::exception("Invalid input! Too many failed tries!");
        }
        std::cout << "\nInvalid input! Please enter a valid number: ";
        flushInputBuffer();
    }

}

void ConsoleInputGetter::recieveTitleInput(Topic& newTopic)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter title: "; //prnthndler

    char newTitle[Configuration::TOPIC_TITLE_MAX_LENGTH];

    std::cin.getline(newTitle, Configuration::TOPIC_TITLE_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newTopic.setTitle(newTitle);
}

void ConsoleInputGetter::recieveDescriptionInput(Topic& newTopic)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter Description: "; //prnthndler

    char newDescription[Configuration::TOPIC_DESCRIPTION_MAX_LENGTH];

    std::cin.getline(newDescription, Configuration::TOPIC_DESCRIPTION_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newTopic.setDescription(newDescription);
}

void ConsoleInputGetter::recieveTitleInput(Discussion& newDiscussion)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter title: "; //prnthndler

    char newTitle[Configuration::DISCUSSION_TITLE_MAX_LENGTH];

    std::cin.getline(newTitle, Configuration::DISCUSSION_TITLE_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newDiscussion.setTitle(newTitle);
}

void ConsoleInputGetter::recieveDescriptionInput(Discussion& newDiscussion)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter Description: "; //prnthndler

    char newDescription[Configuration::DISCUSSION_DESCRIPTION_MAX_LENGTH];

    std::cin.getline(newDescription, Configuration::DISCUSSION_DESCRIPTION_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newDiscussion.setDescription(newDescription);
}

void ConsoleInputGetter::recieveOpenDiscussionIdInput(size_t& id) //BUG : THIS ALLOWS BUFFER OVERFLOW BECAUSE OF \n or \t spam
{
    short failedTries = 0;

    std::cout << "Enter ID: ";
    while (!(std::cin >> id)) {
        failedTries++;
        if (failedTries == 3) {
            flushInputBuffer();
            throw std::exception("Invalid input! Too many failed tries!");
        }

        std::cout << "\nInvalid input! Please enter a valid number: ";
        flushInputBuffer();
    }

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
