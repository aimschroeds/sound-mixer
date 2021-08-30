/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 7 Aug 2021 4:43:54pm
    Author:  Aimee Schroeder

  ==============================================================================
*/


#include "PlaylistComponent.h"
#include "SearchComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
//    trackTitles.push_back("Track 1");
//    trackTitles.push_back("Track 2");
//    trackTitles.push_back("Track 3");
//    trackTitles.push_back("Track 4");
//    trackTitles.push_back("Track 5");
    tableComponent.getHeader().addColumn("Track title", 1, 600);
    tableComponent.getHeader().addColumn("Duration", 2, 300);
    tableComponent.getHeader().addColumn("", 3, 300);
    
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(search);
    addAndMakeVisible(tableComponent);
    
    search.addChangeListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    search.setBounds(0, 0, getWidth(), 20);
    tableComponent.setBounds(0, 20 , getWidth(), getHeight() - 20);
}

int PlaylistComponent::getNumRows()
{
    if (searchResults.empty())
    {
        return tracks.size();
    }
    else
    {
        return searchResults.size();
    }
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else
    {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (!searchResults.empty())
    {
        if (auto *rowElement = searchResults[rowNumber])
        {
            if (columnId == 1)
            {
                g.drawText(rowElement->filename, 2, 0, width - 4, height, juce::Justification::centredLeft);
            }
            else if (columnId == 2)
            {
                g.drawText(rowElement->duration, 2, 0, width - 4, height, juce::Justification::centredLeft);
            }
            
        }
    }
    else
    {
        //    from: https://docs.juce.com/master/tutorial_table_list_box.html
            if (auto *rowElement = tracks[rowNumber])
            {
                if (columnId == 1)
                {
                    g.drawText(rowElement->filename, 2, 0, width - 4, height, juce::Justification::centredLeft);
                }
                else if (columnId == 2)
                {
                    g.drawText(rowElement->duration, 2, 0, width - 4, height, juce::Justification::centredLeft);
                }
                
            }
    }

    
}

juce::Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    juce::Component *existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if(existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"play"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
            
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "PlaylistComponent::buttonClicked: " << tracks[id]->filename << std::endl;
}


void PlaylistComponent::openFileChooser()
{
    juce::FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen())
    {
        tracks.push_back(new Track(juce::URL{chooser.getResult()}));
        tableComponent.updateContent(); 
//        player->loadURL(juce::URL{chooser.getResult()});
//        waveformDisplay.loadURL(juce::URL{chooser.getResult()});
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "PlaylistComponent::isInterestedInFileDrag" << std::endl;
    return true;
}


void PlaylistComponent::filesDropped (const juce::StringArray &files, int x, int y)
{
//    TO DO check if file is appropriate
    std::cout << "PlaylistComponent::filesDropped" << std::endl;
    for (juce::String filename : files)
    {
        
        tracks.push_back(new Track(juce::URL{juce::File{filename}}));
        tableComponent.updateContent();
//        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}


void PlaylistComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    
    if (source == &search)
    {
        searchTracks(search.getKeyword());
    }
}

void PlaylistComponent::searchTracks(juce::String keyword)
{
    searchResults.clear();
    for (auto& t : tracks)
    {
        if (t->filename.contains(keyword))
        {
            searchResults.push_back(t);
            
        }
    }
    tableComponent.updateContent();
}
