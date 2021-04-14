#pragma once
#include "singleton.h"
class MathManager :
    public singleton<MathManager>
{
public:
    template<typename T>
    void Lerp(T* target, T start, T finsh, float time)
    {
        *target = start + (finsh - start) * time * D_TIME;
    }

    void FloodFill(int x, int z);
    void SearchFloodFill(int x, int z, int& bossCount);
    void BackFloodFill(int x, int z);
};

#define MATH MathManager::GetInstance()