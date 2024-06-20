#include "ConsoleInputGetter.h"

String ConsoleInputGetter::commandInput;
String ConsoleInputGetter::socialNetworkDirectoryInput;

String& ConsoleInputGetter::getSocialNetworkDirectoryInput()
{
    return socialNetworkDirectoryInput;
}

String& ConsoleInputGetter::getCommandInput()
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

String ConsoleInputGetter::recieveSocialNetworkDirectoryInput()
{
    std::cout << "Enter social network directory: ";

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    char input[128];
    std::cin.getline(input, 128, '\n');

    String dir = input;

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    return dir;
}

void ConsoleInputGetter::recieveFirstNameInput(String& firstName)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user first name: ";

    char newName[Configuration::FIRST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::FIRST_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    firstName = newName;
}

void ConsoleInputGetter::recieveLastNameInput(String& lastName)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user last name: ";

    char newName[Configuration::LAST_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::LAST_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    lastName = newName;
}

void ConsoleInputGetter::recieveUserNameInput(String& userName)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter username: ";

    char newName[Configuration::USER_NAME_MAX_LENGTH];

    std::cin.getline(newName, Configuration::USER_NAME_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    userName = newName;
}

void ConsoleInputGetter::recievePasswordInput(String& password)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter user password: ";

    char newPass[Configuration::PASSWORD_MAX_LENGTH];

    std::cin.getline(newPass, Configuration::PASSWORD_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    password = newPass;
}

void ConsoleInputGetter::recieveAnswerInputForEditing(short& answer, const short optionsCount)
{

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = 2; //1 for the digit , 2 for the null char
    size_t tempAnswer = 0;

    std::cout << "Please enter number from 0 to " << optionsCount << " to edit : ";
    char* input = new char[inputBuffer];
    std::cin.getline(input, inputBuffer);

    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::invalid_argument("Invalid answer input!");
    }

    String strInput = input;

    try {
        tempAnswer = strInput.toNum();
    }
    catch (const std::invalid_argument&) {
        delete[] input;
        throw;
    }

    delete[] input;
    answer = tempAnswer;
}

size_t ConsoleInputGetter::recieveIdInput()
{

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = Configuration::MAX_DIGITS_INPUT + 1;

    size_t id = SIZE_MAX;

    std::cout << "Enter ID: ";

    char* input = new char[inputBuffer];

    std::cin.getline(input, inputBuffer);
    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::invalid_argument("Invalid Id input!");
    }

    String strInput = input;

    try {
        id = strInput.toNum();
    }
    catch (const std::invalid_argument&) {
        delete[] input;
        throw;
    }

    delete[] input;

    return id;
}

void ConsoleInputGetter::recieveModeratorStatusInput(bool& newModeratorStatus)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = 2; //1 for the digit , 2 for the null char
    size_t tempStatus = 0;

    std::cout << "Enter status number (0 - Normal user ; 1 - Moderator): ";
    char* input = new char[inputBuffer];
    std::cin.getline(input, inputBuffer);

    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::invalid_argument("Invalid moderator status input!");
    }

    String strInput = input;

    try {
        tempStatus = strInput.toNum();
    }
    catch (const std::invalid_argument&) {
        delete[] input;
        throw;
    }

    if (tempStatus == 0) {
        newModeratorStatus = 0;
        delete[] input;

    }

    else if (tempStatus == 1) {
        newModeratorStatus = 1;
        delete[] input;
    }


    else {
        delete[] input;
        throw std::invalid_argument("Invalid status input!");
    }
}

void ConsoleInputGetter::recieveTitleInput(String& title)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter title: ";

    char newTitle[Configuration::TOPIC_TITLE_MAX_LENGTH];

    std::cin.getline(newTitle, Configuration::TOPIC_TITLE_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    title = newTitle;
}

void ConsoleInputGetter::recieveDescriptionInput(String& description)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter description: ";

    char newDescription[Configuration::TOPIC_DESCRIPTION_MAX_LENGTH];

    std::cin.getline(newDescription, Configuration::TOPIC_DESCRIPTION_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    description = newDescription;
}

void ConsoleInputGetter::recievePostTitleInput(String& title)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter title: ";

    char newTitle[Configuration::POST_TITLE_MAX_LENGTH];

    std::cin.getline(newTitle, Configuration::POST_TITLE_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    title = newTitle;
}

void ConsoleInputGetter::recievePostContentInput(String& content)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter content: ";

    char* newContent = new char[Configuration::POST_CONTENT_MAX_LENGTH];

    std::cin.getline(newContent, Configuration::POST_CONTENT_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    try {
        content = newContent;
    }
    catch (const std::bad_alloc&) {
        delete[] newContent;
        throw;
    }

    delete[] newContent;
}

void ConsoleInputGetter::recieveCommentTextInput(String& text)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter comment: ";

    char newText[Configuration::COMMENT_TEXT_MAX_LENGTH]; //add exception handling

    std::cin.getline(newText, Configuration::COMMENT_TEXT_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    text = newText;
}

bool ConsoleInputGetter::getExitSavingAnswer()
{
    std::cout << "There are unsaved changes. Do you wish to save them before exiting? Y/N: ";
    char answer;

    while (true) {
        std::cin.get(answer);

        if (answer == 'y' || answer == 'Y') {
            return true;
        }

        else if (answer == 'n' || answer == 'N') {
            return false;
        }

        else {
            std::cout << "Invalid input! Please answer with either Y or N: ";
            flushInputBuffer();

        }
    }
}