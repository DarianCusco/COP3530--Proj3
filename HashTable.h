#pragma once
#include <iostream>
#include <list>
#include <string>
#include "AlienEncounters.h"
using namespace std;
// Separate chaining hash table, current idea is to hash by city?

class HashTable {
private:
	static const int bucketSize = 50;
	float loadFactor = 0.75f;
	list<pair<int, AlienEncounters>> bucket[bucketSize];
public:
	bool isEmpty();
	int hashFunction();
	void insert(int key, AlienEncounters alien);
	void remove(int key);
	AlienEncounters getAlien(int key);
	void printHashTable();
};