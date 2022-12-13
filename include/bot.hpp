#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <locale>
#include <fstream> //needed to read text from file
#include <cstdlib>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

#ifndef WOLFBOT_HPP
#define WOLFBOT_HPP

class WolfBot {
public:
	WolfBot(const string& token); //default constructor

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
    Bot wolf_bot;
    string message_id; // message that triggered bot
    string current_wisdom; // wolf quote
    string path_to_image_file;
};

#endif