/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    addAndMakeVisible (text);
    
    text.setMultiLine (true);
    
    File f = File::getSpecialLocation (File::userDesktopDirectory);
    watcher.addFolder (f);
    watcher.addListener (this);
    
    folderChanged (f);
    
    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics&)
{
}

void MainContentComponent::resized()
{
    text.setBounds (getLocalBounds());
}

void MainContentComponent::folderChanged (File f)
{
    Array<File> files;
    f.findChildFiles (files, File::findFiles, false);
    
    text.clear();
    
    String txt;
    for (auto ff : files)
        txt += ff.getFileName() + "\n";
    
    text.setText (txt);
}
