#include "MotionVelocity.h"
using namespace cv;

MotionVelocity::MotionVelocity(void)
{
}

MotionVelocity::~MotionVelocity(void)
{
}
Point MotionVelocity::getVelocity(){
	Point velocity = position - lastPosition;
	lastPosition = position;
	return velocity;
}