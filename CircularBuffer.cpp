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

float CircularBuffer::read(float index, InterType inValue){
	float y0, y1, y2, y3, mu, upper, lower, interpAmount;
	
	switch(inValue){
		case cubic:{
				y0 = interpCalcAmount(index - 1, lowerBound);
				y1 = interpCalcAmount(index, lowerBound);
				y2 = interpCalcAmount(index, upperBound);
				y3 = interpCalcAmount(index + 1, upperBound);

				mu = index - y1;

				return cubicInterpolation(getSample(y0), getSample(y1), getSample(y2), getSample(y3), mu);
			break;
		}
		case linear:{
				upper = interpCalcAmount(index, upperBound);
				lower = interpCalcAmount(index, lowerBound);
				interpAmount = index - lower;
				return (getSample(upper) * interpAmount + (1.0 - interpAmount) * getSample(lower));
			break;
		}
		default:
			return 0.0;
		break;
	}
}

void CircularBuffer::write(float inValue){
    head++;
    buffer[head % bufferLength] = inValue;
}

float CircularBuffer::interpCalcAmount(float inValue, Selector inSelector){
    float upper, lower, isRounded = round(inValue);
    
    if(isRounded > inValue){
        upper = isRounded;
        lower = upper - 1;
    }
    else{
        lower = isRounded;
        upper = lower + 1;
    }
	
	switch(inSelector){
		case upperBound:
			return upper;
			break;
		case lowerBound:
			return lower;
			break;
		default:
			return 0.0;
	}
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
    //Cubic interp taken from: http://paulbourke.net/miscellaneous/interpolation/
    double a0, a1, a2, a3, mu2;
    
    mu2 = mu * mu;
    a0 = y3 - y2 - y0 + y1;
    a1 = y0 - y1 - a0;
    a2 = y2 - y0;
    a3 = y1;
    
    return(a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}
