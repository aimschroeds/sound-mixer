/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 6 Aug 2021 9:29:35pm
    Author:  Aimee Schroeder
    Credits: https://electronicmusic.fandom.com/wiki/Filter
 https://www.teachmeaudio.com/mixing/techniques/audio-spectrum

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
                            : formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer()
{
    
}


void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double _sampleRate)
{
    sampleRate = _sampleRate;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    
    bassSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    trebleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    midSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    bassSource.setCoefficients(juce::IIRCoefficients::makeLowShelf(sampleRate, bassCutOff, 1, 1));
    midSource.setCoefficients(juce::IIRCoefficients::makePeakFilter(sampleRate, midCutOff, 1, 1));
    trebleSource.setCoefficients(juce::IIRCoefficients::makeHighShelf(sampleRate, trebleCutOff, 1, 1));
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}


void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    resampleSource.getNextAudioBlock(bufferToFill);
}


void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    bassSource.releaseResources();
    trebleSource.releaseResources();
    midSource.releaseResources();
    resampleSource.releaseResources();
}

//==============================================================================

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource( new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0 , nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        loaded = true;
    }
    else
    {
    std::cout << "Something went wrong loading the file " << std::endl;
    }
}


void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0.0 || gain > 5.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 5" << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
    
}


void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 2.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}


void DJAudioPlayer::setBass(double gain)
{
    if (gain < 0.0 || gain > 2.0)
    {
        std::cout << "DJAudioPlayer::setBass gain should be between 0 and 2" << std::endl;
    }
    else
    {
        bassSource.setCoefficients(juce::IIRCoefficients::makeLowShelf(sampleRate, bassCutOff, 1, gain));
    }
}


void DJAudioPlayer::setMid(double gain)
{
    if (gain < 0.0 || gain > 2.0)
    {
        std::cout << "DJAudioPlayer::setMid gain should be between 0 and 2" << std::endl;
    }
    else
    {
        midSource.setCoefficients(juce::IIRCoefficients::makePeakFilter(sampleRate, midCutOff, 1, gain));
    }
}


void DJAudioPlayer::setTreble(double gain)
{
    if (gain < 0.0 || gain > 2.0)
    {
        std::cout << "DJAudioPlayer::setTreble gain should be between 0 and 2" << std::endl;
    }
    else
    {
        trebleSource.setCoefficients(juce::IIRCoefficients::makeHighShelf(sampleRate, trebleCutOff, 1, gain));
    }
}


void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}


void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}


bool DJAudioPlayer::readyToPlay()
{
    return loaded;
}
