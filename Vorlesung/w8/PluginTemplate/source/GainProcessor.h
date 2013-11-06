#ifndef GAIN_PROCESSOR_H
#define GAIN_PROCESSOR_H

class GainProcessor{
public:
	GainProcessor();
	void initialize(float sampleRate);
	float processOneSample(float);
	void process(float* input, float*output, int numberOfSamples);
	void setGain(float gain);
private:
	float sampleRate;
	float gain;
};
#endif