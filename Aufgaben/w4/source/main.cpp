#include "backgroundsubtraction.h"
#include "colorkeying.h"

using namespace std;


const string videoPath = "C:/Users/Andreas/Desktop/Micro-dance.wmv";	
const string imagePath = "C:/Users/Public/Pictures/Sample Pictures/desert.jpg";

int main(){
	//backgroundSubtraction(videoPath, imagePath);
	colorKeyingRGB(videoPath);
	return 0;
}