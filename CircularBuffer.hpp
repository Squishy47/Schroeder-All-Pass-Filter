//
//  CircularBuffer.hpp
//  CircularBuffer - All
//
//  Created by Sam on 14/02/2018.
//

#ifndef CircularBuffer_hpp
#define CircularBuffer_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>

typedef std::vector<float> Vec_Float;

class CircularBuffer{
    Vec_Float buffer;
    int bufferLength;
    int tail = 0;
    int head = 0;
    
public:
    CircularBuffer(float inValue);
    
    float read(float numElementsToRead, std::string);
    
    void write(float inValue);
    
    float interpCalcAmount(float inValue, std::string);

    float cubicInterpolation(double y0, double y1, double y2, double y3, double mu0);
    
    float getSample(float inValue);
        
    void setBufferLength(float inValue);
    
    int getBufferLength();
};

#endif /* CircularBuffer_hpp */

