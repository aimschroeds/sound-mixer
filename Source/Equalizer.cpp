/*
  ==============================================================================

    Equalizer.cpp
    Created: 28 Aug 2021 9:37:35pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Equalizer.h"

//==============================================================================
Equalizer::Equalizer(DJAudioPlayer* _player): player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    boomBoxImage.setImage(juce::ImageCache::getFromMemory(BinaryData::boom3_png, (size_t)BinaryData::boom3_pngSize));
    boomBoxImage.setImagePlacement(juce::RectanglePlacement(juce::RectanglePlacement::onlyReduceInSize));
    addAndMakeVisible(boomBoxImage);
    
    bassSlider.setSliderStyle (juce::Slider::LinearVertical);
    addAndMakeVisible(bassSlider);
    bassSlider.addListener(this);
    bassSlider.setRange(0.0, 2.0);
    bassSlider.setValue(1.0);
    bassSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    addAndMakeVisible (bassLabel);
    bassLabel.setText ("Bass", juce::dontSendNotification);
    bassLabel.attachToComponent (&bassSlider, false);
    bassLabel.setJustificationType (juce::Justification::centredBottom);
    bassLabel.setMinimumHorizontalScale(0.2);
    
    midSlider.setSliderStyle (juce::Slider::LinearVertical);
    addAndMakeVisible(midSlider);
    midSlider.addListener(this);
    midSlider.setRange(0.0, 2.0);
    midSlider.setValue(1.0);
    midSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    addAndMakeVisible (midLabel);
    midLabel.setText ("Mid", juce::dontSendNotification);
    midLabel.attachToComponent (&midSlider, false);
    midLabel.setJustificationType (juce::Justification::centredBottom);
    midLabel.setMinimumHorizontalScale(0.2);
    
    trebleSlider.setSliderStyle (juce::Slider::LinearVertical);
    addAndMakeVisible(trebleSlider);
    trebleSlider.addListener(this);
    trebleSlider.setRange(0.0, 2.0);
    trebleSlider.setValue(1.0);
    trebleSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    
    
    addAndMakeVisible (trebleLabel);
    trebleLabel.setText ("Treb", juce::dontSendNotification);
    trebleLabel.attachToComponent (&trebleSlider, false);
    trebleLabel.setJustificationType (juce::Justification::centredBottom);
    trebleLabel.setMinimumHorizontalScale(0.2);
}

Equalizer::~Equalizer()
{
}

void Equalizer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//    g.fillAll (juce::Colour (113, 227, 185));
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//    auto boomImageWidth = getHeight() * (512 / 384);
//    auto boomImageHeight = getHeight();
//    g.drawImage(boomboxImage, 0, 0, boomImageWidth , boomImageHeight ,0, 0, 512, 384, false);
//    g.drawImage(boomboxImage, 0, 0, 175, 131.25 ,0, 0, 512, 384, false);
//    g.drawImage(boomboxImage, getLocalBounds().toFloat());
//    g.drawImageWithin(boomboxImage, 0, 0, 45, 36, getBounds());
}

void Equalizer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const int cols = 7;
    boomBoxImage.setBounds (getLocalBounds ());
    bassSlider.setBounds(getWidth() / cols * 2, getHeight() * 0.35, getWidth() / cols, getHeight() * 0.6);
    midSlider.setBounds(getWidth() / cols * 3, getHeight() * 0.35, getWidth() / cols, getHeight() * 0.6);
    trebleSlider.setBounds(getWidth() / cols * 4, getHeight() * 0.35, getWidth() / cols, getHeight() * 0.6);
}


void Equalizer::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &bassSlider)
    {
        player->setBass(slider->getValue());
    }
    
    else if (slider == &midSlider)
    {
        player->setMid(slider->getValue());
    }
    
    else if (slider == &trebleSlider)
    {
        player->setTreble(slider->getValue());
    }
}
