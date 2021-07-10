#pragma once
#include<vector>
#include<map>
#include<iostream>
#include<conio.h>
#include<stdio.h>
namespace TabManager
{
using namespace std;

typedef vector<char> cvec;
class MainMenu
{
private:
	map<char, cvec> tab_field; //for 6-string guitar
	const char* string_names   = "eBGDAE\0";
	const size_t string_number = 6;

	bool any_action = true;

	enum class CODES
	{
		i = 105,
	};
public:
	MainMenu();
	~MainMenu();
private:
	void init_field();

	void print_field();
	inline void increase_field();
	void run();
};
};

