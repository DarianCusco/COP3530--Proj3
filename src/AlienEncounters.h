#pragma once
#include <iostream>
#include <string>
using namespace std;

struct AlienEncounters {
	string city;
	string state;
	string country;
	string shape;
	string dateSighted;
	AlienEncounters(string city, string state, string country, string shape, string dateSighted);
};
