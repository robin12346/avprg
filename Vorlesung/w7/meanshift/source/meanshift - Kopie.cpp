#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "centroid.h"
#include "cross.h"


using namespace cv;
using namespace std;


const int crossLength = 30;
const Scalar colorGreen(0, 255, 0);
const int threshSaturation = 120;
const int lowerHue = 340 / 2;
const int upperHue = 360 / 2;

MatND calcHueHistogram(Mat& image, int minSaturation){
	Mat hsvImage;
	cvtColor(image, hsvImage, CV_BGR2HSV);

	// create mask: saturation > minSaturation
	Mat mask;
	std::vector<Mat> planes;
	split(hsvImage, planes);
	threshold(planes[1], mask, minSaturation, 255, THRESH_BINARY);

	// calculate histogram
	MatND hist;
	const float hranges[] = {0.0, 180.0};	
//	 float hranges[2];
//	 hranges[0] = 0.0;
//	 hranges[1] = 180.0;
	 const float* ranges[1];
	 ranges[0] = hranges;
	 int channels[] = {0};			// index of hue channel
	 int histSize[] = {64};			// number of bins
//	const float hranges[] = {0.0, 180.0};	
//	const int channels[] = {0};			// index of hue channel
//	const int histSize[] = {64};			// number of bins
	calcHist(&hsvImage,				// array of Mat objects
		1,							// histogram of 1 image
		channels,					// array of indices used
		mask,						// binary mask (from saturation)
		hist,						// resulting histogram
		1,							// one dimensional histogram
		histSize,					// number of bins
		ranges						// pixel value range
	);
	return hist;
}


void colorKeying(const string& videoPath, const string& referenceImagePath){
	// Video laden
	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);


	namedWindow("Video");
	namedWindow("Hue");
	createTrackbar("Lower", "Hue", 0, 180);
	setTrackbarPos("Lower", "Hue", lowerHue);
	createTrackbar("Upper", "Hue", 0, 180);
	setTrackbarPos("Upper", "Hue", upperHue);

	namedWindow("Saturation");
	createTrackbar("Select", "Saturation", 0, 255);
	setTrackbarPos("Select", "Saturation", threshSaturation);
	namedWindow("Maske");
	namedWindow("backprojection");
	Mat hsvImage(height, width, CV_8UC3);


	// calculate histogram of reference image
	Mat referenceImage = imread(referenceImagePath);
	MatND histogram = calcHueHistogram(referenceImage, 65);



	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}

		// in HSV wandeln
		cvtColor(videoFrame, hsvImage, CV_BGR2HSV);	
		vector<Mat> hsvPlanes;
		split(hsvImage, hsvPlanes);
		
		// calculate back projection
		const float hranges[] = {0.0, 180.0};	
		const float* ranges[1];
		ranges[0] = hranges;
		int channels[] = {0};			// index of hue channel
		int histSize[] = {64};	
		Mat backprojection;
		calcBackProject(&hsvPlanes[0], 1, channels,histogram, backprojection, ranges);

		imshow("backprojection", backprojection);
/*
		// Schwellwertbildung Saturation
		threshold(hsvPlanes[1], hsvPlanes[1], getTrackbarPos("Select", "Saturation"), 255, THRESH_BINARY);
		imshow("Saturation", hsvPlanes[1]);

		// Schwellwertbildung Hue
		inRange(hsvPlanes[0], getTrackbarPos("Lower", "Hue"), 
				getTrackbarPos("Upper", "Hue"), hsvPlanes[0]);
		imshow("Hue", hsvPlanes[0]);

		// Kombination der beiden Masken
		multiply(hsvPlanes[0], hsvPlanes[1], hsvPlanes[0]);
		imshow("Maske", hsvPlanes[0]);
	
		// Schwerpunkt berechnen
		Point center = centroidOfWhitePixels(hsvPlanes[0]);
		cross(videoFrame, center, crossLength, colorGreen);
*/

		imshow("Video", videoFrame);
		waitKey(30);
	}
}

void main(){
	const string video = "C:/Users/Andreas/Desktop/micro-dance.wmv";
//const string videoPath = "d:/student/micro-dance.wmv";
//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	const string referenceImage = "C:/Users/Andreas/Desktop/rotehand.bmp";

	colorKeying(video, referenceImage);
}