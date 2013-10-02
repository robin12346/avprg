#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
const string path = "C:/Users/Public/Pictures/Sample Pictures/Jellyfish.jpg";
int main(){
	Mat image = imread(path);
	Vec3b pixelObenLinks = image.at<Vec3b>(0, 0);
	cout << "oben links: " 
		 << (int) pixelObenLinks[2] << " "
		 << (int) pixelObenLinks[1] << " "
		 << (int) pixelObenLinks[0] << endl;

	Vec3b pixelObenRechts = image.at<Vec3b>(0, image.cols - 1);
	cout << "oben links: " 
		 << (int) pixelObenRechts[2] << " "
		 << (int) pixelObenRechts[1] << " "
		 << (int) pixelObenRechts[0] << endl;


	Vec3b pixelZweiteZeileLinks = image.at<Vec3b>(1, 0);
	cout << "oben links: " 
		 << (int) pixelZweiteZeileLinks[2] << " "
		 << (int) pixelZweiteZeileLinks[1] << " "
		 << (int) pixelZweiteZeileLinks[0] << endl;

	Vec3b pixelUntersteZeileLinks = image.at<Vec3b>(1, 0);
	cout << "oben links: " 
		 << (int) pixelUntersteZeileLinks[2] << " "
		 << (int) pixelUntersteZeileLinks[1] << " "
		 << (int) pixelUntersteZeileLinks[0] << endl;
	
	cin.get();
	return 0;
}
