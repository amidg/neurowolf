#include "wolf.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <locale>
#include <fstream> //needed to read text from file
#include <cstdlib>

using namespace std;

//constructors
Wolf::Wolf() {
	setlocale(LC_CTYPE,"Russian"); //russian language
	srand(time(NULL)); //initialize random seed
	wolfwisdom = "Волк слабее льва, но в цирке не выступает\n";
}

//getter & setter
string Wolf::getWisdom() {
    return wolfwisdom;
}

string Wolf::getPhrase1() {
    return wisdomPhrase1;
}

string Wolf::getPhrase2() {
    return wisdomPhrase2;
}

void Wolf::setWisdom(string wisdom) {
	wolfwisdom = wisdom;
}

void Wolf::setPhrase1(string phrase1) {
	wisdomPhrase1 = phrase1;
}

void Wolf::setPhrase2(string phrase2) {
	wisdomPhrase2 = phrase2;
}

string Wolf::getLogPath() {
    return fileToPlaceWisdomTo;
}

//functions to get wisdom useful information
string Wolf::getStringContentFromFile(string path) {
	//this function takes random string from the txt file with predefined words
	string phrase = "";
	int numberOfLines = 0;
	int i = 1;

	fileHandler.open(path);

	//check file open status
	if (!fileHandler) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    } else if (fileHandler.is_open()) {
        // Keep reading the file to calculate how many lines we have
        while(getline(fileHandler, phrase))
        {
            numberOfLines++;
            //cout << phrase << endl; // print the line on the standard output
			//cout << numberOfLines << endl;
        }
		fileHandler.close();
	}

	fileHandler.open(path);

	//get one of the random lines
	int randLine = rand() % numberOfLines; //from 1 to numberOfLines
	while (fileHandler.is_open() && i < randLine) {
		getline(fileHandler, phrase);
		i++;

		if (phrase == "") {
			i--; //if phrase is empty we redo the cycle
		}
	}

    // File Close
    fileHandler.close();

	//cout << phrase << endl; // print the line on the standard output

	return phrase;
}

void Wolf::assignPhrasesToWisdomStructure(string phrase1, string phrase2) {
	wisdomPhrase1 = phrase1;
	wisdomPhrase2 = phrase2;
}

void Wolf::buildSimpleWisdomStructure() {
	wolfwisdom = wisdomPhrase1 + " " + wisdomPhrase2;
}

void Wolf::insertWordIntoString(string input, string lookfor, string nounPath, string verbPath) {
	// this function replaces placeholders in the input string with actual words
	std::size_t position = 0;

	while ( input.find(lookfor) < 500 ) {
		position = input.find(lookfor);
		
		input.erase(input.begin() + position);

		input.insert(position, getStringContentFromFile(nounPath));
	}
}

void Wolf::completeWisdomWithWords(string nounPath, string verbPath) {
	/* insert word into the existing wisdom based on markers
		n -> noun 
		v -> verb
		vpresent -> present tense verb
		vpast -> past tense verb
		a -> adjective
		av -> adverb
	*/

	//search for noun
	insertWordIntoString(wisdomPhrase1, "n", nounPath, verbPath);

	// search for verb
	insertWordIntoString(wisdomPhrase1, "v", nounPath, verbPath);

	buildSimpleWisdomStructure();
}

void Wolf::placeWisdomToFile(string wisdom) {
	file_out.open(fileToPlaceWisdomTo, std::ios_base::app); //with append we will write to the end of the text file

	file_out << wolfwisdom << endl;
}

int Wolf::recordLatestMemeIndex(string path) {
	string phrase = "";
	int numberOfLines = 0;
	int i = 1;

	fileHandler.open(path);

	//check file open status
	if (!fileHandler) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    } else if (fileHandler.is_open()) {
        // Keep reading the file to calculate how many lines we have
        while(getline(fileHandler, phrase))
        {
            numberOfLines++;
        }
		fileHandler.close();
	}

	return numberOfLines;
}