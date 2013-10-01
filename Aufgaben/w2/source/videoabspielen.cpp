#include <opencv2/opencv.hpp>
using namespace cv;

int main(){
	namedWindow("Video");
	namedWindow("erstes Video-Frame");
	VideoCapture videoCapture;
	// ACHTUNG: Pfad bitte anpassen!
	videoCapture.open("C:/Users/Andreas/Desktop/Micro-dance_2_.avi");	
	int width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);


	// >>>>>>>>>> VideoWriter Objekt initialisieren
	VideoWriter videoWriter;
	//>>>>>>>>>> VideoWriter Datei öffnen
	videoWriter.open("Video.avi", CV_FOURCC('P','I','M','1'), 30, Size(width, height), true);


	Mat firstFrame;
	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (false == videoCapture.read(videoFrame)){
			break;
		}
		//>>>>>>>>>> VideoWriter Frame schreiben
		videoWriter.write(videoFrame);
		
		frameNumber++;
		if (frameNumber == 1){
			videoFrame.copyTo(firstFrame);		// kopiert die Pixel des ersten Video Frames
		}


		imshow("erstes Video-Frame", firstFrame);
		imshow("Video", videoFrame);
		waitKey(30);
	}
	return 0;
}

		

