#include "MotionVelocity.h"
using namespace cv;

MotionVelocity::MotionVelocity(){}

MotionVelocity::~MotionVelocity(){}

Point MotionVelocity::getVelocity(){
	Point velocity = position - lastPosition;
	lastPosition = position;
	return velocity;
}
