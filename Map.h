#pragma once
#include "Object.h"
class Map :
    public Object
{
public:
    Map(int num);
    virtual ~Map();

    texture* img;
    texture* img2;
    texture* img3;
    texture* img4;
    int num = 0;

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

