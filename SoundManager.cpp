#include "DXUT.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	manager = new CSoundManager;
	manager->Initialize(DXUTGetHWND(), 2);
}

SoundManager::~SoundManager()
{
	for (auto iter : soundMap)
	{
		SAFE_DELETE(iter.second);
	}
	soundMap.clear();
	SAFE_DELETE(manager);
}

void SoundManager::AddSound(string key, wstring path)
{
	auto find = soundMap.find(key);
	if (find != soundMap.end()) return;
	CSound* sound;
	manager->Create(&sound, (LPWSTR)path.c_str(), DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN);
	soundMap[key] = sound;
}

void SoundManager::Play(string key, bool isLoop)
{
	auto find = soundMap.find(key);
	if (find == soundMap.end()) return;
	find->second->Play(0, isLoop);
}

void SoundManager::Copy(string key, long volume, long pan)
{
	auto find = soundMap.find(key);
	if (find == soundMap.end()) return;
	LPDIRECTSOUNDBUFFER buff;
	manager->GetDirectSound()->DuplicateSoundBuffer(find->second->GetBuffer(0), &buff);
	buff->SetCurrentPosition(0);
	buff->SetVolume(volume);
	buff->SetPan(pan);
	buff->Play(0, 0, 0);
}

void SoundManager::Stop(string key)
{
	auto find = soundMap.find(key);
	if (find == soundMap.end()) return;
	find->second->Stop();
}
