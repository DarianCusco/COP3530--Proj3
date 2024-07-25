#include "HashTable.h"

bool HashTable::isEmpty() {
	int sum;
	for (int i = 0; i < bucketSize; i++)
		sum += bucket[i].size();
	if (sum == 0)
		return true;
	else
		return false;
}
int HashTable::hashFunction() {

}
void HashTable::insert(int key, AlienEncounters alien) {

}
void HashTable::remove(int key) {

}
AlienEncounters HashTable::getAlien(int key) {

}
void HashTable::printHashTable() {

}
