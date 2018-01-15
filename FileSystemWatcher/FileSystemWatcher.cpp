/*
  ==============================================================================

    FileSystemWatcher.cpp
    Created: 13 Jan 2018 10:31:15pm
    Author:  Roland Rabien

  ==============================================================================
*/

#include "FileSystemWatcher.h"

void FileSystemWatcher::addListener (Listener* newListener)
{
    listeners.add (newListener);
}

void FileSystemWatcher::removeListener (Listener* listener)
{
    listeners.remove (listener);
}

void FileSystemWatcher::folderChanged (const File& folder)
{
    listeners.call ([folder] (Listener& l) { l.folderChanged (folder); });
}

