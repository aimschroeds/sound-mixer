#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1200, 800);
    setLookAndFeel (&skin);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    setLookAndFeel (nullptr);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

//void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    if (!playing)
//    {
//        // Right now we are not producing any data, in which case we need to clear the buffer
//        // (to prevent the output of random noise)
//        bufferToFill.clearActiveBufferRegion();
//        return;
//    }
//    auto* leftChan = bufferToFill.buffer->getWritePointer(0,
//                                                          bufferToFill.startSample);
//    auto* rightChan = bufferToFill.buffer->getWritePointer(1,
//                                                          bufferToFill.startSample);
//
//    for (auto i = 0; i < bufferToFill.numSamples; ++i)
//    {
////        double sample = rand.nextDouble() * 0.25; // Random tone
////        double sample = fmod(phase, 0.2); // Saw tooth wave form
//        double sample = sin(phase) * 0.1;   // Sin tone
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//        phase += dphase;
//    }
//    // Your audio-processing code goes here!
//
//    // For more details, see the help for AudioProcessor::getNextAudioBlock()
//
//
//}
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
   mixerSource.getNextAudioBlock(bufferToFill);

}
    

void MainComponent::releaseResources()
{
    
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colour (113, 227, 185));

    // You can add your drawing code here!
    
    g.setFont (20.0f);
//    g.drawText ("Hello from Amsterdam", getLocalBounds(),
//                juce::Justification::centred, true);
    juce::Image headerLogo = juce::ImageCache::getFromMemory(BinaryData::Group_1_png, (size_t)BinaryData::Group_1_pngSize);
    g.drawImageAt(headerLogo, getWidth() / 2 - 116, 0, 0);
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    deckGUI1.setBounds(0, 94, getWidth() / 2, getHeight() * 0.7);
    deckGUI2.setBounds(getWidth() / 2, 94, getWidth() / 2, getHeight() * 0.7);
    playlistComponent.setBounds(0, getHeight() * 0.7 + 94, getWidth(), getHeight() * 0.3);
    
}


