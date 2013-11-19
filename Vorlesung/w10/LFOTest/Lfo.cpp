#include <math.h>
#include "Lfo.h"

const float pi = 3.1415926f;

Lfo::Lfo()
: sampleRate(0), index(0), frequency(0)
{}

Lfo::~Lfo(void)
{
}
void Lfo::initialize(float sampleRate){
	this->sampleRate = sampleRate;
}
void Lfo::setFrequency(float setFrequency){
	frequency = setFrequency;
}

float Lfo::getValue(){
	float value = sin(2 * pi * index * frequency / sampleRate);
	index++;
	return 0.5 * (value + 1);
}
