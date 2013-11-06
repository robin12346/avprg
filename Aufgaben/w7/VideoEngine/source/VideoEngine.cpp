#include "VideoEngine.h"
using namespace cv;

VideoEngine::VideoEngine(void)
: frameWidth (0)
, frameHeight(0)
{
	namedWindow("Video");
	namedWindow("Result");
}

VideoEngine::~VideoEngine(void)
{
	destroyAllWindows();
}
bool VideoEngine::open(const std::string& path){
	videoCapture.open(path);
	if (videoCapture.isOpened()){
		frameNumber = 0;
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
		return true;
	}
	else {
		return false;
	}
}

void VideoEngine::run(){
	while(true){
		Mat videoFrame;
		if (videoCapture.read(videoFrame) == false){
			break;
		}
		frameNumber++;
		showVideoFrame(videoFrame);
		Mat processedFrame;
		processFrame(videoFrame, processedFrame);
		showProcessedFrame(processedFrame);
		waitKey(30);
	}
}
void VideoEngine::showVideoFrame(const Mat&videoFrame){
		imshow("Video", videoFrame);
}
void VideoEngine::processFrame(const Mat&videoFrame, Mat& processedFrame){
	videoFrame.copyTo(processedFrame);	
}
void VideoEngine::showProcessedFrame(const Mat&processedFrame){
		imshow("Result", processedFrame);
}