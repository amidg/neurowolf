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

	fileHandler.open(phrasePath);

	//check file open status
	if (!fileHandler) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    } else if (fileHandler.is_open()) {
        // Keep reading the file
        while(getline(fileHandler, phrase))
        {
            // print the line on the standard output
            cout << phrase << endl;
        }
	}


    // File Close
    fileHandler.close();

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