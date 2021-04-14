#pragma once
#include "Object.h"
class Effect :
    public Object
{
public:
    Effect(int num, float size = 0);
    virtual ~Effect();
    VECtexture* aniImg;
    texture* img;
    texture* img2;
    texture* str;
    texture* str2;
    Timer* aniT;
    
    float size;
    float aniF = 0;
    int aniMaxF = 0;
    int num;
    int alpha = 0;
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};