#include "wolf.h"
#include "wolf.cpp"
#include "wolfimggen.h"
#include <cstring>

using namespace std;

//sources for images, text files etc
string whereToFindSourceImages = "./ImgSource/";
string phrase1source = "./Source/Phrase1.txt";
string phrase2source = "./Source/Phrase2.txt";
string nounSource = "./Source/Noun.txt";
string verbSource = "./Source/Verb.txt";

//wolf
Wolf newWolf = Wolf();

int wolfwisdomlen = 0;

int imageNum = 0;

/*
	CUDA CODE IS EXECUTED USING THE FOLLOWING -> check NVIDIA documentation for this
	function<<<grid,block>>>(param1,param2,...); 
*/

int main() {

	newWolf.buildSimpleWisdomStructure(newWolf.getStringContentFromFile(phrase1source), 
									   newWolf.getStringContentFromFile(phrase2source) );

	newWolf.insertWordIntoWisdom(nounSource, verbSource);

	newWolf.placeWisdomToFile(newWolf.getWisdom());

	wolfwisdomlen = newWolf.getWisdom().length();
	char stringToBePassed[wolfwisdomlen + 1];

	strcpy(stringToBePassed, newWolf.getWisdom().c_str());

	generateCompleteWolfImage(stringToBePassed, imageNum);
	
	return 0;
}