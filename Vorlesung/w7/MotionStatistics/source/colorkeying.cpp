#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "centroid.h"
#include "cross.h"
#include "HandMotion.h"
#include "MotionVelocity.h"
using namespace cv;
using namespace std;

const string videoPath = "C:/Users/Andreas/Desktop/micro-dance.wmv";
//const string videoPath = "d:/student/micro-dance.wmv";
//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";

const int crossLength = 30;
const Scalar colorGreen(0, 255, 0);
const int threshSaturation = 120;
const int lowerHue = 340 / 2;
const int upperHue = 360 / 2;



void colorKeying(){
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

	Mat hsvImage(height, width, CV_8UC3);
	HandMotion handMotion;
	MotionVelocity handVelocity;
	Point lastCentroid;
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
		
		// Schwellwertbildung Saturation
		threshold(hsvPlanes[1], hsvPlanes[1], getTrackbarPos("Select", "Saturation"), 255, THRESH_BINARY);
		imshow("Saturation", hsvPlanes[1]);

		// Schwellwertbildung Hue
		inRange(hsvPlanes[0], getTrackbarPos("Lower", "Hue"), 
				getTrackbarPos("Upper", "Hue"), hsvPlanes[0]);
		imshow("Hue", hsvPlanes[0]);

		// Kombination der beiden Masken
		multiply(hsvPlanes[0], hsvPlanes[1], hsvPlanes[0]);
		
		// Median Filter
		medianBlur(hsvPlanes[0], hsvPlanes[0], 5);

		// Konturen finden
		imshow("Maske", hsvPlanes[0]);
	
		// Schwerpunkt berechnen
		Point center = centroidOfWhitePixels(hsvPlanes[0]);
		cross(videoFrame, center, crossLength, colorGreen);

		// Geschwindigkeit anzeigen
		handVelocity.setPosition(center);
		Point velocity = handVelocity.getVelocity();
//		Point velocity = handMotion.calculateVelocity(center);
//		Point velocity = center - lastCentroid;
//		lastCentroid = center;
		// Vektor anzeigen
		line(videoFrame, center, center+velocity*2, Scalar(255,0,0), 3);


		imshow("Video", videoFrame);
		waitKey(100);
	}
}

void main(){
	colorKeying();
}