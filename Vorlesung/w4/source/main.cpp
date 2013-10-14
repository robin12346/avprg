#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(){
	VideoCapture videoCapture;
	videoCapture.open("C:\\Users\\andreas\\Desktop\\Micro-dance_2_.avi");
	int width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

	namedWindow("Video");
	namedWindow("first frame");
	namedWindow("Maske");
	Mat binaerMaske(height, width, CV_8UC1);

	Mat firstFrame;
	int frameNumber = 0;
	while(true){
		Mat videoFrame;
		if (false == videoCapture.read(videoFrame)){
			break;
		}
		frameNumber++;
		if (frameNumber == 1){
			videoFrame.copyTo(firstFrame);
		}
		for(int x = 0; x < width; x++){
			for(int y = 0; y < height; y ++){
				Vec3b pixelVideo = videoFrame.at<Vec3b>(y, x);
				Vec3b pixelFirstFrame = firstFrame.at<Vec3b>(y,x);

				int helligkeitVideo = (pixelVideo[0] + pixelVideo[1]
					+ pixelVideo[2])/3;
				int helligkeitFirstFrame = (pixelFirstFrame[0] 
					+ pixelFirstFrame[1] + pixelFirstFrame[2])/3;

				int binaerPixel;
				if (abs(helligkeitVideo - helligkeitFirstFrame) > 20){
					binaerPixel = 255;
				}
				else {
					binaerPixel = 0;
				}
				binaerMaske.at<uchar>(y,x) = binaerPixel;

			}
		}
		imshow("Video", videoFrame);
		imshow("first frame", firstFrame);
		imshow("Maske", binaerMaske);
		waitKey(30);
	}
}
