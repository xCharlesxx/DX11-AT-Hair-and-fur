#pragma once
#include <string>

class Debug
{
public:
	Debug();
	void Output(std::string message);
private:
	std::string lastMessage;
	int windSize = 50;
};