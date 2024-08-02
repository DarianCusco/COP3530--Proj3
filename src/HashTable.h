#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "AlienEncounters.h"
using namespace std;
// Separate chaining w/ linked lists for hash table

class HashTable {
private:
	int bucketLoad = 0;
	const static int bucketSize = 50;
	float loadFactor = 0.75f;
	pair<int, vector<AlienEncounters>> bucket[bucketSize]; // array of int vector pairs
public:
	bool isEmpty();
	int hashFunction(int key);
	void insert(int key, AlienEncounters alien);
	void remove(int key); // not currently used
	AlienEncounters getAlien(int key); // not currently used
	void printHashTable(); // not currently used
	void rehash();
};