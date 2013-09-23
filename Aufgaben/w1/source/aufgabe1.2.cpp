#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(){
	// 1. Definieren Sie Variablen für x, y (linke obere Ecke), Breite und Höhe eines Rechtecks. 
	// Weisen Sie denen beliebige Werte zu. Die folgenden Teilaufgaben sollen diese Variablen verwenden, 
	// nicht jedoch deren Werte.

	int x = 10;
	int y = 100;
	int breite = 200;
	int hoehe = 20;

	// 2.  Erstellen Sie eine Variable, die ein entsprechendes Rechteck repräsentiert. 
	Rect rect(x, y, breite, hoehe);
	cout << "2. rect: x=" << rect.x << " y=" << rect.y 
		 << " width=" << rect.width << " height=" << rect.height << endl;

	// 3. Initialisieren Sie drei Variablen, die die Koordinaten bestimmter Punkte des Rechtecks 
	//    repräsentieren: 
    //		linksOben: linke obere Ecke des Rechtecks
	//		rechtsUnten: rechte untere Ecke des Rechtecks
	//		centrum:  Zentrum des Rechtecks
	// Lassen Sie dabei den Compiler die Berechnungen durchführen, d.h. verwenden Sie keine magic numbers.

	Point linksOben(rect.x, rect.y);
	Point rechtsUnten(rect.x + rect.width, rect.y + rect.height);
	Point centrum(rect.x + rect.width/2, rect.y + rect.height/2);
	cout << "3: linksoben: " << linksOben 
		 << " rechtsUnten: " << rechtsUnten
		 << " centrum: " << centrum << endl;
	
	// 4. Berechnen Sie die Länge der Diagonalen des Rechtecks. Verwenden  Sie dazu die Funktion norm().
	double laengeDiagonale = norm(linksOben - rechtsUnten);
	cout << "4: Diagonale: " << laengeDiagonale << endl;

	// 5. Transformieren Sie das Rechteck so, dass seine neue linke obere Ecke im Zentrum des alten 
	//    Rechtecks ist, seine neue rechte untere Ecke soll mit der des alten Rechtecks identisch sein.
	
	// Rechteck verschieben
	Point offset = centrum - linksOben;		
	rect = rect + offset;				
	
	// Rechteck schrumpfen
	Size resize(-rect.width/2, -rect.height/2);
	rect = rect + resize;				

	cout << "5. rect: x=" << rect.x << " y=" << rect.y 
		 << " width=" << rect.width << " height=" << rect.height << endl;
	
	int dummy;
	cin >> dummy;
	
	return 0;
}