#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

void showVideo(){
	const string path = "C:\\Users\\andreas\\Dropbox\\Micro-dance_2_.avi";
	// VideoCapture-Objekt
	VideoCapture videoCapture;
	// Videodatei öffnen
	videoCapture.open(path);
	// Kamera öffnen
	//videoCapture.open(0);
	// leeres Fenster erzeugen
	namedWindow("Video");
	// trackbar hinzufügen
	createTrackbar("slider", "Video", 0, 255);


	int width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int fps = videoCapture.get(CV_CAP_PROP_FPS);
	int count = videoCapture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << width << "x" << height << endl;
	cout << fps << " fps" << endl;
	cout << count << " frames" << endl;

	// Videoframes lesen
	while(true){
		Mat videoFrame;
		// Videoframe lesen
		bool success = videoCapture.read(videoFrame);
		if (success == false){
			break;
		}
		imshow("Video", videoFrame);
		
		int value = getTrackbarPos("slider", "Video");
		cout << value << endl;

		// 30 ms auf einen Tastendruck warten; bei Tastendruck beenden
		int key = waitKey(30);
		if (key != -1){
			break;
		}
	}
}


void showImage(){
	const string path = "C:\\Users\\Public\\Pictures\\Sample Pictures\\desert.jpg";
	Mat image = imread(path);
	
	cout << "Breite: " << image.size().width << endl;
	cout << "Hoehe: " << image.size().height << endl;

	namedWindow("desert");
	imshow("desert", image);

	waitKey(0);
}

int main(){
	showVideo();
}