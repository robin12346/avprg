#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;



void backgroundSubtraction(const string& videoPath, const string& imagePath){
	// Video laden
	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Hintergrundbild laden
	Mat image = imread(imagePath);
	Mat hintergrundBild;
	Size videoSize(width, height);
	resize(image, hintergrundBild, videoSize, 0,0);


	namedWindow("Video");
	namedWindow("Maske");
	createTrackbar("Toleranz", "Maske", 0, 50);
	namedWindow("Tänzer vor Wüste");

	Mat firstFrame;
	Mat videoFrameGrau(height, width, CV_8UC1);
	Mat vorBild(height, width, CV_8UC3);

	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}

		// in Graustufen wandeln
		cvtColor(videoFrame, videoFrameGrau, CV_BGR2GRAY);		

		// erstes Frame merken
		frameNumber++;
		if(frameNumber == 1){
			videoFrameGrau.copyTo(firstFrame);
		}

		// berechne pixelweise: videoFrameGrau = abs(videoFrameGrau - firstFrame)
		absdiff(videoFrameGrau, firstFrame, videoFrameGrau);

		// in Binaerbild wandeln
		int schwelle = getTrackbarPos("Toleranz", "Maske");
		threshold(videoFrameGrau, videoFrameGrau, schwelle, 255, THRESH_BINARY);

		// Tänzer vor Wüste
		hintergrundBild.copyTo(vorBild);
		videoFrame.copyTo(vorBild, videoFrameGrau);

		imshow("Video", videoFrame);
		imshow("Maske", videoFrameGrau);
		imshow("Tänzer vor Wüste", vorBild);
		waitKey(30);
	}
}

void backgroundSubtractionRGB(const string& videoPath, const string& imagePath){
	// Video laden
	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Hintergrundbild laden
	Mat image = imread(imagePath);
	Mat hintergrundBild;
	Size videoSize(width, height);
	resize(image, hintergrundBild, videoSize, 0,0);


	namedWindow("Video");
	namedWindow("Maske");
	createTrackbar("Toleranz", "Maske", 0, 50);
	namedWindow("Tänzer vor Wüste");

	vector<Mat> firstFramePlanes(3);
	Mat vorBild(height, width, CV_8UC3);

	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}

		// RGB-Frame in drei getrennte Ebenen aufsplitten
		vector<Mat>rgbPlanes;
		split(videoFrame, rgbPlanes);

		int schwelle = getTrackbarPos("Toleranz", "Maske");
		frameNumber++;
		for (int plane = 0; plane < 3; plane++){
			// erstes Frame merken
			if(frameNumber == 1){
				rgbPlanes[plane].copyTo(firstFramePlanes[plane]);
			}

			// berechne pixelweise: videoFrameGrau = abs(videoFrameGrau - firstFrame)
			absdiff(rgbPlanes[plane], firstFramePlanes[plane], rgbPlanes[plane]);

			// in Binaerbild wandeln
			threshold(rgbPlanes[plane], rgbPlanes[plane], schwelle, 255, THRESH_BINARY);
		}
		multiply(rgbPlanes[0], rgbPlanes[1], rgbPlanes[0]);
		multiply(rgbPlanes[0], rgbPlanes[2], rgbPlanes[0]);
		Mat mask = rgbPlanes[0];
		

		// Tänzer vor Wüste
		hintergrundBild.copyTo(vorBild);
		videoFrame.copyTo(vorBild, mask);

		imshow("Video", videoFrame);
		imshow("Maske", mask);
		imshow("Tänzer vor Wüste", vorBild);
		waitKey(30);
	}
}

void main(){
	//const string videoPath = "d:/student/micro-dance.wmv";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	const string videoPath = "C:/Users/Andreas/Desktop/micro-dance.wmv";
	const string imagePath = "C:/Users/Public/Pictures/Sample Pictures/desert.jpg";

	backgroundSubtraction(videoPath, imagePath);
}