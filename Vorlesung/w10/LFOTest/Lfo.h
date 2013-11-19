#ifndef LFO_H
#define LFO_H

class Lfo
{
public:
	Lfo();
	~Lfo(void);
	void initialize(float sampleRate);
	void setFrequency(float setFrequency);
	float getValue();

private:
	int index;
	float sampleRate;
	float frequency;
};

#endif