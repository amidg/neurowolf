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
    string getStringContentFromFile(string path);

    //functions to build wisdom
    void buildSimpleWisdomStructure(string phrase1, string phrase2);
    void insertWordIntoWisdom(string nounPath, string verbPath);

    //useful variable
    ifstream fileHandler; //txt file handler for C++

private:
	string wolfwisdom;
};

#endif