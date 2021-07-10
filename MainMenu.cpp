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
		tab_field[string_names[i]] = svec();
}
void MainMenu::print_field()
{
	//print in order of insertion
	for (size_t i = 0; i < string_number; i++)
	{
		auto curr = string_names[i];
		auto tab = tab_field[curr];
		if (current_pos.y == i) setcolor(COLORS::RED, COLORS::BLACK);
		else setcolor(COLORS::GREEN, COLORS::BLACK);

		cout << curr;
		setcolor(COLORS::GREEN, COLORS::BLACK);
		cout << "|";
		for (size_t n= 0;n<tab.size();n++)
		{
			auto point = tab[n];
			if (current_pos.x == n &&
				current_pos.y == i) 
				setcolor(COLORS::MAGENTA, COLORS::BLACK);
			else setcolor(COLORS::GREEN, COLORS::BLACK);
			cout << point << " ";
			setcolor(COLORS::GREEN, COLORS::BLACK);
		}
		cout << endl;
	}
}
void MainMenu::increase_field()
{
	for (auto& field : tab_field) field.second.push_back("-");
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
		if (_kbhit() && !key_pressed)
		{
			int input = _getch();
			switch ((CODES)input)
			{
			case CODES::i: increase_field(); break;
			case CODES::a: add_new_value();  break;
			case CODES::s: save();           break;

			case CODES::h: move(LEFT);  break;
			case CODES::l: move(RIGHT); break;
			case CODES::j: move(DOWN);  break;
			case CODES::k: move(UP);    break;
			};
			any_action = true;
			system("cls");
			key_pressed = true;
		}
		if (!_kbhit())key_pressed = false;
	}
}

bool MainMenu::can_move(const Coord& increaser)
{
	Coord new_pos = { current_pos.x + increaser.x,
					 current_pos.y + increaser.y };
	if (new_pos.x < 0 || new_pos.y < 0) return 0;

	Coord max = get_max_pos();

	if (increaser.x == 0) return new_pos.y < max.y;
	if (increaser.y == 0) return new_pos.x < max.x;
}
Coord MainMenu::get_max_pos()
{
	return Coord{ (int)tab_field['e'].size(), (int)string_number};
}
void MainMenu::move(const Coord& dir)
{
	if (can_move(dir))
	{
		current_pos.x += dir.x;
		current_pos.y += dir.y;
	}
}
void MainMenu::setcolor(COLORS _textcol, COLORS _backcol)
{
	int textcol = (int)_textcol;
	int backcol = (int)_backcol;
	if ((textcol % 16) == (backcol % 16))textcol++;
	textcol %= 16; backcol %= 16;
	unsigned short wAttributes = ((unsigned)backcol << 4) | (unsigned)textcol;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, wAttributes);
}
void MainMenu::add_new_value()
{
	string val;
	cout << "value:";
	cin >> val;
	insert_to_field(val);
}
void MainMenu::insert_to_field(const string& val)
{
	for (size_t i = 0; i < string_number; i++)
	{
		if (i == current_pos.y)
		{
			auto name = string_names[i];
			tab_field[name][current_pos.x] = val;
		}
	}
}
void MainMenu::write_tab_down(const string& path)
{
	ofstream file(path);

	vector<string> values;
	for (size_t i = 0; i < string_number; i++)
	{
		string val;
		auto name = string_names[i];
		val += name;
		val += "|";
		for (auto v : tab_field[name]) val += v;
		values.push_back(val);
	}
	for (auto v : values)
	{
		file << v << endl;
	}

	file.close();
}
void MainMenu::save()
{
	string path;
	cout << "path:";
	cin >> path;
	write_tab_down(path);
}