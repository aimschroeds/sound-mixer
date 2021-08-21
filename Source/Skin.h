/*
  ==============================================================================

    Skin.h
    Created: 21 Aug 2021 3:40:00pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Skin : public juce::LookAndFeel_V4
{
public:
    Skin();

//    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
//                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
//    {
//        auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
//        auto centreX = (float) x + (float) width  * 0.5f;
//        auto centreY = (float) y + (float) height * 0.5f;
//        auto rx = centreX - radius;
//        auto ry = centreY - radius;
//        auto rw = radius * 2.0f;
//        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//        // fill
//        g.setColour (juce::Colours::orange);
//        g.fillEllipse (rx, ry, rw, rw);
//
//        // outline
//        g.setColour (juce::Colours::red);
//        g.drawEllipse (rx, ry, rw, rw, 1.0f);
//
//        juce::Path p;
//        auto pointerLength = radius * 0.33f;
//        auto pointerThickness = 2.0f;
//        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
//        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
//
//        // pointer
//        g.setColour (juce::Colours::yellow);
//        g.fillPath (p);
//    }
private:
//    juce::Colour(113, 227, 185) green;
    juce::Colour green = juce::Colour (113, 227, 185);
    juce::Colour black = juce::Colour (0, 0, 0);
    juce::Colour blue = juce::Colour (163, 223, 230);
    juce::Colour peach = juce::Colour (250, 172, 138);
    juce::Colour pink = juce::Colour (250, 170, 165);
};
