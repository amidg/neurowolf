#include <iostream>
#include <string>
using namespace std;

#ifndef WOLF_H
#define WOLF_H

class Wolf {
public:
	Wolf();
	Wolf(string wisdom);
    string readWisdomFromKeyboard();
    string readPhrase1(string filepath);
    string readPhrase2(string filepath);
    string readNoun(string filepath);
    string readVerb(string filepath);
    string generateWisdom(string phrase1, string noun1, string noun2, string noun3, string phrase2, string verb1, string verb2);
	void generateWisdomMeme(string wisdom);

    string getWisdom();

private:
	string wolfwisdom;
};

#endif