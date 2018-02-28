//
//  SchroederAllPass.cpp
//
//  Created by Squishy on 14/02/2018.
//
//  If you use this, please credit me :)

#include "SchroederAllPass.hpp"

SchroederAllPass::SchroederAllPass(float inValue, float inG){
	setDelayLength(inValue);
	setFeedback(inG);
}

void SchroederAllPass::process(float* samples, int bufferSize){
    for(int i = 0; i < bufferSize; i++)
        samples[i] = processSingleSample(samples[i]);
}

float SchroederAllPass::processSingleSample(float sample){
    float delay = CB.read(delayLength, linear);
	
    CB.write(sample + (delay * g));

    delay = delay * (1 - (g * g));

    sample = sample * -g;

    return (delay + sample);
}

void SchroederAllPass::setFeedback(float inValue){
    g = inValue;
}

float SchroederAllPass::getFeedback(){
    return g;
}

void SchroederAllPass::setDelayLength(float inValue){
	if(inValue > 1.0)
		delayLength = inValue;
	else
		delayLength = 1.0;
	
    if (delayLength > CB.getBufferLength())
        CB.setBufferLength(delayLength);
}

float SchroederAllPass::getDelayLength(){
    return delayLength;
}
