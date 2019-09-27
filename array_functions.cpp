/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 *
 *  Finished on: Sep 27, 2019
 *  	Author: Christopher Staunton
 */
#define ARRAY_FUNCTIONS_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
using namespace constants;
using namespace std;

struct entry
{
	string word;
	int number_occurences;
};

entry myEntryArray[100];

int nextSlot = 0;
int currentNumberOfEntries = 0;
bool isOrNot = false;
string holdA = "";
string holdB = "";
entry entryA;
entry entryB;

void clearArray()
{
	for (int i = 0; i < nextSlot; i++)
	{
		myEntryArray[i].word = "";
		myEntryArray[i].number_occurences = 0;
	}
	nextSlot = 0;
	currentNumberOfEntries = 0;
}

int getArraySize()
{
	return currentNumberOfEntries;
}

std::string getArrayWordAt(int i) {
	return myEntryArray[i].word;
}
int getArrayWord_NumbOccur_At(int i)
{
	return myEntryArray[i].number_occurences;
}

void processToken(std::string &token)
{
	strip_unwanted_chars(token);
	if (token != " " && token != "")
	{
		isOrNot = false;
		for (int i = 0; i < nextSlot; i++)
		{
			holdA = token;
			toUpper(holdA);
			holdB = myEntryArray[i].word;
			toUpper(holdB);
			if (myEntryArray[i].word == token || myEntryArray[i].word == holdA || holdA == holdB )
			{
				myEntryArray[i].number_occurences++;
				isOrNot = true;
			}
		}
		holdA = "";
		holdB = "";
		if (isOrNot == false)
		{
			myEntryArray[nextSlot].word = token;
			myEntryArray[nextSlot].number_occurences = 1;
			nextSlot++;
			currentNumberOfEntries++;
		}
	}
}

void extractTokensFromLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;
	while (getline(ss,tempToken,' '))
	{
		processToken(tempToken);
	}
}

void processLine(std::string &myString)
{
	extractTokensFromLine(myString);
}

bool processFile(std::fstream &myfstream)
{
	if (myfstream.is_open() == false)
	{
		return false;
	}
	else
	{
		string line;
		while(myfstream.eof() == false)
		{
			getline(myfstream,line);
			processLine(line);
		}
		return true;
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode)
{
	myfile.open(myFileName);
	if (myfile.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void closeFile(std::fstream& myfile)
{
	if (myfile.is_open())
	{
		myfile.close();
	}
}

int writeArraytoFile(const std::string &outputfilename)
{
	ofstream myOutputfile;
	myOutputfile.open(outputfilename);
	if (currentNumberOfEntries == 0 || nextSlot == 0)
	{
		return FAIL_NO_ARRAY_DATA;
	}
	else if (!myOutputfile.is_open())
	{
		return FAIL_FILE_DID_NOT_OPEN;
	}
	for (int i = 0; i < nextSlot; i++)
	{
		myOutputfile << "" + myEntryArray[i].word + " " + to_string(myEntryArray[i].number_occurences) + "\n";
	}
	myOutputfile.close();
	return SUCCESS;
}

void sAA()
{
	for (int x = 0; x < nextSlot; x++)
	{
		for (int i = 0; i < nextSlot - 1; i++)
		{
			holdA = myEntryArray[i].word;
			toUpper(holdA);
			holdB = myEntryArray[i + 1].word;
			toUpper(holdB);
			if (holdA > holdB)
			{
				entryA = myEntryArray[i];
				entryB = myEntryArray[i + 1];
				myEntryArray[i] = entryB;
				myEntryArray[i + 1] = entryA;
			}
		}
	}

}
void sAD()
{
	for (int x = 0; x < nextSlot; x++)
	{
		for (int i = 0; i < nextSlot - 1; i++)
		{
			holdA = myEntryArray[i].word;
			toUpper(holdA);
			holdB = myEntryArray[i + 1].word;
			toUpper(holdB);
			if (holdA[0] > holdB[0])
			{
				entryA = myEntryArray[i];
				entryB = myEntryArray[i + 1];
				myEntryArray[i] = entryB;
				myEntryArray[i + 1] = entryA;
			}
		}
	}
}
void sANO()
{
	for (int i = 0; i < nextSlot; i++)
	{
		for (int j = 0; j < nextSlot - 1; j++)
		{
			if (myEntryArray[j].number_occurences > myEntryArray[j + 1].number_occurences)
			{
				entryA = myEntryArray[j];
				entryB = myEntryArray[j + 1];
				myEntryArray[j] = entryB;
				myEntryArray[j + 1] = entryA;
			}
		}
	}
}

void sortArray(constants::sortOrder so)
{
	switch(so)
	{
	case NONE: break;
	case ASCENDING: sAA(); break;
	case DESCENDING: sAD(); break;
	case NUMBER_OCCURRENCES: sANO(); break;
	}
}
