#include "MainMenu.h"
using namespace TabManager;

MainMenu::MainMenu()
{
	for (int i = 0; i < string_number; i++)
		tab_field[string_names[i]] = vector<char>();
}
MainMenu::~MainMenu()
{

}