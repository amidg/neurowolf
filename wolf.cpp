#include "wolf.hpp"
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

void Wolf::setWisdom(string wisdom) {
	wolfwisdom = wisdom;
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

void Wolf::buildSimpleWisdomStructure(string phrase1, string phrase2) {
	string wisdomStructure = "";

	wisdomStructure = phrase1 + " " + phrase2;
	wolfwisdom = wisdomStructure;
}

void Wolf::insertWordIntoWisdom(string nounPath, string verbPath) {
	/* insert word into the existing wisdom based on markers
		n -> noun 
		v -> verb
		a -> adjective
		av -> adverb
	*/

	std::size_t position = 0;

	//search for noun
	while (wolfwisdom.find('n') < 500) {
		position = wolfwisdom.find('n');
		
		wolfwisdom.erase(wolfwisdom.begin() + position);

		wolfwisdom.insert(position, getStringContentFromFile(nounPath));
	}

	//search for verb
	while (wolfwisdom.find('v') < 500) {
		position = wolfwisdom.find('v');
		
		wolfwisdom.erase(wolfwisdom.begin() + position);

		wolfwisdom.insert(position, getStringContentFromFile(verbPath));
	}
}
