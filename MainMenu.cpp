#include "MainMenu.h"
using namespace TabManager;

MainMenu::MainMenu()
{
	font.loadFromFile("arial.ttf");
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
		for (size_t n = 0; n < tab.size(); n++)
		{
			auto point = tab[n];
			if (current_pos.x == n &&
				current_pos.y == i)
				setcolor(COLORS::MAGENTA, COLORS::BLACK);
			else setcolor(COLORS::GREEN, COLORS::BLACK);
			cout << point;
			cout << " ";
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
			case CODES::r: load();           break;
			case CODES::d: dump_to_png();    break;

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
	align_field(val.size());
}
void MainMenu::align_field(size_t val_size)
{
	auto cell_sizes = get_cell_sizes();
	auto s_ptr = max_element(cell_sizes.begin(),cell_sizes.end());
	auto max_size =  s_ptr != cell_sizes.end()? *s_ptr:-1;
	for (int i = 0; i < string_number; i++)
	{
		auto curr_str = string_names[i];
		auto cell_size = tab_field[curr_str][current_pos.x].size();
		if (cell_size < max_size && max_size != -1)
		{
			size_t alignment_size = max_size - cell_size;
			string alignment(alignment_size, ' ');

			tab_field[curr_str][current_pos.x] += alignment;
		}
	}
	/*int string_to_be_unchanged = current_pos.y;
	for (int i = 0; i < string_number; i++)
	{
		if (i != string_to_be_unchanged)
		{
			auto curr_str  = string_names[i];
			auto cell_size = tab_field[curr_str][current_pos.x].size();

			if (cell_size < val_size)
			{
				size_t alignment_size = val_size - cell_size;		
				string alignment(alignment_size,' ');

				tab_field[curr_str][current_pos.x] += alignment;
			}
		}

	}*/
}
vector<int> MainMenu::get_cell_sizes()
{
	int x = current_pos.x;

	vector<int> sizes;
	for (int y = 0; y < 6; ++y)
	{
		auto curr_str = string_names[y];
		auto cell_size = tab_field[curr_str][x].size();
		sizes.push_back(cell_size);
	}
	return sizes;
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
		for (auto v : tab_field[name]) val += " "+v+" ";
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

void MainMenu::load()
{
	cout << "enter tab file path:";
	string path;
	cin >> path;
	make_tab_field(read_tab_file(path));
	align_loaded_field();
}
vector<string> MainMenu::read_tab_file(const string& file)
{
	ifstream tab_file(file);
	if (!tab_file)
	{
		cout << "can not read " << file << "!" << endl;
		Sleep(60);
		return vector<string>();
	}
	vector<string> values;
	for (size_t i = 0; i < string_number; i++)
	{
		string val;
		getline(tab_file, val);
		values.push_back(val);
	}
	tab_file.close();

	return values;
}
void MainMenu::make_tab_field(const vector<string>& lines)
{
	auto substr = [&](const string& str, int beg, int end)
	{
		string sub;
		for (int i = beg; i < end; ++i)sub += str[i];
		return sub;
	};
	for (auto& line : lines)
	{
		string tabs = substr(line, 3, line.size());
		char string_name = line[0];
		tab_field[string_name] = split_tab_line(tabs);
	}
}
vector<string> MainMenu::split_tab_line(const string& tab)
{
	vector<string> cells;

	istringstream iss(tab);
	string val;
	while (getline(iss, val, ' '))
	{
		if(!val.empty())
			cells.push_back(val);
	}
	return cells;
}
void MainMenu::align_loaded_field()
{
	Coord max = get_max_pos();
	for (int x = 0; x < max.x; x++)
	{
		for (int y = 0; y < max.y; y++)
		{
			current_pos.x = x;
			current_pos.y = y;

			auto string_name = string_names[y];
			auto curr_size = tab_field[string_name][x].size();
			align_field(curr_size);
		}
	}
}

void MainMenu::dump_to_png()
{
	cout << "it will save tab as .png anyway!" << endl;
	cout << "enter path:";

	string path;
	cin >> path;
	dump(path);
}

vector<vector<sf::Text*>> MainMenu::convert_tabs_to_drawable_text()
{
	vector<vector<sf::Text*>> tab_vec;
	sf::Vector2f pos(0.0f, 0.0f);

	int size = 30;
	cout << pos.x << "  " << pos.y << endl;
	for (size_t i = 0; i < string_number; i++)
	{
		auto name = string_names[i];
		auto tabs = tab_field[name];
		string line;
		line += name;
		line += '|';

		vector<sf::Text*> tab_line;

		if (i == 0)size = 35;
		else if (i > 1 && i <= 2)size -= 2;
		else size = 30;
		sf::Text* text = new sf::Text(line, font, size);
		text->setPosition(pos);
		tab_line.push_back(text);

		bool move_y_back = false;
		for (auto s : tabs)
		{
			sf::Text* val = nullptr;
			pos.x += 30;
			if (s == "-")
				val = new sf::Text("-", font, 30);
			else
			{
				val = new sf::Text(s, font, 25);
				pos.y += 5.0f;
				move_y_back = true;
			}
			val->setPosition(pos);
			if (move_y_back)
			{
				pos.y -= 5.0f;
				move_y_back = false;
			}
			tab_line.push_back(val);
		}
		tab_vec.push_back(tab_line);

		pos.y += 30;
		pos.x = 0;

	}

	return tab_vec;
}
void MainMenu::take_screenshot(sf::RenderWindow& window,
							   const string& path)
{
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	sf::Image screenshot = texture.copyToImage();
	screenshot.saveToFile(path);
}
vector<vector<sf::Text*>> MainMenu::slice_tab(vector<vector<sf::Text*>>& tabs, 
											  int begin, 
											  int end)
{
	vector<vector<sf::Text*>> slice;
	for (auto& line : tabs)
	{
		vector<sf::Text*> line_slice = fp::slice(line, begin, end);
		slice.push_back(line_slice);
	}

	return slice;
}
void MainMenu::dump(const string& path)
{
	vector<vector<sf::Text*>> tab_vec = convert_tabs_to_drawable_text();
	
	int rounds = should_slice(tab_vec[0].size()) ? get_slice_number(tab_vec[0].size()) : 1;
	int start = 0;
	int end = tab_vec[0].size() < 22 ? tab_vec[0].size() : 22;
	int round_counter = 0;
	for (int i = 0; i < rounds; ++i)
	{
		string _path = path;
		string name = _path.insert(path.find('/')+1, to_string(round_counter));

		auto slice = slice_tab(tab_vec, start, end);
		if (i > 0)slice = move_slice_left(slice);
		render_tabs(slice, name);
		round_counter++;

		start = end + 1;	
		const int& MDTCN = MAX_DRAWABABLE_TAB_CELL_NUMBER;
		end = start + MDTCN > tab_vec[0].size() ? tab_vec[0].size() : start + MDTCN;
	}
}
bool MainMenu::should_slice(size_t tab_line_size)
{
	return (tab_line_size / MAX_DRAWABABLE_TAB_CELL_NUMBER) >= 2;
}
size_t MainMenu::get_slice_number(size_t tab_line_size)
{
	int additional = tab_line_size % 2 == 0 ? 0 : 1;
	int slice_number = tab_line_size / MAX_DRAWABABLE_TAB_CELL_NUMBER;
	return slice_number + additional;
}
void MainMenu::render_tabs(vector<vector<sf::Text*>>& tabs,
						   const string& path)
{
	sf::RenderWindow window(sf::VideoMode(720, 320), "test");

	int counter = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		take_screenshot(window, path);
		if (counter > 5) window.close();


		window.clear();
		for (auto tabs : tabs)
		{
			for (auto t : tabs)
			{
				window.draw(*t);
			}
		}
		window.display();
		++counter;
	}
}
vector<vector<sf::Text*>> MainMenu::move_slice_left(vector<vector<sf::Text*>>& tabs)
{
	vector<vector<sf::Text*>> lines;
	sf::Vector2f pos(0.0f, 0.0f);

	vector<sf::Text*> line;
	for (auto& line : tabs)
	{
		for (auto* cell : line)
		{
			sf::Text* new_cell = new sf::Text(*cell);
			new_cell->setPosition(pos);
			line.push_back(new_cell);
			pos.x += 30.0f;
		}
		lines.push_back(line);
		pos.x = 0.0f;
		pos.y += 30.0f;
	}
	return lines;
}