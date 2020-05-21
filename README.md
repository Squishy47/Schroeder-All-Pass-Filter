# Schroeder-All-Pass-Filter
Basic Implimentation of a Schroeder All-Pass Filter

Initialisation
Create a new instance of the filter for every channel of audio data you wish to process. 

The first constructor value is the delay length of the filter, the second is the feedback gain of the filter.

    SchroederAllPass ap{10, 0.707};

To process a block of samples at once call the process function with:
  1: a pointer to where the audio data is stored.
  2: the size of the audio block/buffer.
  
    ap.process(audioDataPointer, bufferSize);
    
processSingleSample(audioData) will return a single processed sample. pass in the each element of the data you want processed.

    audioData[i] = ap.processSingleSample(audioData[i]);
    
    
To change the filter feedback gain, call setFeedback(), with a float between 0.0 and 1.0;

    ap.setFeedback(0.707);
    
To Change the delay length of the filter, call setDelayLength(), with a float between 1.0 and beyond...

    ap.setDelayLength(100);
    
getFeedback() and getDelayLength() return float values for the respective values.    
