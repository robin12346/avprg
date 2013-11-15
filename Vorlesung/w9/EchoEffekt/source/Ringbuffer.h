#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <vector>

class Ringbuffer{
public:
	Ringbuffer();
	void resize(int size);
	void write(float sample);
	float readWithDelay(int delay);
private:
	std::vector<float> buffer;
	int writeIndex;
};

#endif