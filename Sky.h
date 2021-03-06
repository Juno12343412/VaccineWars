#pragma once
#include "Object.h"
class Sky :
    public Object
{
public:
    Sky(int num);
    virtual ~Sky();
    int num;
    CMeshLoader* mesh;
    // Object을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

