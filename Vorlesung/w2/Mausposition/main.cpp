#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// Definition der Maushandler-Callbackfunktion
void mouseHandler(int event, int x, int y, int flags, void* param){
	Point* point = (Point*) param;
	point->x = x;
	point->y = y;
	cout << x << " " << y << endl;
}

int main(){
	Mat image(400, 300, CV_8UC3);
	namedWindow("opencv");

	Point mousePosition;
	setMouseCallback("opencv", mouseHandler, &mousePosition);
	imshow("opencv", image);
	waitKey(0);
}