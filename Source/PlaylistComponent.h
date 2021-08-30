/*
  ==============================================================================

    PlaylistComponent.h
    Created: 7 Aug 2021 4:43:54pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "Track.h"
#include "SearchComponent.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                        public juce::TableListBoxModel,
                        public juce::Button::Listener,
                        public juce::FileDragAndDropTarget,
                        public::juce::ChangeListener, public::juce::ChangeBroadcaster,
                        public::juce::DragAndDropContainer
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    void paintRowBackground (juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    juce::Component* refreshComponentForCell (int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        juce::Component *existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    juce::var getDragSourceDescription(const juce::SparseSet< int > &currentlySelectedRows) override;
    
private:
    juce::TableListBox tableComponent;
    SearchComponent search;
    std::vector<Track*> tracks;
    std::vector<Track*> searchResults;
    void searchTracks(juce::String keyword);
    void openFileChooser();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
