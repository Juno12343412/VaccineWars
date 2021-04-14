#pragma once
#include "Scene.h"
class IntroScene :
    public Scene
{
public:
    IntroScene(int num);
    virtual ~IntroScene();
    bool sceneStart = true;
    int num;
    list<texture*> introList;
    float size = 0;
    float maxSize = 1920;
    Timer* delay;
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    void AddIntro(texture* texture);
};

