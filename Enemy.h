#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
    Enemy(int num);
    virtual ~Enemy();
    int num, num2;
    texture* img;
    Vector3 moveDir = { 1,0,1 };
    Vector3 nextMoveDir = { 1,0,1 };
    float imgSize;
    float size = 15;
    float maxSize = 15;
    int speed;
    int plusSpeed = 1;
    float bodyRot = 0;
    float myY = 0;
    float plusSize = 0;
    int alpha = 255;
    bool alphaUp = false;
    bool bossWin = false;
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

