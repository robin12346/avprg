#include "mousecallback.h"

// Variante 1 für Mouse-Callback: die globalen Variablen werden gesetzt
int mouseX = 0;
int mouseY = 0;
void mouseCallback1(int event, int x, int y, int flags, void*param){
	mouseX = x;
	mouseY = y;
}
