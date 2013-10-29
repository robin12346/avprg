#ifndef HANDMOTION_H__
#define HANDMOTION_H__
#include <opencv2/opencv.hpp>

class HandMotion{
public:
	HandMotion();
	~HandMotion();
	cv::Point calculateVelocity(cv::Point position);
private:
	cv::Point lastPosition;
};


#endif