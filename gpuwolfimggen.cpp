#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <stdio.h>
#include <string.h>

using namespace cv;
using namespace std;

const int MAX_NUMBER_OF_NFT_ELEMENTS = 7;
const double alpha = 1;

string sourceBackground = "./Source/Background/BACK4.png";
string sourceBody = "./Source/girl/body/GIRL.png";
string sourceEyes = "./Source/girl/eyes/EYES1.png";
string sourceHair = "./Source/girl/hair/HAIR2.png";
string sourceDress = "./Source/girl/clothing/empty.png";
string sourceExtra = "./Source/girl/extra/ROSE.png";
string sourceCorner = "./Source/Corner/CORNER1.png";

string imagesForTesting[] = {sourceBackground, sourceBody, sourceEyes, sourceHair, sourceDress, sourceExtra, sourceCorner};

Mat getAlphaChannelOf(Mat& input) {
	Mat alphaChannel(input.rows, input.cols, CV_8UC1);

	cuda::GpuMat tempImage;
	vector<cuda::GpuMat> channels;

	tempImage.upload(input);
	cuda::split(tempImage, channels);
	channels[3].download(alphaChannel);

	tempImage.release();

	return alphaChannel;
}

void showAlphaChannelOf(Mat& input) {
	imwrite("./NFTs/alpha.png", getAlphaChannelOf(input)); // file is being saved
}

void addAlphaChannelTo(Mat& input, int opacity) {
	cuda::GpuMat alphaMask(input.rows, input.cols, CV_8UC1, Scalar(opacity)); //8bit 1 channel alpha mask, should add white

	// alpha-channel for transperancy using GPU
	cuda::GpuMat tempImg; //, tempMask;
	cuda::GpuMat tempImageWithAlpha(input.rows, input.cols, input.type());
    vector<cuda::GpuMat> channels;

	if ( input.channels() == 3) {
		tempImg.upload(input);
		//tempMask.upload(mask);
					
		// break image into channels
		cuda::split(tempImg, channels); 

		// append alpha channel
		if (channels.size() == 3) { channels.push_back(alphaMask); };

		// combine channels
		cuda::merge(channels, tempImageWithAlpha); 
		tempImageWithAlpha.download(input); // download from GPU memory

		//cout << "Alpha Channel added: " << (input.channels() == 4) << endl;
	}

	tempImg.release();
	tempImageWithAlpha.release(); // deallocate memory
}

Mat overlayImagesUsingCUDA(Mat imageArray[], int imageArraySize) { 
	// images must have same size
	Mat result;

	// initialize image in GPU
	cuda::GpuMat gpuresult(imageArray[0].rows, imageArray[0].cols, CV_8UC4);

	for (int iter = 0; iter < imageArraySize; iter++) {
		if (imageArray[iter].channels() == 1) {
			cout << "empty image detected: " << imagesForTesting[iter] << endl;
			break;
		}

		switch (iter) {
		case 0: // 0 must be some sort of background image
			addAlphaChannelTo(imageArray[iter], 255); // executed only if 3 channels in the image
			gpuresult.upload(imageArray[iter]);
			break;
		default:
			// overlay two images in GPU -> must have alpha channel as well
			cuda::add(gpuresult, imageArray[iter], gpuresult);
			break;
		}
	}

	// download image from GPU memory
	gpuresult.download(result);

	return result;
}

void CUDAmergeNewAlphaChannelTo(cuda::GpuMat& singleChannelAlpha, cuda::GpuMat& image) {
	vector<cuda::GpuMat> vec4b;
	cuda::split(image, vec4b);
	vec4b[3] = singleChannelAlpha.cuda::GpuMat::clone();
	cuda::merge(vec4b, image);
}

Mat addBackgroundToImage(Mat imageArray[]) { 
	// images must have same size
	Mat result;

	// initialize image in GPU
	cuda::GpuMat gpuresult(imageArray[0].rows, imageArray[0].cols, CV_8UC4);
	cuda::GpuMat backAlphaGPU(imageArray[0].rows, imageArray[0].cols, CV_8UC1);
	cuda::GpuMat characterImage(imageArray[1].rows, imageArray[1].cols, CV_8UC4);

	for (int iter = 0; iter < 2; iter++) 
	{
		if (imageArray[iter].channels() == 1) {
			cout << "empty image detected: " << imagesForTesting[iter] << endl;
			break;
		}

		switch (iter) {
		case 0: // 0 must be some sort of background image
			addAlphaChannelTo(imageArray[iter], 255); // executed only if 3 channels in the image
			gpuresult.upload(imageArray[iter]);
			break;
		default:
			// 1. get proper alpha channel for background image
			vector<cuda::GpuMat> vec4b;
			backAlphaGPU.upload(getAlphaChannelOf(imageArray[0]));
			cuda::bitwise_not(backAlphaGPU, backAlphaGPU, getAlphaChannelOf(imageArray[iter]));
			cuda::split(gpuresult, vec4b);
			vec4b[3] = backAlphaGPU.cuda::GpuMat::clone();
			cuda::merge(vec4b, gpuresult);

			// 2. merge main picture to the background
			characterImage.upload(imageArray[iter]);
			backAlphaGPU = cuda::GpuMat(imageArray[iter].rows, imageArray[iter].cols, CV_8UC1, Scalar(255));
			break;
		}
	}

	// download image from GPU memory
	gpuresult.download(result);

	imwrite("./NFTs/test_alpha.png", getAlphaChannelOf(result));

	return result;
}

void addTextToImage() {
	
}

/*
	build: g++ cuda_image_gen.cpp -o testcuda -g `pkg-config --libs --cflags opencv4`
*/

int main(int argc, char *argv[]) {
	Mat characterImageArray[MAX_NUMBER_OF_NFT_ELEMENTS-1];
	Mat fullImageArray[2];

	Mat completeImage;

	// get character image working
	for (int i = 0; i < MAX_NUMBER_OF_NFT_ELEMENTS-1; i++) {
		characterImageArray[i] = imread(imagesForTesting[i+1], IMREAD_UNCHANGED);
	}

	completeImage = overlayImagesUsingCUDA(characterImageArray, sizeof(characterImageArray)/sizeof(Mat));	

	showAlphaChannelOf(completeImage);

	// get full image
	fullImageArray[0] = imread(imagesForTesting[0], IMREAD_UNCHANGED);
	fullImageArray[1] = completeImage.clone();

	completeImage = addBackgroundToImage(fullImageArray);	

	imwrite("./NFTs/test.png", completeImage); // file is being saved

	cout << "done" << endl;

    return 0;
}