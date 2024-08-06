#include <iostream>
#include <string>
#include <vector>
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

    bool operator==(const AlienEncounters& alien) {
	if (this->city == alien.city && this->state == alien.state && this->country == alien.country && this->shape == alien.shape && this->dateSighted == alien.dateSighted)
		return true;
	else
		return false;
    }

};