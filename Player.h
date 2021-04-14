#pragma once
#include "Object.h"
class Player :
    public Object
{
    float hp;
    float maxHp;
    float moveHp;
    float maxMoveHp;
    int speed;
    bool areaPlus = false;
    texture* pimg;
    texture* bimg;
    Vector3 vStart = { 0,0,0 };
    int* temp = nullptr;

    float imgDir = 180;

    int armor = 0;

    bool invin = false;
    Timer* invinT;
    int invinC = 0;

    wstring itemStr = L"No Buff";

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    void Move();
    void BackEvent();
    void AreaPlus(int num);
    bool shoot1 = false;
    bool shoot2 = false;
    bool shoot3 = false;
    bool shoot4 = false;
    Timer* attackT;
    Timer* shootT;
    int shootC = 0;
    Vector3 moveDir = { 0,0,0 };
    Timer* noMove;
    bool noMoveb = false;
    Timer* stageT;
    int stageC = 0;
    wstring stageCtext = L"제한시간 : 180초";
    bool reTry = false;
    Timer* gameOverT;
    int gameOverC;
    wstring gameOverText = L"10";
    bool shoot3Move = false;
    Timer* shoot3MoveT;
    bool playerDes = false;
    
    
};