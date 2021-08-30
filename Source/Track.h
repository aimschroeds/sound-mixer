/*
  ==============================================================================

    Track.h
    Created: 29 Aug 2021 1:25:24pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once
#include <string>
#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class Track
{
    public :
        Track (juce::URL _audioURL);
        ~Track();
        juce::String filename;
        char duration[6];
        juce::URL trackUrl;
        
    private:
        void setDuration();
};
