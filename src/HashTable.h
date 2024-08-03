#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "AlienEncounters.h"
using namespace std;

class HashTable {
private:
	int bucketLoad = 0;
	int bucketSize = 50;
	float loadFactor = 0.75f;
	vector<pair<int, vector<AlienEncounters>>> bucket;

	int hashFunction(string city);
	void rehash();
public:
	HashTable();
	bool isEmpty();
	void insert(AlienEncounters alien);
	void remove(int key);
	AlienEncounters getAlien(int key);
	void printHashTable();
};