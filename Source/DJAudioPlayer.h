/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 6 Aug 2021 9:29:35pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource {
    public:
        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();
        
    //==============================================================================
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

    //==============================================================================
   
        void loadURL(juce::URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);
    
        void setBass(double gain);
        void setMid(double gain);
        void setTreble(double gain);
    
        void start();
        void stop();
        
        /** Get the relative position of the playhead */
        double getPositionRelative();
        
        bool readyToPlay();
        
    
    private:
        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        
        juce::AudioTransportSource transportSource;
        juce::IIRFilterAudioSource bassSource{&transportSource, false};
        juce::IIRFilterAudioSource trebleSource{&bassSource, false};
        juce::IIRFilterAudioSource midSource{&trebleSource, false};
    
        juce::ResamplingAudioSource resampleSource{&midSource, false, 2};
        bool loaded = false;
    
        double sampleRate;
        const int bassCutOff = 250;
        const int midCutOff = 3000;
        const int trebleCutOff = 8000;
};
