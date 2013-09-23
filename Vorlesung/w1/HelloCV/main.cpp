#include "opencv2/opencv.hpp"
using namespace cv;
int main(){
	Mat image(480, 640, CV_8UC3);
	rectangle(image, Point(100,100), Point(200,200), Scalar(255,0,0), 3);
	namedWindow( "opencv", 1 );
	imshow( "opencv", image );
	waitKey(0);
	return 0;
}