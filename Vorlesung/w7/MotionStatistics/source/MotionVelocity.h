#ifndef __MOTIONVELOCITY_H
#define __MOTIONVELOCITY_H
#include "MotionStatistics.h"

class MotionVelocity:public MotionStatistics
{
public:
	MotionVelocity(void);
	~MotionVelocity(void);
	cv::Point getVelocity();
private:
	cv::Point lastPosition;
	
};
#endif