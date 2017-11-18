#include "Debug.h" 
#include <iostream>
#include <Windows.h>

Debug::Debug()
{
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		AttachConsole(GetCurrentProcessId());
		std::cout << "Debug Console Initialised." << std::endl;
	}
}

void Debug::Output(std::string message)
{
	std::cout << message + "\n"; 
}
