#pragma once
#include<Windows.h>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<stdio.h>

namespace TabManager
{
using namespace std;


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
	void insert_to_field(const string& val);

	void save();
	void write_tab_down(const string& path);
};
};

