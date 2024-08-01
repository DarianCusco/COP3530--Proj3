#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "AlienEncounters.h"
using namespace std;
// Separate chaining w/ linked lists for hash table, current idea is to hash by city

class HashTable {
private:
	int bucketLoad = 0;
	const static int bucketSize = 50;
	float loadFactor = 0.75f;
	pair<int, vector<AlienEncounters>> bucket[bucketSize];
public:
	bool isEmpty();
	int hashFunction(int key, string city);
	void insert(int key, AlienEncounters alien);
	void remove(int key);
	AlienEncounters getAlien(int key);
	void printHashTable();
};