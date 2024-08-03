#include "HashTable.h"

bool HashTable::isEmpty() {
	int sum = 0;
	for (int i = 0; i < bucketSize; i++)
		sum += bucket[i].second.size();
	if (sum == 0)
		return true;
	else
		return false;
}
int HashTable::hashFunction(int key) {
	string strKey = to_string(key);
	int hashCode = 0;
	for (int i = 0; i < strKey.length(); i++)
		hashCode += strKey[i] * pow(31, i);
	return hashCode % bucketSize;
}
void HashTable::insert(int key, AlienEncounters alien) {
	int hashKey = hashFunction(key);
	bool keyExists = false;
	// if no existing values at hashKey location
	if (bucket[hashKey].second.size() == 0) {
		bucket[hashKey].second.push_back(alien);
		bucketLoad++;
	}
	else {
		// check for collisions
		for (int i = 0; i < bucket[hashKey].second.size(); i++) {
			if (bucket[hashKey].second[i] == alien) {
				keyExists = true;
			}
		}
	}
	if (!keyExists) {
		bucket[hashKey].second.push_back(alien);
		bucketLoad++;
	}
	if (float(bucketLoad / bucketSize) >= loadFactor) {
		rehash();
	}
	return;
}
/*AlienEncounters HashTable::getAlien(int key) {
	int hashKey = hashFunction(key);
	return bucket->second[hashKey];
}
void HashTable::rehash() {

}
void HashTable::remove(int key) {
	// this function isn't really getting used
	return;
}
void HashTable::printHashTable() {

}*/