#include <opencv2/opencv.hpp>
#include "backgroundsubtraction.h"
using namespace cv;
using namespace std;


const int crossLength = 30;
const Scalar colorGreen(0, 255, 0);
const Scalar colorBlau(255, 0, 0);

void backgroundSubtraction(const string& videoPath, const string& imagePath){
	// Video laden
	VideoCapture video;
	video.open(videoPath);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Hintergrundbild laden
	Mat imageOriginalSize = imread(imagePath);
	Mat image;
	resize(imageOriginalSize, image, Size(width, height));
	
	namedWindow("Video");
	namedWindow("erstes Frame");
	namedWindow("Maske");
	createTrackbar("Schwelle", "Maske", 0, 100);
	setTrackbarPos("Schwelle", "Maske", 20);
	namedWindow("Tänzer vor Blau");
	namedWindow("Tänzer vor Bild");
	Mat firstFrame;
	Mat binaerMaske(height, width, CV_8UC1);

	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (video.read(videoFrame) == false){
			break;
		}
		frameNumber++;
		if(frameNumber == 1){
			videoFrame.copyTo(firstFrame);
		}
		// Mat-Objekte für Kombinationen
		Mat taenzerVorBlau;
		videoFrame.copyTo(taenzerVorBlau);
		Mat taenzerVorBild;
		videoFrame.copyTo(taenzerVorBild);

		int schwelle = getTrackbarPos("Schwelle", "Maske");
		for(int x = 0; x < videoFrame.cols; x++){
			for (int y = 0; y < videoFrame.rows; y++){
				Vec3b pixelVideo = videoFrame.at<Vec3b>(y, x);
				Vec3b pixelFirstFrame = firstFrame.at<Vec3b>(y,x);

				int helligkeitPixelVideo = 
					(pixelVideo[0] + pixelVideo[1] + pixelVideo[2])/3;
				int helligkeitPixelFirstFrame =
					(pixelFirstFrame[0] + pixelFirstFrame[1] + pixelFirstFrame[2])/3;

				if(abs(helligkeitPixelVideo - helligkeitPixelFirstFrame) > schwelle){
					// Vordergrund
					binaerMaske.at<uchar>(y,x) = 255;
				}
				else{
					// Hintergrund
					binaerMaske.at<uchar>(y,x) = 0;
					taenzerVorBlau.at<Vec3b>(y,x) = Vec3b(255,0,0);
					taenzerVorBild.at<Vec3b>(y,x) = image.at<Vec3b>(y,x);
				}
			}
		}

		imshow("Video", videoFrame);
		imshow("erstes Frame", firstFrame);
		imshow("Maske", binaerMaske);
		imshow("Tänzer vor Blau", taenzerVorBlau);
		imshow("Tänzer vor Bild", taenzerVorBild);
		waitKey(30);
	}
}
