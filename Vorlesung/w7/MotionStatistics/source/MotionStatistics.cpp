#include "MotionStatistics.h"
using namespace cv;

MotionStatistics::MotionStatistics(void)
{
}

MotionStatistics::~MotionStatistics(void)
{
}
void MotionStatistics::setPosition(cv::Point pt){
	position = pt;
}