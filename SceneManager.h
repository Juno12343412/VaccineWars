#pragma once
#include "singleton.h"
#include "Scene.h"


class SceneManager :
    public singleton<SceneManager>
{
public:
    SceneManager();
    virtual ~SceneManager();
    Scene* nowScene;
    Scene* nextScene;
    map<string, Scene*> sceneMap;

    Scene* AddScene(const string& key, Scene* scenePtr);
    Scene* ChageScene(const string& key);

    void Update();
    void Render();
    void Release();
};

#define SCENE SceneManager::GetInstance()