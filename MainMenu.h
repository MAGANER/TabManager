#pragma once
#include"SFML/Graphics.hpp"
#include"Functools.hpp"
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<Windows.h>

namespace TabManager
{
using namespace std;
namespace fp = Functools;
struct Coord
{
	int x, y;
};

typedef vector<string> svec;
class MainMenu
{
private:
	map<char, svec> tab_field; //for 6-string guitar
	const char* string_names   = "eBGDAE\0";
	const size_t string_number = 6;

	bool any_action = true;

	enum class CODES
	{
		i = 105, //increase field
		a = 97,  //add new value
		s = 115, //save
		r = 114, //read
		d = 100, //dump to png

		j = 106, //down
		k = 107, //up
		h = 104, //left
		l = 108, //right
	};
	enum class COLORS
	{
		BLACK   = 0,
		GREEN   = 2,
		RED     = 4,
		MAGENTA = 5,
	};

	Coord start_position = { 2,0 };
	Coord current_pos = { 0, 0 }; //y can not be higher then 6

	//moving directions
	const Coord LEFT { -1,0  };
	const Coord RIGHT{ 1,0   };
	const Coord UP   { 0,-1  };
	const Coord DOWN { 0,1   };

	bool key_pressed = false;

	sf::Font font;
	const int MAX_DRAWABABLE_TAB_CELL_NUMBER = 22;
public:
	MainMenu();
	~MainMenu();
private:
	void init_field();

	void print_field();
	inline void increase_field();

	void run();

	void move(const Coord& dir);
	bool can_move(const Coord& increaser);
	Coord get_max_pos();

	void setcolor(COLORS _textcol, COLORS backcol);

	void add_new_value();
	void align_field(size_t val_size);
	void insert_to_field(const string& val);

	void save();
	void write_tab_down(const string& path);

	void load();
	vector<string> read_tab_file(const string& path);
	void make_tab_field(const vector<string>& lines);
	vector<string> split_tab_line(const string& tab);
	void align_loaded_field();

	void dump_to_png();
	void dump(const string& path);
	vector<vector<sf::Text*>> convert_tabs_to_drawable_text();
	void take_screenshot(sf::RenderWindow& window,
						 const string& path);
	void render_tabs(vector<vector<sf::Text*>>& tabs,
					 const string& path);
	inline bool should_slice(size_t tab_line_size);
	inline size_t get_slice_number(size_t tab_line_size);
	vector<vector<sf::Text*>> slice_tab(vector<vector<sf::Text*>>& tabs, int begin, int end);
	vector<vector<sf::Text*>> move_slice_left(vector<vector<sf::Text*>>& tabs);
};
};

