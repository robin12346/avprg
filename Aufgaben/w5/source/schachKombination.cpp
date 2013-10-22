#include <sstream>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main(){
	// Bilder laden
	Mat image1 = imread("C:/Users/Public/Pictures/Sample Pictures/tulips.jpg");
	Mat image2OriginalSize = imread("C:/Users/Public/Pictures/Sample Pictures/desert.jpg");
	Mat image2;
	resize(image2OriginalSize, image2, Size(image1.cols, image1.rows));

	// Schachbrettmuster
	Mat chessBoard(image1.rows, image2.cols, CV_8UC1, Scalar(255));
	int w = image1.cols/10;
	int h = image1.rows/10;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if ((i+j)%2 == 0){
				rectangle(chessBoard, Point(i*w, j*h), Point((i+1)*w, (j+1)*h), Scalar(0), CV_FILLED);
			}
		}
	}
	// Bilder kombinieren
	Mat result;
	image1.copyTo(result);
	image2.copyTo(result, chessBoard );

	namedWindow("Bild 1");
	imshow("Bild 1", result);
	waitKey(0);
}
