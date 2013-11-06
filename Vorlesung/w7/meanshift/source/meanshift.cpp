#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// demonstration of histogram calculation (not used later)
std::vector<float> histogram(const Mat& image){
	std::vector<float>histogram(256);
	for(int x = 0; x < image.cols; x++){
		for(int y = 0; y < image.rows; y++){
			uchar pixel = image.at<uchar>(y,x);
			histogram[pixel]++;
		}
	}
	float max_element = *std::max_element(histogram.begin(), histogram.end());
	float scale = 255.0f / max_element;
	for(int i = 0; i < histogram.size(); i++){
		histogram[i] *= scale;
	}
	return histogram;
}

// demonstration of backprojection calculation (not used later)
void backprojection(Mat & image, const std::vector<float>& histogram){
	for(int x = 0; x < image.cols; x++){
		for(int y = 0; y < image.rows; y++){
			uchar pixel = image.at<uchar>(y,x);
			float frequency = histogram[pixel];
			image.at<uchar>(y,x) = (int)frequency;
		}
	}
}

int backprojection(const string& videoPath, const string& referencePath){
	namedWindow("Video");
	namedWindow("Backprojection");

	// Calculate histogram of hand
	Mat handRGB = imread(referencePath);
	Mat handHSV;
	cvtColor(handRGB, handHSV, CV_BGR2HSV);
	vector<Mat>planes;
	split(handHSV, planes);
	Mat handHue = planes[0];

	// Get the Histogram and normalize it
	MatND hist;
	int histSize = 64;
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };
	calcHist( &handHue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
	normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ ) {
		float histValue = hist.at<float>(i - 1);
		cout << histValue << " ";
	}
	cout << endl;

	VideoCapture videoCapture;
	videoCapture.open(videoPath);	
	int width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);


	Rect rect (width/2-20, height/2 - 20, 40, 40);
	while(true){
		Mat videoFrame;
		if (false == videoCapture.read(videoFrame)){
			break;
		}

		Mat videoHSV;
		cvtColor(videoFrame, videoHSV, CV_BGR2HSV);

		vector<Mat>hsvPlanes;
		split(videoHSV, hsvPlanes);
		const int minSaturation = 65;
		threshold(hsvPlanes[1], hsvPlanes[1], minSaturation, 255, THRESH_BINARY);
		Mat videoHue = hsvPlanes[0];
	
		// calculate backprojection
	    MatND backproj;
		calcBackProject(&videoHue, 1, 0, hist, backproj, &ranges, 1, true );

		// mask with (saturation > minSaturation)
		backproj &= hsvPlanes[1];
		imshow("Backprojection", backproj);
		
		TermCriteria criteria(TermCriteria::MAX_ITER, 10, 0.01);
		meanShift(backproj, rect, criteria);

		rectangle(videoFrame, rect, Scalar(0, 255, 0));
		imshow("Video", videoFrame);
		waitKey(100);
	}
	return 0;
}

int main(){
	try
	{	
		const string videoPath = "C:/Users/Andreas/Desktop/Micro-dance.wmv";
		const string handPath = "C:/Users/Andreas/Desktop/rotehand.bmp";

		backprojection(videoPath, handPath);
	}
	catch( cv::Exception& e )
	{
		const char* err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
		waitKey(0);
	}
}