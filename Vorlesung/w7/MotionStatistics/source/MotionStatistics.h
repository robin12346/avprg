#ifndef __MOTIONSTATISTICS_H
#define __MOTIONSTATISTICS_H
#include <opencv2/opencv.hpp>
class MotionStatistics
{
public:
	MotionStatistics(void);
	~MotionStatistics(void);
	void setPosition(cv::Point pt);
protected:
	cv::Point position;
};
#endif