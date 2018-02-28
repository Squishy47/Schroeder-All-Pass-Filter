//
//  SchroederAllPass.hpp
//  SchroederAllPassTest
//
//  Created by Sam on 16/02/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#ifndef SchroederAllPass_hpp
#define SchroederAllPass_hpp

#include <stdio.h>

// USER HEADERS
#include "CircularBuffer.hpp"


//delay 1.7 - 5 ms

class SchroederAllPass{
    CircularBuffer CB{44100};
    
    int Fs;
    float delayLength;
    float g;
public:
    SchroederAllPass(float inValue, float inG);
        
    void process(float* samples, int bufferSize);
    
    float processSingleSample(float sample);
    
    void setFeedback(float inValue);
    
    float getFeedback();
    
    void setDelayLength(float inValue);
    
    float getDelayLength();
    
    void setFs(int inValue);
};

#endif /* SchroederAllPass_hpp */
