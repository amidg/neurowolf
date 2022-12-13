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
	WolfBot(); //default constructor

    // telegram bot API
    void run();

    // get/set
    string get_msg_id();
    string get_wisdom();
    string get_file_path();

    //useful variable
    ifstream fileHandler; //txt file handler for C++
    ofstream file_out;

private:
    Bot wolf_bot;
    string bot_token;   // bot token, passed as env variable
    string message_id; // message that triggered bot
    string current_wisdom; // wolf quote
    string path_to_image_file;
};

#endif