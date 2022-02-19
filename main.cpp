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

/*
	CUDA CODE IS EXECUTED USING THE FOLLOWING -> check NVIDIA documentation for this
	function<<<grid,block>>>(param1,param2,...); 
*/

/*
		1. Build Go-lang library for Wolf:
			go build -buildmode=c-archive wolfimggen.go

			NOTE: must indicate necessary functions with //export <function name>

		2. Build C++ main wolf program using the following:
			g++ -pthread main.cpp wolfimggen.a -o wolfwisdomgenerator
	*/

int main(int argc, char *argv[]) {

	newWolf.buildSimpleWisdomStructure(newWolf.getStringContentFromFile(phrase1source), 
									   newWolf.getStringContentFromFile(phrase2source) );

	newWolf.insertWordIntoWisdom(nounSource, verbSource);

	newWolf.placeWisdomToFile(newWolf.getWisdom());

	wolfwisdomlen = newWolf.getWisdom().length();
	char stringToBePassed[wolfwisdomlen + 1];

	strcpy(stringToBePassed, newWolf.getWisdom().c_str());

	generateCompleteWolfImage( stringToBePassed, int(argv[1]) ); // generate image index based on command line input
	//generateCompleteWolfImage(stringToBePassed, newWolf.recordLatestMemeIndex(newWolf.getLogPath())); //use last number
	
	return 0;
}