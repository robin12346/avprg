#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


void aendereHelligkeitKontrast(const string& imagePath){
	namedWindow("Originalbild");
	namedWindow("Bearbeitetes Bild");
	createTrackbar("Helligkeit", "Bearbeitetes Bild", 0, 512);	    // -256 ... 256
	setTrackbarPos("Helligkeit", "Bearbeitetes Bild", 256);
	createTrackbar("Kontrast", "Bearbeitetes Bild", 0, 10);			//   -5 ... +5
	setTrackbarPos("Kontrast", "Bearbeitetes Bild", 5);

	Mat image = imread(imagePath);
	Mat processedImage(image.rows, image.cols, image.type());

	while(waitKey(30) == -1){
		// ACHTUNG: die Abfrage sollte hier geschehen und NICHT innerhalb der for-Schleifen,
		//          was enorm viel Performance kosten würde!
		int helligkeitsAenderung = getTrackbarPos("Helligkeit", "Bearbeitetes Bild") - 256;

		int kontrastTrackbarPos = getTrackbarPos("Kontrast", "Bearbeitetes Bild");
		double kontrastAenderung = pow(5., (kontrastTrackbarPos - 5) / 5);			// 1/5 ... 5
		for(int x = 0; x < image.cols; x++){
			for(int y = 0; y < image.rows; y++){
				
				Vec3b srcPixel = image.at<Vec3b>(y,x);
				int r = srcPixel[2];
				int g = srcPixel[1];
				int b = srcPixel[0];

				r = saturate_cast<uchar>(r * kontrastAenderung + helligkeitsAenderung);
				g = saturate_cast<uchar>(g * kontrastAenderung + helligkeitsAenderung);
				b = saturate_cast<uchar>(b * kontrastAenderung + helligkeitsAenderung);

				Vec3b dstPixel(b,g,r);
				processedImage.at<Vec3b>(y,x) = dstPixel;
			}
		}

		imshow("Originalbild", image);
		imshow("Bearbeitetes Bild", processedImage);
	}
}

void wandleInGraustufenUndBinaerbild(const string& imagePath){
	namedWindow("Originalbild");
	namedWindow("Graustufen Bild");
	namedWindow("Binärbild");
	createTrackbar("Schwelle", "Binärbild", 0, 255);
	setTrackbarPos("Schwelle", "Binärbild", 128);

	Mat image = imread(imagePath);
	Mat grauesBild(image.rows, image.cols, CV_8UC1);
	Mat schwarzweissBild(image.rows, image.cols, CV_8UC1);

	while(waitKey(30) == -1){
		int schwelle = getTrackbarPos("Schwelle", "Binärbild");
		for(int x = 0; x < image.cols; x++){
			for(int y = 0; y < image.rows; y++){
				Vec3b pixel = image.at<Vec3b>(y,x);
				int grauWert = (pixel[0] + pixel[1] + pixel[2])/3;
				int binaerWert; 
				if (grauWert > schwelle){
					binaerWert = 255;
				}
				else{
					binaerWert = 0;
				}
				// oder kürzer
				// int binaerWert = (grauWert > schwelle) ? 255 : 0;
				grauesBild.at<uchar>(y,x) = grauWert;
				schwarzweissBild.at<uchar>(y,x) = binaerWert;
			}
		}
		imshow("Originalbild", image);
		imshow("Graustufen Bild", grauesBild);
		imshow("Binärbild", schwarzweissBild);
	}
}
void wandleInPlanar(const string& imagePath){

	Mat image = imread(imagePath);
	Mat rotKomponente(image.rows, image.cols, CV_8UC1);
	Mat gruenKomponente(image.rows, image.cols, CV_8UC1);
	Mat blauKomponente(image.rows, image.cols, CV_8UC1);
	for(int x = 0; x < image.cols; x++){
		for(int y = 0; y < image.rows; y++){
			Vec3b pixel = image.at<Vec3b>(y,x);
			uchar blauerWert = pixel[0];
			uchar gruenerWert = pixel[1];
			uchar roterWert = pixel[2];
			rotKomponente.at<uchar>(y,x) = roterWert;
			gruenKomponente.at<uchar>(y,x) = gruenerWert;
			blauKomponente.at<uchar>(y,x) = blauerWert;
		}
	}

	namedWindow("Originalbild");
	imshow("image", image);
	namedWindow("rote Komponente");
	imshow("rote Komponente", rotKomponente);
	namedWindow("grüne Komponente");
	imshow("grüne Komponente", gruenKomponente);
	namedWindow("blaue Komponente");
	imshow("blaue Komponente", blauKomponente);
	waitKey(0);
}

void morph(const string& imagePath, const string& imagePath2){

	Mat image1 = imread(imagePath);
	Mat image2Original = imread(imagePath2);

	Mat image2;
	Size resizedImageSize(image1.cols, image1.rows);
	resize(image2Original, image2, resizedImageSize, 0,0);

	Mat image3(image1.rows, image1.cols, image1.type());

	namedWindow("Bild 1");
	namedWindow("Bild 2");
	namedWindow("Bild 3");
	createTrackbar("Blenden", "Bild 3", 0, 100);

	while(waitKey(30) == -1){
		double alpha = getTrackbarPos("Blenden", "Bild 3") / 100.;
		double beta = 1 - alpha;
		for(int x = 0; x < image1.cols; x++){
			for(int y = 0; y < image1.rows; y++){
				Vec3b pixel1 = image1.at<Vec3b>(y,x);
				Vec3b pixel2 = image2.at<Vec3b>(y,x);

				Vec3b pixel3 = pixel1 * alpha + pixel2 * beta;
				image3.at<Vec3b>(y,x) = pixel3;
			}

		}

		imshow("Bild 1", image1);
		imshow("Bild 2", image2);
		imshow("Bild 3", image3);
	}
}
// Mouse-Callback: Adresse eines Point-Objekts für die Mauskoordinaten wird übergeben
void mouseCallback2(int event, int x, int y, int flags, void*param){
	Point *mouse = (Point*) param;		// typecast von void* nach Point* (= Zeiger auf Point-Objekt)
	mouse->x = x;
	mouse->y = y;
}

void pixelLupe(const string& imagePath){
	Mat image = imread(imagePath);

	namedWindow("Aufgabe 5");

	Point mouse;
	setMouseCallback("Aufgabe 5", mouseCallback2, &mouse);	// Adresse von mouse wird uebergeben

	while(waitKey(30) == -1){
		Vec3b pixel = image.at<Vec3b>(mouse.y, mouse.x);

		rectangle(image, Point(0,0),Point(20,20), Scalar(pixel), CV_FILLED);

		imshow("Aufgabe 5", image);
	}
}
