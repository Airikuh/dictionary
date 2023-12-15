//QuadraticProbing.cpp File For Hash Table Functions
#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

//Pre-Condition: Hash table is already itialized.
//Post Condition:Hash Table return true if number is prime
//else false.
bool isPrime(int n) {
    bool flag = true;

    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

//Pre-Condition:  Hash table is already itialized.
//Called from rehash or constructor.
//Post Condition: Hash Table return size is Prime.
int nextPrime(int n) {
    if (n <= 0)
        n = 3;

    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

//Pre-Condition:  Hash table is already itialized.
//Post Condition: Returns integer value for incoming 
//string object.
int hash1(const string& key) {
    int hashVal = 0;

    for (unsigned int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];

    return hashVal;
}


//Pre-Condition: Existing hash table
//Call From myhash
//Post Condition: Returns integer value
int hash1(int key) {
    return key;
}
