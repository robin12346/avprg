#include <sstream>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void onMouse( int event, int x, int y, int flags, void* param){
	Point* mouse = (Point*) param;
	mouse->x = x;
	mouse->y = y;
}

int main(){
	// Bild laden
	Mat image = imread("C:/Users/Public/Pictures/Sample Pictures/tulips.jpg");
	// im Fenster darstellen
	namedWindow("Originalbild");
	imshow("Originalbild", image);
	
	// nach HSV wandeln
	Mat hsvImage;
	cvtColor(image, hsvImage, CV_BGR2HSV);

	// in HSV-Ebenen aufsplitten
	vector<Mat> hsvPlanes;
	split(hsvImage, hsvPlanes);

	namedWindow("Hue");
	imshow("Hue", hsvPlanes[0]);
	namedWindow("Saturation");
	imshow("Saturation", hsvPlanes[1]);
	namedWindow("Value");
	imshow("Value", hsvPlanes[2]);

	// Maushandler
	Point mouse;
	setMouseCallback("Originalbild", onMouse, &mouse);


	while(waitKey(30) == -1){
		Vec3b pixel = hsvImage.at<Vec3b>(mouse.y, mouse.x);
		// Ausgabe in Konsole
		cout << "H: " << (int)pixel[0] << " S: " << (int)pixel[1] << " V: " << (int)pixel[2] << endl;
		
		// Ausgabe auf das Bild
		Mat copyOfImage;
		image.copyTo(copyOfImage);
		ostringstream os;
		os  << " H:" << (int)pixel[0] 	<< " S:" << (int)pixel[1] << " V:" << (int)pixel[2];
		putText(copyOfImage, os.str(), mouse + Point(10,10), FONT_HERSHEY_SIMPLEX, .3, Scalar(0, 255, 0));
		imshow("Originalbild", copyOfImage);
	}
}
