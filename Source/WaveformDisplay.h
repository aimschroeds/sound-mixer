/*
  ==============================================================================

    WaveformDisplay.h
    Created: 6 Aug 2021 11:36:02pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener
{
public:
    WaveformDisplay( juce::AudioFormatManager & formatManagerToUse,
                     juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback (juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);
    /** Set the relative position of the playhead */
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;
    
    juce::Colour green = juce::Colour (113, 227, 185);
    juce::Colour black = juce::Colour (0, 0, 0);
    juce::Colour blue = juce::Colour (163, 223, 230);
    juce::Colour peach = juce::Colour (250, 172, 138);
    juce::Colour pink = juce::Colour (250, 170, 165);
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
