#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <locale>
#include <fstream> //needed to read text from file
#include <cstdlib>

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
    string getStringContentFromFile(string path);

    //functions to build wisdom
    void buildSimpleWisdomStructure(string phrase1, string phrase2);
    void insertWordIntoWisdom(string nounPath, string verbPath);
    void placeWisdomToFile(string wisdom);

    void recordLatestMemeIndex(int index);

    //useful variable
    ifstream fileHandler; //txt file handler for C++
    ofstream file_out;

private:
	string wolfwisdom;
    string fileToPlaceWisdomTo = "./wisdomLog.txt";
};

#endif