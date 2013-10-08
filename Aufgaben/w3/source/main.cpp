#include "aufgaben3.h"
#include <iostream>
using namespace std;

const string imagePath2 = "C:/Users/Public/Pictures/Sample Pictures/Jellyfish.jpg";
const string imagePath = "C:/Users/Public/Pictures/Sample Pictures/desert.jpg";

int main(){
	cout << "Welche Aufgabe?" << endl;
	int choice;
	cin >> choice;

	if (choice == 1){
		aendereHelligkeitKontrast(imagePath);
	}
	else if (choice == 2){
		wandleInGraustufenUndBinaerbild(imagePath);
	}
	else if (choice == 3){
		wandleInPlanar(imagePath);
	}
	else if (choice == 4){
		morph(imagePath, imagePath2);
	}
	else if (choice == 5){
		pixelLupe(imagePath);
	}
	return 0;
}
