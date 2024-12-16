#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "bin.h"
#include "HashTable.h"

using namespace std;

void ReadFile(vector<AlienEncounters>& dataContainer) {
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

		string line;

		getline(myData, line);
		//Using 50,000 for testing porpuses
		while (getline(myData, line)) { //Change to "while (getline(myData, line))" to store all data points
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

			//Skips uneeded lines
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
	}
}

void writeBins(vector<vector<pair<string, int>>>dataContainer) {
	ofstream myNewData("../data/sorted_ufo_sightings_bins.csv");

	for (int i = 0; i < dataContainer.size(); i++) {
		// cout << "Bins: " << binRanges[i].first << "-" << binRanges[i].second;

		for (auto j : dataContainer[i]) {
			myNewData << j.first << " " << j.second << ",";
		}
		myNewData << "\n";
	}
}

void writeHashFunction(const HashTable& table) {
	ofstream myNewData("../data/sorted_ufo_sightings_Hash.csv");
	if (!myNewData.is_open()) {
		cout << "Failed to open output file." << endl;
		return;
	}
	vector<pair<int, vector<AlienEncounters>>> bucket = table.getBucket();

	vector<pair<string, int>> Data; // string is state, int is visit count

	for (int i = 0; i < table.getBucketSize(); i++) {
		for (int j = 0; j < bucket[i].second.size(); j++) {
			// Check if the state already exists in the Data vector
			auto it = find_if(Data.begin(), Data.end(), [&](const pair<string, int>& p) {
				return p.first == bucket[i].second[j].state;
				});
			if (it == Data.end()) {
				// If the state doesn't exist, add it with a count of 1
				Data.push_back(make_pair(bucket[i].second[j].state, 1));
			}
			else {
				// If the state exists, increment the count
				it->second++;
			}
		}
	}

	for (const auto& entry : Data) {
		myNewData << entry.first << " " << entry.second << ",";
		myNewData << "\n";
	}
}
map<string, int> getCountryStats(vector<AlienEncounters>& dataContainer) {
	map<string, int> freq;
	for (auto dt : dataContainer) {
		freq[dt.state]++;
	}
	return freq;
}

void createJSONFile(string csvFile, string jsonFile) {
	/*
	What I expect JSON to look like

	"Group X":
	[
		{"state": y "occurances:" z},
		{"state": y "occurances:" z},
		{"state": y "occurances:" z},
		{"state": y "occurances:" z},
		{"state": y "occurances:" z},
	],
	*/
	map<int, vector<pair<string, int>>> dataGrouped;
	int groupNumber = 1;

	ifstream myData;
	myData.open(csvFile); //opens updated csv file

	if (!myData.is_open()) { cout << "data not loaded properly" << endl; }
	else {
		string line;
		string stateData;
		while (getline(myData, line)) {
			stringstream ss(line);

			while (getline(ss, stateData, ',')) {
				string state;
				int stateOccurances;
				stringstream lineStream(stateData);
				lineStream >> state >> stateOccurances;
				dataGrouped[(groupNumber)].push_back(make_pair(state, stateOccurances));
			}
			groupNumber++;
		}
	}

	ofstream outFile("../data/" + jsonFile);
	bool groupOne = true; //true if first group
	outFile << "{\n";
	for (auto group : dataGrouped) {
		if (!groupOne) { outFile << ",\n"; } //used to seperate groups
		groupOne = false;
		bool firstEntry = true; //true if first data point in group
		outFile << "\"" << "group: " << group.first << "\": [\n";

		for (auto state : group.second) {
			if (!firstEntry) { outFile << ",\n"; } //Used to seperate entries
			firstEntry = false;

			outFile << "{ \"state\": \"" << state.first << "\" , \"count\": " << state.second << "}";
		}
		outFile << "\n  ]";
	}
	outFile << "\n}\n";

}
int main() {
	vector<AlienEncounters> dataContainer;

	ReadFile(dataContainer);
	map<string, int> temp = getCountryStats(dataContainer);

	// Testing purposes
	// for (auto itr : temp) {
	//     cout << itr.first << " " << itr.second <<endl;
	// }   

	//For bins data structure
	auto t1 = Clock::now();
	vector<vector<pair<string, int>>> binnedData = equalFreqBins(temp, 10);
	writeBins(binnedData);
	createJSONFile("../data/sorted_ufo_sightings_bins.csv", "ufo_sightings_Bins.JSON");
	auto t2 = Clock::now();
	cout << "Time taken by bins: " << t2 - t1 << endl;

	t1 = Clock::now();
	HashTable hashTable;
	for (const auto& encounter : dataContainer) {
		hashTable.insert(encounter);
	}

	//For bins data structure
	writeHashFunction(hashTable);
	createJSONFile("../data/sorted_ufo_sightings_Hash.csv", "ufo_sightings_Hash.JSON");
	t2 = Clock::now();
	cout << "Time taken by hash table: " << t2 - t1 << endl;
	return 0;
}
