//Source.cpp Source File For Spell Checking Program
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "QuadraticProbing.h"
using namespace std;


//Function Prototypes
string toLowerCase(string);
void letterDelete(HashTable<string>& dictionary, string word);
void neighborSwap(HashTable<string>& dictionary, string word);
void letSwap(HashTable<string>& dictionary, string word);
void replaceLetter(HashTable<string>& dictionary, string word);


//Pre-Condition: Command Line Arguments and text files are already added to project.
//Post-Condition: Saves suggestions and statistics to output files.
int main(int argc, char* argv[]) {


	//Variable Declarations and Initializations
	int numWords;
	string dict;
	string text;
	//Command Line Arguments Variable Initializations
	numWords = stoi(argv[1]);
	dict = argv[2];
	text = argv[3];
	//Dictionary File Declaration and open
	ifstream dictFile;
	dictFile.open(dict);

	//Dictionary Hash Table Created
	HashTable<string> dictionary = HashTable <string>(2 * numWords);

	//If File is Open Insert Contents into Hash Table and Report to Cerr
	if (dictFile) {
		//Variable Declarations
		string temp;
		dictFile >> temp;
		//While Loop to Loop Through Contents and Insert 
		while (dictFile) {
			dictionary.insert(temp);
			dictFile >> temp;
		}

		//Report to Cerr For OutPut File
		cerr << "Number of words " << dictionary.getCurrentSize() << ", ";
		cerr << "Total size : " << dictionary.getTotalSize() << ", ";
		cerr << "Load factor : " << dictionary.getLoadFactor() << endl;
		cerr << "Collisions : " << dictionary.getNumberCollisions() << ", ";
		cerr << "Average chain length: " << dictionary.getAverageLength() << ", ";
		cerr << "Longest Chain length: " << dictionary.getLongestLength() << endl << endl;

	}

	//Else Statement To Display if Issue With File
	else {
		cout << "Problem With Dictionary File, Check Command Line Arguments!" << endl;
	}

	//Text File Declaration and Open
	ifstream textFile;
	textFile.open(text);

	//If Text File is Open Get Contents of File
	if (textFile) {
		//Variable Declarations
		int lineNum = 1;
		string currLine;

		//Get Contents of File
		getline(textFile, currLine);

		//While Loop to Loop Through Contents
		while (textFile) {

			//For Loop to Change Anything That is Not a Letter to a Blank Space
			for (int i = 0; i < currLine.length(); i++) {
				if (!isalpha(currLine[i]))
					currLine[i] = ' ';
			}

			//String Stream Object to Put Contents Into Buffer For Checks and Operations
			stringstream ssin(currLine);
			//While Statement to Loop Through as Long as There Are Items in Buffer
			while (ssin.good()) {
				string word;
				//Read Buffer Word in For Check
				ssin >> word;
				//If Statement to Loop Through For Words
				if (word != "") {
					//If Statement to Check and Display Suggestions as Long as Word is NOT in Dictionary
					if (!dictionary.contains(word)) {
						//Call to Function to Change Uppercase to Lowercase
						string currentWord = toLowerCase(word);

						//If Statement to Check Word Against Hash Table and Offer Suggested Spellings
						if (!dictionary.contains(currentWord)) {
							cout << left << setw(10) << word << "(" << setw(2) << lineNum << ") : ";
							//Function Calls
							letterDelete(dictionary, word);
							letSwap(dictionary, word);
							neighborSwap(dictionary, word);
							replaceLetter(dictionary, word);

							cout << endl;

						}
					}
				}
			}
			//Increment to Next Line
			++lineNum;
			//Get Next Line For Loop Checks
			getline(textFile, currLine);
		}

	}
	//Else Statement to Display if Problem With Text File
	else {
		cout << "Problem With Text File, Check Command Line Arguments!" << endl;
	}

	//Get Character 
	getchar();


	return 0;
}

//Pre-Condition: There is a string variable.
//Post Condition: Returns string with lowercase letters.
string toLowerCase(string word) {
	//Variable Declarations and Initializations
	int x = 0;
	char c = word[x];

	//While Loop to Cycle Through Each Character of the Word
	//And Check Against ASCII Table, Change Uppercase
	//To Lowercase
	while (x < word.length()) {
		//If Statenent to Check if Character Falls Within
		//ASCII Table Uppercase Values
		if (c >= 65 && c <= 90) {
			//By Adding 32, an Uppercase Letter Becomes it's Lowercase
			//Version
			c = c + 32;
			//Replace Character in String
			word[x] = c;
		}
		//Increment to Next Letter to Check if Uppercase
		++x;
	}

	//Return Lowercase Word
	return word;
}

//Pre-Condition: There is a string variable.
//Post Condition: String is changed by deleting 
//a letter then displayed as long as it is part of the dictionary.
void letterDelete(HashTable<string>& dictionary, string word) {
	//For Loop to Cycle Through Word Trying Each Letter Delete
	for (int i = 0; i < word.length(); ++i) {
		//Variable to Hold Information
		string temp;
		//Delete Letter and Use Temporary Value to Store Information
		temp = word.substr(0, i) + word.substr(i + 1, word.length());
		//Check Changed Word Against Dictionary
		if (dictionary.contains(temp))
			//If In Dictionary Display New Suggested Word
			cout << temp << ' ';
	}
}

//Pre-Condition:There is a string variable.
//Post Condition: Swaps letter with a letter
//next to it then displays as long as it is part of the dictionary.
void neighborSwap(HashTable<string>& dictionary, string word) {
	for (int i = 0; i < word.length() - 1; ++i) {
		//Variable to Hold Information
		string temp = word;
		//Swap Neighbor Letters  and Use Temporary Value to Store Information
		swap(temp[i], temp[i + 1]);
		//Check Changed Word Against Dictionary
		if (dictionary.contains(temp))
			//If In Dictionary Display New Suggested Word
			cout << temp << ' ';
	}
}

//Pre-Condition:There is a string variable.
//Post Condition: Swaps any letter within the string
//then displays as long as it is part of the dictionary.
void letSwap(HashTable<string>& dictionary, string word) {
	for (int i = 0; i <= word.length(); ++i) {
		for (char ch = 'a'; ch <= 'z'; ch++) {
			//Variable to Hold Information
			string temp;
			//Swap Any Letters in String and Use Temporary Value to Store Information
			temp = word.substr(0, i) + ch + word.substr(i, word.length());
			//Check Changed Word Against Dictionary
			if (dictionary.contains(temp))
				//If In Dictionary Display New Suggested Word
				cout << temp << ' ';
		}
	}
}


//Pre-Condition: There is a string variable.
//Post Condition: Replaces each letter with any letter
//in the alphabet then displays as long as it is part of the dictionary.
void replaceLetter(HashTable<string>& dictionary, string word) {
	for (int i = 0; i < word.length(); ++i) {
		//Variable to Hold Information
		string temp = word;
		//For Loop to Cycle Through All Alphabetic Possibilities in All Spaces of Word
		for (char ch = 'a'; ch <= 'z'; ch++) {
			//Store Possibility in Temporary Value
			temp[i] = ch;
			//Check Changed Word Against Dictionary
			if (dictionary.contains(temp))
				//If In Dictionary Display New Suggested Word
				cout << temp << ' ';
		}
	}
}
