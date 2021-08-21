/*
  ==============================================================================

    DeckGUI.cpp
    Created: 6 Aug 2021 10:23:14pm
    Author:  Aimee Schroeder
    Headphone by DinosoftLab from the Noun Project
    Headphones by Atif Arshad from the Noun Project
  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse
                 ) : player(_player),
                        waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    // TO DO: Add labels: https://docs.juce.com/master/tutorial_slider_values.html
    
    // TO DO: Change look and feel of buttons and sliders: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
    
    // STRETCH TO DO: Animate something: https://docs.juce.com/master/tutorial_animation.html
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(powerToggle);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(100);
    
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId)); // clear the background
}
//{
//    /* This demo code just fills the component's background and
//       draws some placeholder text to get you started.
//
//       You should replace everything in this method with your own
//       drawing code..
//    */
//
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("DeckGUI", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
//}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 10;
    playButton.setBounds(0, 0 , getWidth() / 2, rowH);
    stopButton.setBounds(0, rowH , getWidth() / 2, rowH);
    
    volSlider.setBounds(0, rowH * 3 , getWidth() / 2, rowH);
    speedSlider.setBounds(0, rowH * 4 , getWidth() / 2, rowH);
    posSlider.setBounds(0, rowH * 5 , getWidth() / 2, rowH);
    waveformDisplay.setBounds(0, rowH * 6 , getWidth() / 2, rowH * 2);
    powerToggle.setBounds(0, rowH * 9, getWidth() / 2, rowH);
    loadButton.setBounds(0, rowH * 8, getWidth() / 2, rowH);

}


void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
        
    }
    else if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
        
    }
    // TO DO: Distinguish stop vs pause buttons
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{chooser.getResult()});
            waveformDisplay.loadURL(juce::URL{chooser.getResult()});
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
//        dphase = volSlider.getValue() * 0.01;       // frequency control
        player->setGain(slider->getValue());
    }


    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }


    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

}


bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}


void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
//    TO DO check if file is appropriate
    std::cout << "DeckGUI::filesDropped" << std::endl;
    for (juce::String filename : files)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}


void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
