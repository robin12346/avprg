#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;
void main(){
	namedWindow("opencv");

	Mat image (300, 400, CV_8UC1);
	// Hintergrund schwarz
	image = (uchar) 0;
	rectangle(image, Point(10, 10), Point(20, 30), 255, CV_FILLED);

	// 2-dimensionaler Vektor von Koordinaten
	vector<vector<Point> > contours;
	findContours(image, contours, 
			CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	cout << "es gibt " << contours.size() << " Regionen" << endl;
	cout << "Koordinaten: " << endl;
	for(int i = 0; i < contours[0].size(); i++){
		Point p = contours[0][i];
		cout << p.x << " " << p.y << endl;
	}

	// Einfärben
	Mat coloredImage (300, 400, CV_8UC3);
	coloredImage=Scalar(0, 0, 0);
	int indexOfRegion = 0;
	Scalar color(255, 255, 0);
	drawContours(coloredImage, contours, indexOfRegion, 
						color, CV_FILLED);

	imshow("opencv", coloredImage);


	// Fläche
	vector<Point> contour = contours[0];
	int area = contourArea(contour);
	cout << "Fläche: " << area << endl;

	// bounding rect
	Rect rect = boundingRect(contour);
	cout << rect.width << " " << rect.height << endl;

	imshow("opencv", coloredImage);

	waitKey(0);
}