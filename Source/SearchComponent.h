/*
  ==============================================================================

    SearchComponent.h
    Created: 29 Aug 2021 4:51:51pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SearchComponent  : public juce::Component
{
public:
    SearchComponent();
    ~SearchComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextEditor input{"Search"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchComponent)
};
