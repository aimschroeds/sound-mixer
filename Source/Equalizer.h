/*
  ==============================================================================

    Equalizer.h
    Created: 28 Aug 2021 9:37:35pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "Skin.h"

//==============================================================================
/*
*/
class Equalizer  : public juce::Component,
                    public juce::Slider::Listener
{
public:
    Equalizer(DJAudioPlayer* _player);
    ~Equalizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement Slider::Listener */
    void sliderValueChanged(juce::Slider *slider) override;

private:
    DJAudioPlayer* player;
    
    juce::Slider bassSlider;
    juce::Slider trebleSlider;
    juce::Slider midSlider;
    
    juce::Label bassLabel;
    juce::Label trebleLabel;
    juce::Label midLabel;
    
    juce::ImageComponent boomBoxImage;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Equalizer)
};
