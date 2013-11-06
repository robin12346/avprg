#include "HandMotion.h"
using namespace cv;
HandMotion::HandMotion(void)
{
}

HandMotion::~HandMotion(void)
{
}

Point HandMotion::calculateVelocity(Point position){
	Point velocity = position - lastPosition;
	lastPosition = position;
	return velocity;
}