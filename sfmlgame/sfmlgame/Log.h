#pragma once
#include <string>

class Log
{
public:
	Log();
	virtual ~Log();

	static void err(std::string message);
	static void debug(std::string message);
private:
};

