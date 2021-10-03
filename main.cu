#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "wolf.h"
#include "wolf.cpp"
#include <locale>

using namespace std;

/*
	GOAL:
	- design code to generate wolf wisdom using C++ and CUDA
	- C++ is used to generate text
	- CUDA is used to generate image/video content, can be used for text as well (not sure if needed)

*/

//sources for images, text files etc
string whereToFindSourceImages = "./ImgSource/";
string phrase1source = "./Source/Phrase1.txt";
string phrase2source = "./Source/Phrase2.txt";
string nounSource = "./Source/Noun.txt";
string verbSource = "./Source/Verb.txt";

//function declarations
__global__ void cuda_hello();

//wolf
Wolf newWolf = Wolf();

/*
	CUDA CODE IS EXECUTED USING THE FOLLOWING -> check NVIDIA documentation for this
	function<<<grid,block>>>(param1,param2,...); 
*/

int main() {
	//initializing code
    setlocale(LC_CTYPE,"Russian"); //russian language
	srand (time(NULL)); //initialize random seed

    //debug or temp code
    cuda_hello<<<1,1>>>();
    std::cout << newWolf.getPhrase("Phrase1.txt");


    //loop code
	
	
	return 0;
}

//functions descriptions
__global__ void cuda_hello() {
    printf("Wolf Wisdom Generator v10.2021.0\n");
    printf("Powered by NVIDIA CUDA 10.0 using NVIDIA QUADRO K5000\n");
}
