#include "Log.h"
#include <iostream>

Log::Log()
{
	//ctor
}

Log::~Log()
{
	//dtor
}

void Log::err(std::string message)
{
	std::cout << "ERROR: " << message << std::endl;
}

void Log::debug(std::string message)
{
	std::cout << message << std::endl;
}
