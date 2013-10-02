#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
const string path = "C:/Users/Public/Pictures/Sample Pictures/Jellyfish.jpg";
int main(){
	Mat image = imread(path);
	Mat copyOfImage(image.rows, image.cols, image.type());

	namedWindow("Original");
	namedWindow("Kopie");

	if (image.type() == CV_8UC3){
		for(int x = 0; x < image.cols; x++){
			for(int y = 0; y < image.rows; y++){
				Vec3b pixel = image.at<Vec3b>(y, x);
				copyOfImage.at<Vec3b>(y,x) = pixel;
			}
		}
	}
	
	imshow("Original", image);
	imshow("Kopie", copyOfImage);
	waitKey(0);
	return 0;
}
