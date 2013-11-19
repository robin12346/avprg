#include <math.h>
#include <iostream>
#include "Lfo.h"
using namespace std;

void main(){
	int sampleRate = 441 ;

	Lfo lfo;
	lfo.initialize(sampleRate);
	lfo.setFrequency(10);

	for (int i = 0; i < sampleRate; i++){
		float value = lfo.getValue();
		cout << i << ": " << value << endl;
	}

	int dummy = 0;
	cin >> dummy;
}