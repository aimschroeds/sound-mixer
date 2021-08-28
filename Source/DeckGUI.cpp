/*
  ==============================================================================

    DeckGUI.cpp
    Created: 6 Aug 2021 10:23:14pm
    Author:  Aimee Schroeder
    Credits
    Logo: Headphone by DinosoftLab from the Noun Project
    Logo: Headphones by Atif Arshad from the Noun Project
    
    play by Matthew Brinkley from the Noun Project
    Stop by Matthew Brinkley from the Noun Project
    pause by Matthew Brinkley from the Noun Project
    Boom Box by DinosoftLab from the Noun Project
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
    
    // TO DO: Fix labels: https://docs.juce.com/master/tutorial_slider_values.html
    
    
    // TO DO: Change look and feel of buttons and sliders: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
    
    volSlider.setSliderStyle (juce::Slider::Rotary);
    speedSlider.setSliderStyle (juce::Slider::Rotary);
    posSlider.setSliderStyle (juce::Slider::ThreeValueHorizontal);
    // TO DO: Trigger callback if min or max is changed; to start or end playback at according point
    posSlider.setMinValue(0);
    posSlider.setMaxValue(1.0);
    
    posSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    volSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    speedSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    // STRETCH TO DO: Animate something: https://docs.juce.com/master/tutorial_animation.html
    
    auto stopIcon = juce::Drawable::createFromImageData(BinaryData::stop_svg, BinaryData::stop_svgSize);
    auto playIcon = juce::Drawable::createFromImageData(BinaryData::play_svg, BinaryData::play_svgSize);
    auto pauseIcon = juce::Drawable::createFromImageData(BinaryData::pause_svg, BinaryData::pause_svgSize);
    
    stopButton.setImages(stopIcon.get());
    playButton.setImages(playIcon.get());
    pauseButton.setImages(pauseIcon.get());
    
    addAndMakeVisible(stopButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(pauseButton);
    
    addAndMakeVisible(loadButton);
//    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(powerToggle);
    
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(equalizer);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    pauseButton.addListener(this);
    loadButton.onClick = [this] { openFileChooser(); };
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 5.0);
    volSlider.setValue(1.0);
    speedSlider.setRange(0.0, 2.0);
    speedSlider.setValue(1.0);
    posSlider.setRange(0.0, 1.0);
    
    
    addAndMakeVisible (volLabel);
    volLabel.setText ("Volume", juce::dontSendNotification);
    volLabel.attachToComponent (&volSlider, false);
    volLabel.setJustificationType (juce::Justification::centredBottom);
    
    addAndMakeVisible (speedLabel);
    speedLabel.setText ("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent (&speedSlider, false);
    speedLabel.setJustificationType (juce::Justification::centredBottom);
    
    
    addAndMakeVisible (posLabel);
    posLabel.setText ("Playback", juce::dontSendNotification);
    posLabel.attachToComponent (&posSlider, false);
    posLabel.setJustificationType (juce::Justification::centredBottom);
    
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
    double rowH = getHeight() / 18;
    
    
    
//    dial2.setBounds (dialArea.reduced (border));
//
//    auto buttonHeight = 30;
//
//    button1.setBounds (area.removeFromTop (buttonHeight).reduced (border));
//    button2.setBounds (area.removeFromTop (buttonHeight).reduced (border));
    
    // This method is where you should set the bounds of any child
    // components that your component contains..
    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 4);
    posSlider.setBounds(0, rowH * 5 , getWidth(), rowH);
    equalizer.setBounds(getWidth() * 0.05, rowH * 6, getWidth() * 0.3, rowH * 5);
    playButton.setBounds(getWidth() * 0.4, rowH * 7 , getWidth() / 6, rowH * 3);
    pauseButton.setBounds(getWidth() * 0.6, rowH * 7 , getWidth() / 6, rowH * 3);
    stopButton.setBounds(getWidth() * 0.8, rowH * 7 , getWidth() / 6, rowH * 3);
    
    
    volSlider.setBounds(10, rowH * 12, getWidth() / 2, rowH * 5);
    speedSlider.setBounds(getWidth() / 2 - 10, rowH * 12, getWidth() / 2, rowH * 5);

    loadButton.setBounds(0, rowH * 17, getWidth(), rowH * 1);

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
        player->setPositionRelative(0);
    }
    else if (button == &pauseButton)
    {
        std::cout << "Pause button was clicked " << std::endl;
        player->stop();
        
    }
}


void DeckGUI::openFileChooser()
{
    juce::FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen())
    {
        player->loadURL(juce::URL{chooser.getResult()});
        waveformDisplay.loadURL(juce::URL{chooser.getResult()});
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
        if (slider->getMinValue() > slider->getValue())
        {
            std::cout << "min " <<std::endl;
            slider->setValue(slider->getMinValue());
            
        }
        else if (slider->getMaxValue() < slider->getValue())
        {
            std::cout << "max " <<std::endl;
            slider->setValue(slider->getMaxValue());
            
        }
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
    if (player->readyToPlay())
    {
        instructPlayer(&posSlider);
        posSlider.setValue(player->getPositionRelative());
    }
    
}

void DeckGUI::instructPlayer(juce::Slider* slider)
{
    if (slider->getMinValue() > player->getPositionRelative())
    {
        std::cout << "min " <<std::endl;
        slider->setValue(slider->getMinValue());
        player->setPositionRelative(slider->getMinValue());
        
    }
    else if (slider->getMaxValue() < player->getPositionRelative())
    {
        std::cout << "max " <<std::endl;
        slider->setValue(slider->getMaxValue());
        player->setPositionRelative(slider->getMaxValue());
        player->stop();
    }
    
}
