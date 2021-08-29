/*
  ==============================================================================

    SearchComponent.cpp
    Created: 29 Aug 2021 4:51:51pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchComponent.h"

//==============================================================================
SearchComponent::SearchComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible(input);
    input.setTextToShowWhenEmpty("Search", juce::Colour (0, 0, 0));
    input.addListener(this);
}

SearchComponent::~SearchComponent()
{
    input.removeListener(this);
    deleteAllChildren();
}

void SearchComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//    g.fillAll (juce::Colours::darkgrey);   // clear the background

//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("SearchComponent", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
}

void SearchComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    input.setBounds (0.05 * getHeight(), 0, 300, getHeight() * 0.9);
}


void SearchComponent::textEditorTextChanged(juce::TextEditor &editor)
{
    std::cout << "SearchComponent::textEditorTextChanged - " << input.getText() << std::endl;
    sendChangeMessage();
}


