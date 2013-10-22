#include <vector>
#include <opencv2/opencv.hpp>
#include "colorkeying.h"
#include "cross.h"
using namespace cv;
using namespace std;



const int crossLength = 30;
const Scalar colorGreen(0, 255, 0);
const int threshSaturation = 120;
const int lowerHue = 340 / 2;
const int upperHue = 360 / 2;

const Vec3b REFERENCE_COLOR(51, 42, 91);	// BGR


void colorKeyingRGB(const string&videoPath){
	// Video laden
	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	namedWindow("Video");

	namedWindow("Maske");
	createTrackbar("Threshold", "Maske", 0, 255);
	setTrackbarPos("Threshold", "Maske", 20);

	Mat mask(height, width, CV_8UC1);

	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}

		// Schwellen holen
		int threshold = getTrackbarPos("Threshold", "Maske");

		// Pixel analysieren
		int sumx = 0;
		int sumy = 0;
		int countWhites = 0;
		for(int x = 0; x < videoFrame.cols; x++){
			for(int y = 0; y < videoFrame.rows; y++){
				Vec3b pixel = videoFrame.at<Vec3b>(y,x);
				double distance = norm(REFERENCE_COLOR, pixel);

				// Maskierung und Schwerpunktsberechnung
				if (distance < threshold){
					mask.at<uchar>(y,x) = 255;
					sumx += x;
					sumy += y;
					countWhites++;
				}
				else{
					mask.at<uchar>(y,x) = 0;
				}
			}
		}
	
		// Schwerpunkt berechnen
		if (countWhites > 0){
			Point center(sumx/countWhites, sumy/countWhites);
			cross(videoFrame, center, crossLength, colorGreen);
		}
		
		imshow("Maske", mask);
		imshow("Video", videoFrame);
		waitKey(100);
	}
}



void colorKeyingHSV(const string&videoPath){
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

	Mat hueFrame(height, width, CV_8UC1);
	Mat saturationFrame(height, width, CV_8UC1);
	Mat mask(height, width, CV_8UC1);

	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}

		// in Graustufen wandeln
		Mat hsvFrame;
		cvtColor(videoFrame, hsvFrame, CV_BGR2HSV);	

		// Schwellen holen
		int threshSaturation = getTrackbarPos("Select", "Saturation");
		int lowerThreshHue = getTrackbarPos("Lower", "Hue");
		int upperThreshHue = getTrackbarPos("Upper", "Hue");

		// Pixel analysieren
		int sumx = 0;
		int sumy = 0;
		int countWhites = 0;
		for(int x = 0; x < videoFrame.cols; x++){
			for(int y = 0; y < videoFrame.rows; y++){
				Vec3b hsvPixel = hsvFrame.at<Vec3b>(y,x);
				int hue = hsvPixel[0];
				int saturation = hsvPixel[1];

				// Maskierung und Schwerpunktsberechnung
				if (saturation > threshSaturation && hue > lowerThreshHue && hue < upperThreshHue){
					mask.at<uchar>(y,x) = 255;
					sumx += x;
					sumy += y;
					countWhites++;
				}
				else{
					mask.at<uchar>(y,x) = 0;
				}

				// die folgenden Schritte sind eigentlich nicht nötig, sie dienen der Veranschaulichung
				if (hue > lowerThreshHue && hue < upperThreshHue){
					hueFrame.at<uchar>(y,x) = 255;
				}
				else{
					hueFrame.at<uchar>(y,x) = 0;
				}
				if (saturation > threshSaturation){
					saturationFrame.at<uchar>(y,x) = 255;
				}
				else{
					saturationFrame.at<uchar>(y,x) = 0;
				}
			}
		}
	
		// Schwerpunkt berechnen
		if (countWhites > 0){
			Point center(sumx/countWhites, sumy/countWhites);
			cross(videoFrame, center, crossLength, colorGreen);
		}
		
		imshow("Hue", hueFrame);
		imshow("Saturation", saturationFrame);
		imshow("Maske", mask);
		imshow("Video", videoFrame);
		waitKey(100);
	}
}
