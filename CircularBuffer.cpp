//
//  CircularBuffer.cpp
//  CircularBuffer - All
//
//  Created by Squishy on 14/02/2018.
//
#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(float inValue){
    bufferLength = inValue;
    buffer.resize(bufferLength);
}

float CircularBuffer::read(float numElementsToRead, std::string interpType){
    if(interpType == "Cubic"){
        float y1 = interpCalcAmount(numElementsToRead, "lower");
        float y2 = interpCalcAmount(numElementsToRead, "upper");
    
        float y0 = interpCalcAmount(numElementsToRead - 1, "lower");
        float y3 = interpCalcAmount(numElementsToRead + 1, "upper");
    
        float mu = numElementsToRead - y1;

        return cubicInterpolation(getSample(y0), getSample(y1), getSample(y2), getSample(y3), mu);
    }
    else{
        //Linear
        float upper = interpCalcAmount(numElementsToRead, "upper");
        float lower = interpCalcAmount(numElementsToRead, "lower");
        float interpAmount = numElementsToRead - lower;
        return (getSample(upper) * interpAmount + (1.0 - interpAmount) * getSample(lower));
    }
}

void CircularBuffer::write(float inValue){
    head++;

    if(head > bufferLength - 1)
        head -= bufferLength;
    else if(head < 0)
        tail += bufferLength;
    
    buffer[head] = inValue;
}

float CircularBuffer::interpCalcAmount(float inValue, std::string inSelector){
    float upper, lower, inRounded = round(inValue);
    
    if(inRounded > inValue){
        upper = inRounded;
        lower = upper - 1;
    }
    else{
        lower = inRounded;
        upper = lower + 1;
    }
    
    if(inSelector == "upper")
        return upper;
    else if(inSelector == "lower")
        return lower;
    else
        return 0.0;
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
