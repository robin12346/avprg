#ifndef MOTIONVELOCITY_H__
#define MOTIONVELOCITY_H__

#include "MotionStatistics.h"

class MotionVelocity: public MotionStatistics{
public:
	MotionVelocity();
	~MotionVelocity();
	cv::Point getVelocity();
private:
	cv::Point lastPosition;
};

#endif