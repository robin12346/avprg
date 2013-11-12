#ifndef DELAYPROCESSOR_H
#define DELAYPROCESSOR_H

#include "Ringbuffer.h"

class DelayProcessor{
public:
	DelayProcessor();
	void initialize(float sampleRate);
	float processOneSample(float sample);
	void process(float* input, float* output, int numberOfSamples);
private:
	float sampleRate;
	Ringbuffer ringbuffer;
};

#endif