#include <opencv2/opencv.hpp>
#include <iostream>
#include "mousecallback.h"
using namespace cv;
using namespace std;


void aufgabe1(){
	namedWindow("Aufgabe1");				// Fenster erzeugen
	createTrackbar("rot", "Aufgabe1", 0, 255);
	createTrackbar("grün", "Aufgabe1", 0, 255);
	createTrackbar("blau", "Aufgabe1", 0, 255);

	Mat image(400, 400, CV_8UC3);
	while(waitKey(30) == -1){
		int r = getTrackbarPos("rot", "Aufgabe1");
		int g = getTrackbarPos("grün", "Aufgabe1");
		int b = getTrackbarPos("blau", "Aufgabe1");

		image = Scalar(b,g,r);
		imshow("Aufgabe1", image);
	}
}


void aufgabe2(){
	const int laenge = 30;
	namedWindow("Aufgabe2");				// Fenster erzeugen
	setMouseCallback("Aufgabe2", mouseCallback1);

	Mat image(400, 400, CV_8UC3);
	while(waitKey(30) == -1){
		image =  Scalar(255,255,255);	// alte Zeichnung löschen (auf Weiß setzen)

		Point pt1(mouseX, mouseY);
		double diagonale = norm(pt1);
		Point pt2(mouseX - mouseX * laenge / diagonale, mouseY - mouseY * laenge / diagonale);
		line(image, pt1, pt2, Scalar(0, 0, 255), 1);

		imshow("Aufgabe2", image);
	}
}

// Variante 2 für Mouse-Callback: Adresse eines Point-Objekts für die Mauskoordinaten wird übergeben
void mouseCallback2(int event, int x, int y, int flags, void*param){
	Point2f *mouse = (Point2f*) param;		// typecast von void* nach Point2f* (= Zeiger auf Point2f-Objekt)
	
	// ist das gleiche wie:
	// (*mouse).x = x;
	// (*mouse).y = y;
	
	mouse->x = x;
	mouse->y = y;
}

// ACHTUNG: diese Lösung verwendet die Klasse Point2f, die eine Koordinate als zwei float-Zahlen repräsentiert
// Bei der Variante mit Point (x,y als int) kommt es zu Rundungsfehlern.
void aufgabe3(){
	const Scalar colorRed(0, 0, 255);
	const int radius = 10;
	
	namedWindow("Aufgabe 3");				// Fenster erzeugen

	Point2f mouse;
	setMouseCallback("Aufgabe 3", mouseCallback2, &mouse);	// Adresse von mouse wird uebergeben

	Point2f mouseGefiltert = mouse;

	Mat image(400, 400, CV_8UC3);
	while(waitKey(30) == -1){
		image =  Scalar(255,255,255);	// alte Zeichnung löschen (auf Weiß setzen)
										// Für Experten: das geht nur, weil der = Operator von Mat überschrieben wurde
		
		mouseGefiltert = 0.9f * mouseGefiltert + 0.1f * mouse;
		circle(image, mouseGefiltert, radius, colorRed, CV_FILLED);
		imshow("Aufgabe 3", image);
	}
}

int main(){
	cout << "Welche Aufgabe?" << endl;
	int choice;
	cin >> choice;

	if (choice == 1){
		aufgabe1();
	}
	else if (choice == 2){
		aufgabe2();
	}
	else if (choice == 3){
		aufgabe3();
	}
	return 0;
}
