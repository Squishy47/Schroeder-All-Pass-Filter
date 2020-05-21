//
//  SchroederAllPass.cpp
//  SchroederAllPassTest
//
//  Created by Sam on 16/02/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#include "SchroederAllPass.hpp"

SchroederAllPass::SchroederAllPass(float inValue, float inG){
    delayLength = inValue;
    g = inG;
}

void SchroederAllPass::process(float* samples, int bufferSize){
    for(int i = 0; i < bufferSize; i++)
        samples[i] = processSingleSample(samples[i]);
}

float SchroederAllPass::processSingleSample(float sample){
    delayedSample = CB.read(delayLength, "Cubic");
    
    CB.write(sample + (delayedSample * g));

    feedFordwardSample = sample * -g;

    return (delayedSample + feedFordwardSample);
}



void SchroederAllPass::setFeedback(float inValue){
    g = inValue;
}

float SchroederAllPass::getFeedback(){
    return g;
}

void SchroederAllPass::setDelayLength(float inValue){
    delayLength = inValue;
    if (delayLength > CB.getBufferLength())
        CB.setBufferLength(delayLength);
}

float SchroederAllPass::getDelayLength(){
    return delayLength;
}

void SchroederAllPass::setFs(int inValue){
    Fs = inValue;
}


