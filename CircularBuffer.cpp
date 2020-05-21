//
//  CircularBuffer.cpp
//
//  Created by Squishy on 14/02/2018.
//
//  If you use this, please credit me :)

#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(float inValue){
	setBufferLength(inValue);
}

float CircularBuffer::readCubic(float index){
	float y0, y1, y2, y3, mu;

	y0 = floor(index - 1);
	y1 = floor(index);
	y2 = floor(index);
	y3 = floor(index + 1);
	mu = index - y1;
	
	return cubicInterpolation(getSample(y0), getSample(y1), getSample(y2), getSample(y3), mu);
}

float CircularBuffer::readLinear(float index){
	float upper = floor(index) + 1;
	float lower = floor(index);
	float interpAmount = index - lower;
	
	return (getSample(upper) * interpAmount + (1.0 - interpAmount) * getSample(lower));
}

void CircularBuffer::write(float inValue){
    head = (head += 4) % bufferLength;
    buffer[head] = inValue;
}

float CircularBuffer::getSample(float inValue){
    tail = head - inValue;
	
	if (tail > bufferLength - 1)
		tail -= bufferLength;
	else if (tail < 0)
		tail += bufferLength;
	
	return buffer[tail];
}

void CircularBuffer::setBufferLength(float inValue){
    bufferLength = inValue;
    buffer.resize(inValue);
}

int CircularBuffer::getBufferLength(){
    return (int)buffer.size();
}

float CircularBuffer::cubicInterpolation(double y0, double y1, double y2, double y3, double mu){
    //Cubic interp (this algorithm) taken from: http://paulbourke.net/miscellaneous/interpolation/
    double a0, a1, a2, a3, mu2;
    
    mu2 = mu * mu;
	a0 = -0.5 * y0 + 1.5 * y1 - 1.5 * y2 + 0.5 * y3;
	a1 = y0 - 2.5 * y1 + 2 * y2 - 0.5 * y3;
	a2 = -0.5 * y0 + 0.5 * y2;
	a3 = y1;
    
    return(a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}
