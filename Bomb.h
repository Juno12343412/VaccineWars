#pragma once
#include "Object.h"
class Bomb :
    public Object
{
    CMeshLoader* mesh;
    Timer* boom;
    int time = 0;
    bool isBoom = false;
    // Object을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    float radius = 50;
};

