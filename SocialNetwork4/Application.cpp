#include "Application.h"

Application& Application::getInstance()
{
	static Application instance;
	return instance;
}

void Application::run()
{

	
}

Application::Application() {}
