#pragma once
#include "Object.h"
class Earth :
    public Object
{
public:
    Earth(int num);
    virtual ~Earth();

    CMeshLoader* mesh;
    int num = 0;
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

