#pragma once
#include<vector>
#include<map>
#include<iostream>
namespace TabManager
{
using namespace std;

class MainMenu
{
private:
	map<char, vector<char>> tab_field; //for 6-string guitar
	const char* string_names   = "eBGDAE\0";
	const size_t string_number = 6;
public:
	MainMenu();
	~MainMenu();
};
};

