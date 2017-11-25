#include "Debug.h" 
#include <iostream>
#include <Windows.h>

Debug::Debug()
{
	_SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = rect.Top + windSize;
	rect.Right = rect.Left + windSize;
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
		AttachConsole(GetCurrentProcessId());
	}
}

void Debug::Output(std::string message)
{
	if (message != lastMessage)
	{
		std::cout << message + "\n";
		lastMessage = message;
	}

}
