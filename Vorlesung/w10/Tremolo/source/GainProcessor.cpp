#include "GainProcessor.h"

GainProcessor::GainProcessor()
: gain(1)
{}

void GainProcessor::initialize(float sampleRate){
	this->sampleRate = sampleRate;
	lfo.initialize(sampleRate);
}
void GainProcessor::setGain(float gain){
	this->gain = gain;
}
void GainProcessor::setFrequency(float frequency){
	lfo.setFrequency(frequency);
}

float GainProcessor::processOneSample(float input){
	float lfoValue = lfo.getValue();
	return input * gain * lfoValue;
}
void GainProcessor::process(float* input, float*output, int numberOfSamples){
	for(int i = 0; i < numberOfSamples; i++){
		output[i] = processOneSample(input[i]);
	}
}