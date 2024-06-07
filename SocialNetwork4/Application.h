#pragma once
//#include "PrintHandler.h"
//#include "CommandsHandler.h"
//#include "ConsoleInputGetter.h"
//#include "InputValidator.h"

class Application
{
public:

    static Application& getInstance();

    void run();

private:

    Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
};