#pragma once
#include "singleton.h"
class SoundManager :
    public singleton<SoundManager>
{
public:
    map<string, CSound*> soundMap;
    CSoundManager* manager;
    
    SoundManager();
    virtual ~SoundManager();
    void AddSound(string key, wstring path);
    void Play(string key, bool isLoop = false);
    void Copy(string key, long volume = -1000, long pan = 0);
    void Stop(string key);

};

#define SOUND SoundManager::GetInstance()