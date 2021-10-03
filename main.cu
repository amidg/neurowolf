#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "wolf.h"
#include "wolf.cpp"
#include <locale>
#include <cuda.h>

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

//CUDA related code
cudaDeviceProp deviceProp;
void CUDAdeviceInfo();

//wolf
Wolf newWolf = Wolf();

/*
	CUDA CODE IS EXECUTED USING THE FOLLOWING -> check NVIDIA documentation for this
	function<<<grid,block>>>(param1,param2,...); 
*/

int main() {
	//initializing code
    setlocale(LC_CTYPE,"Russian"); //russian language
	srand(time(NULL)); //initialize random seed

    //debug or temp code
    CUDAdeviceInfo();
	int i = 1;

    //loop code
	while(i < 10) {
		i++;
		newWolf.buildSimpleWisdomStructure(newWolf.getStringContentFromFile(phrase1source), 
										   newWolf.getStringContentFromFile(phrase2source) );

		cout << newWolf.getWisdom() << endl;
	}
	
	return 0;
}

//functions descriptions
void CUDAdeviceInfo() {
    printf("Wolf Wisdom Generator v10.2021.0\n");
    printf("Powered by NVIDIA CUDA 10.0 using:\n");

	cudaGetDeviceProperties(&deviceProp, 0);

	printf("Device name:                %s\n", deviceProp.name); 
	printf("Major revision number:      %d\n", deviceProp.major);
    printf("Minor revision Number:      %d\n", deviceProp.minor); 
    printf("Total Global Memory:        %d\n", deviceProp.totalGlobalMem);
    printf("Total shared mem per block: %d\n", deviceProp.sharedMemPerBlock); 
    printf("Total const mem size:       %d\n", deviceProp.totalConstMem); 
    printf("Warp size:                  %d\n", deviceProp.warpSize); 
    printf("Maximum block dimensions:   %d x %d x %d\n", deviceProp.maxThreadsDim[0], \ 
														 deviceProp.maxThreadsDim[1], \
                                                         deviceProp.maxThreadsDim[2]); 

    printf("Maximum grid dimensions:    %d x %d x %d\n", deviceProp.maxGridSize[0], \
                                                         deviceProp.maxGridSize[1], \
                                                         deviceProp.maxGridSize[2]); 

    printf("Clock Rate:                 %d\n", deviceProp.clockRate); 
    printf("Number of muliprocessors:   %d\n", deviceProp.multiProcessorCount); 
}
