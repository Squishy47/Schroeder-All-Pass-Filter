//
//  SchroederAllPass.hpp
//
//  Created by Squishy on 14/02/2018.
//
//  If you use this, please credit me :)

#ifndef SchroederAllPass_hpp
#define SchroederAllPass_hpp

#include <stdio.h>

// USER HEADERS
#include "CircularBuffer.hpp"


//delay 1.7 - 5 ms

class SchroederAllPass{
    CircularBuffer CB{44100};
    float delayLength, g;
	
public:
    SchroederAllPass(float inValue, float inG);
        
    void process(float* samples, int bufferSize);
    
    float processSingleSample(float sample);
    
    void setFeedback(float inValue);
    
    float getFeedback();
    
    void setDelayLength(float inValue);
    
    float getDelayLength();
};

#endif /* SchroederAllPass_hpp */
