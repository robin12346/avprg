#include "GainProcessor.h"

GainProcessor::GainProcessor()
: gain(1)
{}

void GainProcessor::initialize(float sampleRate){
	this->sampleRate = sampleRate;
}
void GainProcessor::setGain(float gain){
	this->gain = gain;
}

float GainProcessor::processOneSample(float input){
	return input * gain;
}
void GainProcessor::process(float* input, float*output, int numberOfSamples){
	for(int i = 0; i < numberOfSamples; i++){
		output[i] = processOneSample(input[i]);
	}
}