#ifndef __HANDMOTION_H
#define __HANDMOTION_H
#include <opencv2/opencv.hpp>

class HandMotion
{
public:
	HandMotion(void);
	~HandMotion(void);
	cv::Point calculateVelocity(cv::Point position);
private:
	cv::Point lastPosition;
};
#endif