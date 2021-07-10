#include "MainMenu.h"
using namespace TabManager;

MainMenu::MainMenu()
{
	init_field();

	run();
}
MainMenu::~MainMenu()
{
	
}
void MainMenu::init_field()
{
	for (size_t i = 0; i < string_number; i++)
		tab_field[string_names[i]] = vector<char>();
}
void MainMenu::print_field()
{
	//print in order of insertion
	for (size_t i = 0; i < string_number; i++)
	{
		auto curr = string_names[i];
		auto tab = tab_field[curr];
		cout << curr << "|";
		for (auto& point : tab) cout << point<<" ";
		cout << endl;
	}
}
void MainMenu::increase_field()
{
	for_each(tab_field.begin(), tab_field.end(),
		[&](pair<char,cvec> val)
		{
			val.second.push_back('-');
		});
}

void MainMenu::run()
{
	while (true)
	{
		if (any_action)
		{
			print_field();
			any_action = false;
		}
		if (_kbhit())
		{

		}
	}
}