#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream myData;
    myData.open("../data/ufo_sightings.csv");
    if (!myData.is_open()){cout << "file not properly opened" << endl;}
    else {
        string line;
         if (getline(myData, line)) {cout << "Header: " << line << endl;}

         vector<vector<string>> data;
         for (int i = 0; i < 10; i++) {
            getline(myData, line);
            stringstream ss(line);
            string field;
            vector<string> dataRow;

            while (getline(ss, field, ',')) {
                dataRow.push_back(field);
            }
            data.push_back(dataRow);
         }

    for (const auto &row : data) {
    for (const auto &field : row) {
        std::cout << field << " | ";
    }
    std::cout << '\n';
}

    }
    return 0;
}