/*
  ==============================================================================

    Track.cpp
    Created: 29 Aug 2021 1:25:24pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#include "Track.h"
#include <string>
#include <stdio.h>

Track::Track(juce::URL _audioURL) : trackUrl(_audioURL)
{
    filename = trackUrl.getFileName();
    setDuration();
}

Track::~Track()
{
    
}

void Track::setDuration()
{
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    double durationSecondsTotal;
    juce::AudioTransportSource transportSource;
    
    formatManager.registerBasicFormats();
    auto* reader = formatManager.createReaderFor(trackUrl.createInputStream(false));
    
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource( new juce::AudioFormatReaderSource(reader, true));
        
        transportSource.setSource(newSource.get(), 0 , nullptr, reader->sampleRate);
        
        readerSource.reset(newSource.release());
        
        durationSecondsTotal = transportSource.getLengthInSeconds();
        
    }
    else
    {
    std::cout << "Something went wrong getting duration " << std::endl;
       durationSecondsTotal = 0;
    }
    int durationMinutesComponent = durationSecondsTotal / 60;
    int durationSecondsComponent = (int)durationSecondsTotal % 60;

    sprintf(duration, "%02d:%02d", durationMinutesComponent, durationSecondsComponent);
    
}
