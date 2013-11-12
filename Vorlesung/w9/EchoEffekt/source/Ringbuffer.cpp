#include "Ringbuffer.h"
using namespace std;

Ringbuffer::Ringbuffer()
	: writeIndex (0)
{}

void Ringbuffer::resize(int size){
	buffer.resize(size);
}

void Ringbuffer::write(float sample){
	buffer[writeIndex] = sample;
	writeIndex++;
	if (writeIndex == buffer.size()){
		writeIndex = 0;
	}
}

float Ringbuffer::readWithDelay(int delay){
	int readIndex = writeIndex - delay;
	if (readIndex < 0){
		readIndex += buffer.size();
	}
	float sample = buffer[readIndex];
	return sample;
}