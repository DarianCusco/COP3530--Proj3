#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "alienEncounters.h"

using namespace std;

class HashTable {
private:
    vector<pair<int, vector<AlienEncounters>>> bucket;
    int bucketLoad;
    int bucketSize;
    float loadFactor;

    int hashFunction(string city);
    void rehash();

public:
    HashTable();
    bool isEmpty();
    void insert(AlienEncounters alien);
    AlienEncounters getAlien(int key);
    void printHashTable();
    int getBucketSize() const; // Mark as const
    vector<pair<int, vector<AlienEncounters>>> getBucket() const; // Mark as const
};

HashTable::HashTable() : bucketLoad(0), bucketSize(16), loadFactor(0.75) {
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
    for (AlienEncounters& existingAlien : bucket[hashKey].second) {
        if (existingAlien == alien) {
            keyExists = true;
            break;
        }
    }
    if (!keyExists) {
        bucket[hashKey].second.push_back(alien);
        bucketLoad++;
    }
    if (float(bucketLoad) / bucketSize >= loadFactor) {
        rehash();
    }
}

AlienEncounters HashTable::getAlien(int key) {
    if (bucket[key].second.empty())
        return AlienEncounters("N/A", "N/A", "N/A", "N/A", "N/A");
    else if (bucket[key].second.size() == 1)
        return bucket[key].second[0];
    else {
        return bucket[key].second[0];
    }
}

void HashTable::printHashTable() {
    for (int i = 0; i < bucketSize; i++) {
        cout << "Bucket " << i << ": ";
        for (const auto& alien : bucket[i].second) {
            cout << alien.city << " ";
        }
        cout << endl;
    }
}

int HashTable::getBucketSize() const {
    return bucketSize;
}

vector<pair<int, vector<AlienEncounters>>> HashTable::getBucket() const {
    return bucket;
}