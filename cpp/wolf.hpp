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
    string getPhrase1();
    string getPhrase2();

    void setWisdom(string wisdom);
    void setPhrase1(string phrase1);
    void setPhrase2(string phrase2);

    string getLogPath();

    //functions to get wisdom useful information
    string getStringContentFromFile(string path);

    //functions to build wisdom
    void assignPhrasesToWisdomStructure(string phrase1, string phrase2);
    void buildSimpleWisdomStructure(string phrase1, string phrase2);
    string insertWordIntoString(string input, char lookfor, string nounPath, string verbPath);
    void completeWisdomWithWords(string nounPath, string verbPath);
    void placeWisdomToFile(string wisdom);

    int recordLatestMemeIndex(string path);

    //useful variable
    ifstream fileHandler; //txt file handler for C++
    ofstream file_out;

private:
	string wolfwisdom;
    string wisdomPhrase1;
    string wisdomPhrase2;
    string fileToPlaceWisdomTo = "./wisdomLog.txt";
};

#endif