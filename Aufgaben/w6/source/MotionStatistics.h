#ifndef MOTIONSTATISTICS_H__
#define MOTIONSTATISTICS_H__
#include <opencv2\opencv.hpp>

class MotionStatistics{
public:
	MotionStatistics();
	// Regel: eine Basisklasse soll immer einen virtuellen Destruktor haben!
	virtual ~MotionStatistics();
	virtual void setPosition(cv::Point point);
protected:
	cv::Point position;
};

#endif
