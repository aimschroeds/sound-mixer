/*
  ==============================================================================

    DeckGUI.h
    Created: 6 Aug 2021 10:23:14pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Skin.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* _player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement Button::Listener */
    void buttonClicked(juce::Button* button) override;
    
    /** Implement Slider::Listener */
    void sliderValueChanged(juce::Slider *slider) override;
    
    /** Implement Timer::timerCallback*/
    void timerCallback() override;
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    
private:
    juce::TextButton playButton{"Play"};
    juce::TextButton stopButton{"Stop"};
    juce::TextButton loadButton{"Load"};
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    juce::ToggleButton powerToggle{"On"};
    
    juce::Label volLabel;
    juce::Label posLabel;
    
    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
