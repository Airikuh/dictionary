//QuadraticProbing.h Header File For HashTable Class
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
using namespace std;

//Function Prototypes
int nextPrime(int n);
int hash1(const string& key);
int hash1(int key);

//Global Variable Declarations For Statistics
static int numberCollisions = 0;
static int longestChain = 0;
static double averageChain = 1.0;


//Hash Table Class to Create Table
template <typename HashedObj>
class HashTable {
public:
	//Pre-Condition: None
	//Post Condition: Table initialized to empty. Array Initialized
	//to next prime number size.
	explicit HashTable(int size = 101) : array(nextPrime(size)) {
		makeEmpty();
	}

	//Pre-Condition: Another function has called it
	//Post Condition: Returns true if position in hash table is 
	//currently being used, else false.
	bool contains(const HashedObj& x) const {
		return isActive(findPos(x));
	}

	//Pre-Condition: Existing vector.
	//Post Condition: Empties vector's elements.
	void makeEmpty() {
		//Initialize Size of Vector to Zero
		currentSize = 0;
		//Loop Through Contents of Vector, Emptying Each
		//Position in Vector
		for (int i = 0; i < array.size(); i++)
			array[i].info = EMPTY;
	}

	//Insert Element Check 
	//Pre-Condition: Hash table has been initialized.
	//Post Condition: Returns false if spot in table taken,  
	//else puts element in position, checks if needs resized,
	//and returns true.
	bool insert(const HashedObj& x) {
		// Insert x as active
		int currentPos = findInsertPos(x);
		if (isActive(currentPos))
			return false;

		array[currentPos] = HashEntry(x, ACTIVE);

		// Rehash; see Section 5.5
		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition: Returns true if remove successful,
	//else return false
	bool remove(const HashedObj& x) {
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;

		array[currentPos].info = DELETED;
		return true;
	}

	//Pre-Condition: Hash table has been initialized
	//Post Condition: Returns Current Size
	int getCurrentSize() {
		return currentSize;
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition:  Returns total size of hash table
	int getTotalSize() {
		return array.size();
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition:  Returns load factor of hash table
	double getLoadFactor() {
		return double(currentSize) / array.size();
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition:  Returns number of collisions insertion encountered
	int getNumberCollisions() {
		return numberCollisions / 2;
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition:  Returns longest collision chain
	int getLongestLength() {
		return longestChain / 2;
	}

	//Pre-Condition: Hash table has been initialized.
	//Post Condition:  Returns average collision chain length
	double getAverageLength() {
		return averageChain / currentSize;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry {
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) { }
	};

	vector<HashEntry> array;
	int currentSize;

	//Pre-Condition: Hash table already initialized
	//Post Condition: Returns true if position being used, 
	//else returns false
	bool isActive(int currentPos) const {
		return array[currentPos].info == ACTIVE;
	}

	//Pre-Condition: Hash table already initialized
	//Post Condition: Returns index number position of 
	//incoming object
	int findPos(const HashedObj& x) const {
		int offset = 1;
		int currentPos = myhash(x);

		// Assuming table is half-empty, and table length is prime,
		// this loop terminates
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x) {
			currentPos += offset;  // Compute ith probe
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}

		return currentPos;
	}

	//Pre-Condition:Hash table already initialized
	//Post Condition: Returns index number of position available for
	//inserting another item to table. Increments statistics counts.
	int findInsertPos(const HashedObj& x) const {
		int offset = 1;
		int currentPos = myhash(x);
		averageChain++;

		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x) {
			numberCollisions++;
			averageChain++;
			currentPos += offset;
			offset += 2;
			if (currentPos >= array.size()) {
				currentPos -= array.size();
			}
			if (longestChain < offset) {
				longestChain = offset;
				++longestChain;
			}
		}

		return currentPos;
	}

	//Pre-Condition: Called by another function because current table size too 
	//small
	//Post Condition: Hash table size increased, all hash table values copied to 
	//new table
	void rehash() {
		numberCollisions = 0;
		averageChain = 0.0;
		longestChain = 0;
		vector<HashEntry> oldArray = array;

		// Create New Double-Sized, Empty Table, Call to Next Prime to Get New Size of 
		//Next Largest Prime Number
		array.resize(nextPrime(2 * oldArray.size()));
		for (int j = 0; j < array.size(); j++)
			array[j].info = EMPTY;

		// Copy table over
		currentSize = 0;
		for (int i = 0; i < oldArray.size(); i++)
			if (oldArray[i].info == ACTIVE)
				insert(oldArray[i].element);
	}


	//Pre-Condition: Hash table already initialized.
	//Call from findPos or findInsertPos
	//Post Condition: String to integer conversation for
	//return 
	int myhash(const HashedObj& x) const {
		int hashVal = hash1(x);

		hashVal %= array.size();
		if (hashVal < 0)
			hashVal += array.size();

		return hashVal;
	}
};


#endif
