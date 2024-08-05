#include <iostream>
#include <vector>
#include <cstring>
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
	HashTable(int newSize);
	bool isEmpty();
	void insert(AlienEncounters alien);
	void printHashTable();
};

HashTable::HashTable(int newSize) {
	bucket.resize(newSize);
	bucketSize = newSize;
}

bool HashTable::isEmpty() {
	return bucketLoad == 0;
}

int HashTable::hashFunction(string city) {
	int hashCode = 0;
	for (int i = 0; i < city.length(); i++) {
		hashCode = (hashCode * 31 + city[i]) % bucketSize;
	}
	return hashCode;
}

void HashTable::rehash() {
	int oldBucketSize = bucketSize;
	bucketSize *= 2;
	vector<pair<int, vector<AlienEncounters>>> newBucket(bucketSize);

	for (int i = 0; i < oldBucketSize; i++) {
		for (AlienEncounters& alien : bucket[i].second) {
			int newHashKey = hashFunction(alien.city);
			newBucket[newHashKey].second.push_back(alien);
		}
	}
	bucket = newBucket;
}

void HashTable::insert(AlienEncounters alien) {
	int hashKey = hashFunction(alien.city);
	bool keyExists = false;
	// inserting repeated alien is ignored
	for (AlienEncounters& existingAlien : bucket[hashKey].second) {
		if (existingAlien == alien) {
			keyExists = true;
			break;
		}
	}
	// separate chaining
	if (!keyExists) {
		bucket[hashKey].second.push_back(alien);
		bucketLoad++;
	}
	// check if rehashing is needed
	if (float(bucketLoad) / float(bucketSize) >= loadFactor)
		rehash();
	return;
}

void HashTable::printHashTable() {
	for (int i = 0; i < bucketSize; i++) {
		if (bucket[i].second.size() == 0)
			continue;
		for (auto bItr = bucket[i].second.begin(); bItr != bucket[i].second.end(); bItr++) {
			cout << "State: " << bItr->state << endl;
		}
	}
	return;
}
