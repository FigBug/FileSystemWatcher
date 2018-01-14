/*
  ==============================================================================

    FileSystemWatcher.h
    Created: 13 Jan 2018 10:31:15pm
    Author:  Roland Rabien

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FileSystemWatch : public ChangeBroadcaster
{
public:
    FileSystemWatcher();
    
    void addFolder (const File& folder);
    void removeFolder (const File& folder);
};
