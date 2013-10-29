#include "HandMotion.h"

using namespace cv;

HandMotion::HandMotion(){}

HandMotion::~HandMotion(){}

Point HandMotion::calculateVelocity(Point position){
	Point velocity = position - lastPosition;
	lastPosition = position;
	return velocity;
}