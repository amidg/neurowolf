#include<iostream>
#include "wolf.h"
#include <cstdlib>
#include <unistd.h>
#include <locale> //needed to read russian language
#include <fstream> //needed to read text from file

using namespace std;

//constructors
Wolf::Wolf() {
	wolfwisdom = "Волк слабее льва, но в цирке не выступает\n";
}

//getter & setter
string Wolf::getWisdom() {
    return wolfwisdom;
}

void Wolf::setWisdom(string wisdom) {
	wolfwisdom = wisdom;
}

//functions to get wisdom useful information
string Wolf::getPhrase(string phrasePath) {
	string phrase = "";
	int numberOfLines = 0;

	fileHandler.open(phrasePath);

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

	fileHandler.open(phrasePath);

	//get one of the random lines
	int randLine = rand() % numberOfLines; //from 1 to numberOfLines
	for (int i = 1; i < randLine; i++) {
		getline(fileHandler, phrase);
		// cout << phrase << endl; // print the line on the standard output
	}

    // File Close
    fileHandler.close();

	cout << phrase << endl; // print the line on the standard output

	return phrase;
}

string Wolf::getNoun(string nounPath) {
	string noun = "";


	return noun;
}

string Wolf::getAdj(string adjPath) {
	string adj = "";


	return adj;
}

string Wolf::getVerb(string verbPath) {
	string verb = "";

	return verb;
}