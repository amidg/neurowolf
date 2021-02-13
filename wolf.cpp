#include<iostream>
#include "wolf.h"
#include <cstdlib>
#define cimg_display 0
#include "CImg.h"
using namespace std;
using namespace cimg_library;

//constructors
Wolf::Wolf() {
	wolfwisdom = "Волк слабее льва, но в цирке не выступает";
}

Wolf::Wolf(string wisdom) {
	wolfwisdom = wisdom;
}

string Wolf::getWisdom() {
    return wolfwisdom;
}

//read phrase from keyboard for manually specified wolf wisdom
string Wolf::readWisdomFromKeyboard() {

}

//read phrase templates from source files
string Wolf::readPhrase1(string filepath) {


	
}

string Wolf::readPhrase2(string filepath) {


	
}

string Wolf::readNoun(string filepath) {


	
}

string Wolf::readVerb(string filepath) {


	
}

//generate wisdom phrase
string Wolf::generateWisdom(string phrase1, string noun1, string noun2, string noun3, string phrase2, string verb1, string verb2) {


	
}

//generate picture
void Wolf::generateWisdomMeme(string wisdom) {
    
	
}