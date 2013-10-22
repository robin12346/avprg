#include <string>
#include <stack>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

bool isPixelWhite(Mat& image, int y, int x){
	Vec3b pixel = image.at<Vec3b>(y,x);
	if (pixel == Vec3b(255,255,255)){
		return true;
	}
	else {
		return false;
	}
}



void floodFill(Mat& image, int y, int x, Vec3b label){
	if (x >= 0 && x < image.cols && y >= 0 && y < image.rows
			&& isPixelWhite(image, y, x) == true
	){
		image.at<Vec3b>(y,x) = label;
		floodFill(image, y-1, x  , label);
		floodFill(image, y  , x+1, label);
		floodFill(image, y+1, x  , label);
		floodFill(image, y  , x-1, label);
	}
}

void floodFill2(Mat& image, int y, int x, Vec3b label){
	stack<Point> stack;
	stack.push(Point(x,y));
	while(stack.empty() == false){
		Point point = stack.top();
		stack.pop();
		x = point.x;
		y = point.y;
		if (x >= 0 && x < image.cols && y >= 0 && y < image.rows
			&& isPixelWhite(image, y, x) == true
		){
			image.at<Vec3b>(y,x) = label;
			stack.push(Point(x  , y-1));
			stack.push(Point(x+1, y  ));
			stack.push(Point(x  , y+1));
			stack.push(Point(x-1, y  ));
		}
	}
}
			



void main(){
	Mat image(300, 400, CV_8UC3);
	
	// Region 1
	rectangle(image, Point(10,10), Point(30,30), Scalar(255,255,255), CV_FILLED);
	rectangle(image, Point(30,30), Point(35,45), Scalar(255,255,255), CV_FILLED);
	// Region 2
    ellipse(image, Point(100,100), Size(20,30), 0, 0, 360, Scalar(255,255,255), 3);
	// Region 3
	rectangle(image, Point(5, 100), Point(50, 200), Scalar(255,255,255), CV_FILLED);
	namedWindow("Originalbild");
	imshow("Originalbild", image);

	floodFill(image, 11,11, Vec3b(255,0,0));
	floodFill(image, 71,100,Vec3b(0, 255, 0));
	floodFill2(image, 101, 6, Vec3b(0, 0, 255));
	namedWindow("FloodFilled");
	imshow("FloodFilled", image);

	waitKey(0);

}
