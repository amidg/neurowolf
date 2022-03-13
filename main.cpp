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
int phrase1len = 0;
int phrase2len = 0;

string ImageIdFromLog = "";

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

	/*
		argc -> sets number of arguments
		argv -> strings provided in the command line e.g. if ((argc >= 2 ) && ( strcmp(argv[1], "-a") == 0))

		executable example would be:
		./wolfwisdomgenerator imageID twophrases
	*/

	// cout << "arguments provided " + to_string(argc - 1) << endl; // debug only

	switch (argc) {
		case 1:
			cout << "please provide image ID" << endl;
			break;
		case 2: // imageId only provided
			if ( argv[1] != "" && argv[1] != "\n") {
				newWolf.assignPhrasesToWisdomStructure( newWolf.getStringContentFromFile(phrase1source), 
									   					newWolf.getStringContentFromFile(phrase2source) );

				newWolf.completeWisdomWithWords(nounSource, verbSource);

				newWolf.buildSimpleWisdomStructure(newWolf.getPhrase1(), newWolf.getPhrase2());

				newWolf.placeWisdomToFile(newWolf.getWisdom());

				wolfwisdomlen = newWolf.getWisdom().length();
				char stringToBePassed[wolfwisdomlen + 1];

				ImageIdFromLog = to_string(newWolf.recordLatestMemeIndex(newWolf.getLogPath()));
				char imageId[ImageIdFromLog.length() + 1];

				strcpy(stringToBePassed, newWolf.getWisdom().c_str());
				strcpy(imageId, ImageIdFromLog.c_str());
				generateCompleteWolfImage( stringToBePassed, argv[1] );
			} 
			break;
		case 3: // command provided for number of phrases
			if ( argv[2] == "twophrases" ) {
				newWolf.assignPhrasesToWisdomStructure( newWolf.getStringContentFromFile(phrase1source), 
									   					newWolf.getStringContentFromFile(phrase2source) );

				newWolf.completeWisdomWithWords(nounSource, verbSource);

				newWolf.buildSimpleWisdomStructure(newWolf.getPhrase1(), newWolf.getPhrase2());
				
				newWolf.placeWisdomToFile(newWolf.getWisdom());

				phrase1len = newWolf.getPhrase1().length();
				phrase2len = newWolf.getPhrase2().length();
				char phrase1topass[phrase1len + 1];
				char phrase2topass[phrase2len + 1];

				ImageIdFromLog = to_string(newWolf.recordLatestMemeIndex(newWolf.getLogPath()));
				char imageId[ImageIdFromLog.length() + 1];

				strcpy(phrase1topass, newWolf.getPhrase1().c_str());
				strcpy(phrase2topass, newWolf.getPhrase2().c_str());
				strcpy(imageId, ImageIdFromLog.c_str());

				generateCompleteWolfImageFromTwoPhrases( phrase1topass, phrase2topass, argv[1]);
			} else {
				cout << "incorrect argument, use twophrases" << endl;
			}
			break;			
	}
	
	return 0;
}