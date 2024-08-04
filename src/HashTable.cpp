#include "HashTable.h"
#include <cmath>

HashTable::HashTable() {
	bucket.resize(bucketSize);
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
	if (float(bucketLoad / bucketSize) >= loadFactor) {
		rehash();
	}
	return;
}

void HashTable::remove(int key) {
	// This function isn't really getting used
	return;
}
vector<pair<int, vector<AlienEncounters>>> HashTable::getBucket() {
	return bucket;
}

AlienEncounters HashTable::getAlien(int key) {
	// Implementation needed
	if (bucket[key].second.size() == 0)
		return (AlienEncounters("N/A", "N/A", "N/A", "N/A", "N/A"));
	else if (bucket[key].second.size() == 1)
		return bucket[key].second[0];
	else {
		// somehow find correct alien from separate chaining vector?
	}
}
int HashTable::getbucketSize() {
	return bucketSize;
}
void HashTable::printHashTable() {
	// Implementation needed
}
