/*
  ==============================================================================

    FileSystemWatcher.cpp
    Created: 13 Jan 2018 10:31:15pm
    Author:  Roland Rabien

  ==============================================================================
*/

#ifdef  _WIN32
#include <Windows.h>
#endif 

#include "FileSystemWatcher.h"

#ifdef _WIN32
class FileSystemWatcher::Impl : public Thread,
                                private AsyncUpdater
{
public:
    Impl (FileSystemWatcher& o, File f) 
      : Thread ("FileSystemWatcher::Impl"), owner (o), folder (f)
    {
        WCHAR path[_MAX_PATH] = {0};
        wcsncpy (path, folder.getFullPathName().toWideCharPointer(), _MAX_PATH - 1);

        handleFile = FindFirstChangeNotificationW (path, FALSE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
                                                   FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE);

        handleExit = CreateEvent (NULL, FALSE, FALSE, NULL);
        
        startThread();
    }

    ~Impl()
    {
        SetEvent (handleExit);
        stopThread (1000);

        CloseHandle (handleExit);

        if (handleFile != INVALID_HANDLE_VALUE)
            FindCloseChangeNotification (handleFile);
    }

    void run() override
    {
        while (true)
        {
            HANDLE handles[] = { handleFile, handleExit };
            DWORD res = WaitForMultipleObjects (2, handles, FALSE, INFINITE);
            
            if (threadShouldExit())
                break;

            if (res == WAIT_OBJECT_0 + 0)
            {
                triggerAsyncUpdate();

                FindNextChangeNotification (handleFile);
            }
            else if (res == WAIT_OBJECT_0 + 1)
            {
                break;
            }
        }
    }

    void handleAsyncUpdate() override
    {
        owner.folderChanged (folder);
    }

    FileSystemWatcher& owner;
    File folder;

    HANDLE handleFile, handleExit;

};

FileSystemWatcher::FileSystemWatcher()
{
}

FileSystemWatcher::~FileSystemWatcher()
{
}

void FileSystemWatcher::addFolder (const File& folder)
{
    watched.add (new Impl (*this, folder));
}

void FileSystemWatcher::removeFolder (const File& folder)
{
    for (int i = 0; --i >= 0;)
    {
        if (watched[i]->folder == folder)
        {
            watched.remove (i);
            break;
        }
    }
}
#endif

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
    listeners.call (&FileSystemWatcher::Listener::folderChanged, folder);
}

