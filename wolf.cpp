#include<iostream>
#include "wolf.h"
#include <cstdlib>
#include <unistd.h>

using namespace std;

//constructors
Wolf::Wolf() {
	wolfwisdom = "Волк слабее льва, но в цирке не выступает\n";
}

//getter & setter
string Wolf::getWisdom() {
    return wolfwisdom;
}

void Wolf::setWisdom(string wisdom) {
	wolfwisdom = wisdom;
}

//wisdom generation functions