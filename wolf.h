#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <locale> //needed to read russian language
#include <fstream> //needed to read text from file

using namespace std;

#ifndef WOLF_H
#define WOLF_H

class Wolf {
public:
	Wolf(); //default constructor

    //getter and setter for default wolf
    string getWisdom();
    void setWisdom(string wisdom);

    //functions to get wisdom useful information
    string getPhrase(string phrasePath);
    string getNoun(string nounPath);
    string getAdj(string adjPath);
    string getVerb(string verbPath);

    //functions to build wisdom
    


private:
	string wolfwisdom;
};

#endif