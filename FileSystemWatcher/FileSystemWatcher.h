/*
  ==============================================================================

    FileSystemWatcher.h
    Created: 13 Jan 2018 10:31:15pm
    Author:  Roland Rabien

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FileSystemWatcher : public ChangeBroadcaster
{
public:
    FileSystemWatcher();
    ~FileSystemWatcher();
    
    void addFolder (const File& folder);
    void removeFolder (const File& folder);
    
    class Listener
    {
    public:
        virtual ~Listener()  {}

        virtual void folderChanged (const File)    {}
    };
    
    void addListener (Listener* newListener);

    void removeListener (Listener* listener);
    
private:
    class Impl;
    
    void folderChanged (const File& folder);
    
    ListenerList<Listener> listeners;
    
    OwnedArray<Impl> watched;
};
