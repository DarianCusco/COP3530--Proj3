#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "AlienEncounters.h"
#include <list>
using namespace std;

int main() {
	int array[5] = { 1, 2, 3, 4, 5 };
	ifstream myData;
	myData.open("../data/ufo_sightings.csv");
	if (!myData.is_open()) { cout << "file not properly opened" << endl; }
	else {

		string _city;
		string _state;
		string _country;
		string _shape;

		string _sightedYear;
		string _sightedMonth;
		string _sightedDay;

		string throwaway;

		vector<AlienEncounters> dataContainer;


		string line;
		if (getline(myData, line)) { cout << "Header: " << line << endl; }
		for (int i = 0; i < 10; i++) { //Change to "while (getline(myData, line))" to store all data points
			getline(myData, line);
			stringstream ss(line);

			getline(ss, throwaway, '"');
			getline(ss, _city, '"');  //stores city info
			getline(ss, throwaway, '"');
			getline(ss, _state, '"');  //stores state info
			getline(ss, throwaway, '"');
			getline(ss, _country, '"'); //stores country info
			getline(ss, throwaway, '"');
			getline(ss, _shape, '"'); //stores shape info
			getline(ss, throwaway, '"');

			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');
			getline(ss, throwaway, '"');

			getline(ss, _sightedYear, '"');  //stores sighted year
			getline(ss, throwaway, '"');
			getline(ss, _sightedMonth, '"');  //stores sighted month
			getline(ss, throwaway, '"');
			getline(ss, _sightedDay, '"');  //stores sighted day

			string _sightedDate;
			_sightedDate = _sightedMonth + "/" + _sightedDay + "/" + _sightedYear;  //Adds all calendar info into one variable

			AlienEncounters temp(_city, _state, _country, _shape, _sightedDate);
			dataContainer.push_back(temp);

		}
		for (auto i : dataContainer) {
			cout << i.state << endl;
		}
	}
	return 0;
}