#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "bin.h"

using namespace std;

struct AlienEncounters {
    string city;
    string state;
    string country;
    string shape;
    string dateSighted;

    AlienEncounters(string city, string state, string country, string shape, string dateSighted) {
        this->city = city;
        this->state = state;
        this->country = country;
        this->shape = shape;
        this->dateSighted = dateSighted;
    };
};
void ReadFile(vector<AlienEncounters>& dataContainer) {
    ifstream myData;
    myData.open("../data/ufo_sightings.csv");
    if (!myData.is_open()){cout << "file not properly opened" << endl;}
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
        if (getline(myData, line)) {cout << "Header: " << line << endl;}
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
    ofstream myNewData("../data/sorted_ufo_sightings.csv");

     for (int i = 0; i < dataContainer.size(); i++) {
        // cout << "Bins: " << binRanges[i].first << "-" << binRanges[i].second;
        
        for (auto j : dataContainer[i]) {
            myNewData << j.first << " " << j.second  << ",";
            }
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

    if (!myData.is_open()) {cout << "data not loaded properly" << endl;}
    else {
        string line;
        string stateData;
        while(getline(myData, line)) {
            stringstream ss(line);

            while(getline(ss, stateData, ',')) {
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
        if (!groupOne) {outFile << ",\n";} //used to seperate groups
        groupOne = false;
        bool firstEntry = true; //true if first data point in group
        outFile << "\"" <<"group: " << group.first << "\": [\n";

        for (auto state : group.second) {
            if (!firstEntry) {outFile << ",\n";} //Used to seperate entries
            firstEntry = false;

            outFile << "{ \"state\": \"" << state.first << "\" , \"count\": " << state.second <<"}";
        }
        outFile << "\n  ]";
    }
    outFile << "\n}\n";
    
}
int main() {
    vector<AlienEncounters> dataContainer;

    ReadFile(dataContainer);
    map<string, int> temp = getCountryStats(dataContainer);

	//Testing purposes
    // for (auto itr : temp) {
    //     cout << itr.first << " " << itr.second <<endl;
    // }   

    vector<vector<pair<string, int>>> binnedData = equalFreqBins(temp, 10);
    writeBins(binnedData);
    createJSONFile("../data/sorted_ufo_sightings.csv", "ufo_sightings_test.JSON");
    return 0;
}