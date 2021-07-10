#include"MainMenu.h"

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
int main()
{
	system("cls");
	hidecursor();

	namespace tm = TabManager;
	tm::MainMenu app;

	return 0;
}