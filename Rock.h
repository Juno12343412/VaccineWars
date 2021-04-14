#pragma once
#include "Object.h"
class Rock :
    public Object
{
public:
    Rock(int num);
    virtual ~Rock();
    texture* img;
    int num;
    int sizeX, sizeY = 0;
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

