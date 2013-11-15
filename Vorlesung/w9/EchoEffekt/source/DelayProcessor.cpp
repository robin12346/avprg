#include "DelayProcessor.h"

float DELAY_SEC = 0.1;	// 100 ms Delay

DelayProcessor::DelayProcessor()
	: sampleRate(0)
{
}

void DelayProcessor::initialize(float samplerate){
	this->sampleRate = samplerate;
	ringbuffer.resize(1 * samplerate);	// 1 Sekunde
}

float DelayProcessor::processOneSample(float sample){
	float output = ringbuffer.readWithDelay(DELAY_SEC * sampleRate);
	ringbuffer.write(sample);
	return output + sample;
}

void DelayProcessor::process(float* input, float* output, int numberOfSamples){
	for(int i = 0; i < numberOfSamples; i++){
		output[i] = processOneSample(input[i]);
	}
}

