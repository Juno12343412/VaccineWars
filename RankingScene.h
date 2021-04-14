#pragma once
#include "Scene.h"
class RankingScene :
    public Scene
{
public:

    texture* img;
    wstring ch = L"";
    int result = 0;
    int resultW = 0;
    int rank = 1;
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

