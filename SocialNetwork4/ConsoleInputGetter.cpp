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

    std::cout << "\nEnter user first name: "; 

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

    std::cout << "\nEnter user last name: ";

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

    std::cout << "\nEnter username: "; 

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

    std::cout << "\nEnter user password: ";

    char newPass[Configuration::PASSWORD_MAX_LENGTH];

    std::cin.getline(newPass, Configuration::PASSWORD_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newUser.setPassword(newPass);
}

void ConsoleInputGetter::recieveAnswerInputForEditing(short& answer)
{

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = 2; //1 for the digit , 2 for the null char
    size_t tempAnswer = 0;

    std::cout << "Please enter number from 0 to 5 to edit: ";
    char* input = new char[inputBuffer];
    std::cin.getline(input, inputBuffer);

    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::exception("Invalid answer input!");
    }

    CustomString strInput = input;

    try {
        tempAnswer = strInput.toNum();
    }
    catch (std::exception e) {
        delete[] input;
        throw e;
    }

    delete[] input;
    answer = tempAnswer;
}

void ConsoleInputGetter::recieveIdInputForEditUserAsModerator(size_t& id)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = Configuration::MAX_DIGITS_INPUT + 1;

    size_t tempId = 0;

    std::cout << "Enter ID: ";

    char* input = new char[inputBuffer];

    std::cin.getline(input, inputBuffer); 
    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::exception("Invalid Id input!");
    }

    CustomString strInput = input;

    try {
        tempId = strInput.toNum();
    }
    catch (std::exception e) {
        delete[] input;
        throw e;
    }

    if (tempId == 0) {
        delete[] input;
        throw std::exception("Invalid input! Cannot change moderator status of the root admin!");
    }


    delete[] input;
    id = tempId;

}

void ConsoleInputGetter::recieveModeratorStatusInputForEditUserAsModerator(bool& newModeratorStatus)
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
        throw std::exception("Invalid moderator status input!");
    }

    CustomString strInput = input;

    try {
        tempStatus = strInput.toNum();
    }
    catch (std::exception e) {
        delete[] input;
        throw e;
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
        throw std::exception("Invalid status input!");
    }

}

void ConsoleInputGetter::recieveTitleInput(Topic& newTopic)
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

    newTopic.setTitle(newTitle);

}

void ConsoleInputGetter::recieveDescriptionInput(Topic& newTopic)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter Description: ";

    char newDescription[Configuration::TOPIC_DESCRIPTION_MAX_LENGTH];

    std::cin.getline(newDescription, Configuration::TOPIC_DESCRIPTION_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newTopic.setDescription(newDescription);
}

void ConsoleInputGetter::recieveDiscussionTitleInput(Discussion& newDiscussion)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter title: ";

    char newTitle[Configuration::DISCUSSION_TITLE_MAX_LENGTH];

    std::cin.getline(newTitle, Configuration::DISCUSSION_TITLE_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newDiscussion.setTitle(newTitle);
}

void ConsoleInputGetter::recieveDiscussionContentInput(Discussion& newDiscussion)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter Content: ";

    char* newContent = new char[Configuration::DISCUSSION_CONTENT_MAX_LENGTH]; //add exception handling

    std::cin.getline(newContent, Configuration::DISCUSSION_CONTENT_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    try {
        newDiscussion.setContent(newContent);
    }
    catch (...) {
        delete[] newContent;
        throw;
    }

    delete[] newContent;
}

void ConsoleInputGetter::recieveOpenDiscussionIdInput(size_t& id)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = Configuration::MAX_DIGITS_INPUT + 1;
    
    size_t tempId = 0;

    std::cout << "Enter ID: ";

    char* input = new char[inputBuffer]; //Potential optimisation? : dynamic because Configuration::MAX_DIGITS_INPUT cannot be used as const, can it ?

    std::cin.getline(input, inputBuffer);
    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::exception("Invalid Id input!");
    }

    CustomString strInput = input;

    try {
        tempId = strInput.toNum();
    }
    catch (std::exception e) {
        delete[] input;
        throw e;
    }

    delete[] input;
    id = tempId;
}

void ConsoleInputGetter::recieveCommentTextInput(Comment& newComment)
{
    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    std::cout << "\nEnter comment: ";

    char comment[Configuration::COMMENT_TEXT_MAX_LENGTH]; //add exception handling

    std::cin.getline(comment, Configuration::COMMENT_TEXT_MAX_LENGTH);

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    newComment.setText(comment);
}

size_t ConsoleInputGetter::recieveIdInputForCommentReply()
{

    if (isBufferOverfilled()) {
        flushInputBuffer();
    }

    short inputBuffer = Configuration::MAX_DIGITS_INPUT + 1;

    size_t id = SIZE_MAX;

    std::cout << "Enter comment ID: ";

    char* input = new char[inputBuffer]; //Potential optimisation? : dynamic because Configuration::MAX_DIGITS_INPUT cannot be used as const, can it ?

    std::cin.getline(input, inputBuffer);
    if (InputValidator::doesStringContainNonAsciiChars(input) || input[0] == '\0') {
        delete[] input;
        input = nullptr;
        throw std::exception("Invalid Id input!");
    }

    CustomString strInput = input;

    try {
        id = strInput.toNum();
    }
    catch (std::exception e) {
        delete[] input;
        throw e;
    }

    delete[] input;

    return id;
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