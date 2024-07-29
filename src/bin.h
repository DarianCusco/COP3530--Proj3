#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

bool greaterThan(pair<string, int>& a, pair<string, int>& b) {return a.second > b.second;}

vector<pair<string,int>> sortMap(map<string, int>& mp) {
    vector<pair<string, int>> temp;

    for (auto itr : mp) {
        temp.push_back(itr);
    }
    sort(temp.begin(), temp.end(), greaterThan);
    return temp;
    
}

vector<vector<pair<string, int>>> equalFreqBins(map<string, int>& encounterCount, int numOfBins) {
    int binSize = encounterCount.size() / numOfBins; //gets size of each bin
    int remainder = encounterCount.size() % numOfBins; //if not perfectly dividible we use remainder

    vector<pair<string, int>> sortedMap = sortMap(encounterCount);

    vector<vector<pair<string, int>>> bins(numOfBins); //stores states and incidents
    vector<pair<int, int>> binRanges(numOfBins);

    auto itr = sortedMap.begin();
    for (int i = 0; i < numOfBins; i++) {
        int currBinSize = binSize + (remainder > i ? 1 : 0); //if we have a remainder, bin size will be 1 bigger
        int minVal = itr->second;

        for (int j = 0; j < currBinSize; j++) {
            bins[i].push_back(make_pair(itr->first, itr->second));
            itr++;
        }

        int maxVal = (bins[i].empty() ? minVal : bins[i].back().second); // Maximum value in the bin
        binRanges[i] = make_pair(minVal, maxVal); // Stores the range
    }
    return bins;
    // for (int i = 0; i < bins.size(); i++) {
    //     // cout << "Bins: " << binRanges[i].first << "-" << binRanges[i].second;
        
    //     for (auto j : bins[i]) {
    //         cout << j.first << " " << j.second  << ",";
    //         }
    //     cout <<endl;
    // }
}
    

