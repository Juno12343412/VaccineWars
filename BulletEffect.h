#pragma once
#include "Object.h"
class BulletEffect :
    public Object
{
public:
    BulletEffect(float size,int r, int g, int b);
    virtual ~BulletEffect();

    float size = 0;
    int alpha = 255;
    
    int r = 255, g = 255, b =255;

    // Object을(를) 통해 상속됨
    virtual void Init() override;

    virtual void Update() override;

    virtual void Render() override;

    virtual void Release() override;

};

