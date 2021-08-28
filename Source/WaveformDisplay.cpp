/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 6 Aug 2021 11:36:02pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                                 juce::AudioThumbnailCache & cacheToUse) :
                                    audioThumb(1000, formatManagerToUse, cacheToUse),
                                    fileLoaded(false),
                                    position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

//    g.setColour (green);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    auto withMargin = getLocalBounds().reduced(8, 0);
    g.setColour (pink);
    std::cout << "width audioThumbnail" << getWidth() << std::endl;
    if(fileLoaded)
    {
        audioThumb.drawChannel(g,
                          withMargin,
                          0,
                          audioThumb.getTotalLength(),
                          0,
                          1);
        g.setColour(blue);
        g.drawRect(4 + position * withMargin.getWidth(), 0, 0.025 * withMargin.getWidth(), getHeight(), 2);
    }
    else
    {
        g.setFont (20.0f);
        g.drawText ("File not yet loaded", getLocalBounds(),
                    juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void WaveformDisplay::loadURL(juce::URL audioURL)
{
    std::cout << "WaveformDisplay::loadURL" << std::endl;
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
}


void WaveformDisplay::changeListenerCallback (juce::ChangeBroadcaster *source)
{
    std::cout << "WaveformDisplay::changeListenerCallback" << std::endl;
    repaint();
}


void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}
