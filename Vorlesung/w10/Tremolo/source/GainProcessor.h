#ifndef GAIN_PROCESSOR_H
#define GAIN_PROCESSOR_H
#include "Lfo.h"
class GainProcessor{
public:
	GainProcessor();
	void initialize(float sampleRate);
	float processOneSample(float);
	void process(float* input, float*output, int numberOfSamples);
	void setGain(float gain);
	void setFrequency(float frequency);
private:
	float sampleRate;
	float gain;
	Lfo lfo;
};
#endif