#include "BackgroundSubstraction.h"
using namespace cv;
using namespace std;

int main(){
	const string videoPath = "C:/Users/Andreas/Desktop/micro-dance.wmv";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	Backgroundsubstraction app;
	if (app.open(videoPath)){
		app.run();
	}
}