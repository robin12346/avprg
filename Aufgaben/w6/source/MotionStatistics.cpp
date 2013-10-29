#include "MotionStatistics.h"
using namespace cv;

MotionStatistics::MotionStatistics(){}

MotionStatistics::~MotionStatistics(){}

void MotionStatistics::setPosition(Point point){
	position = point;
}