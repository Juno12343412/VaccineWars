#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
    texture* img;
    texture* button1, *button2, *button3, *button4;

    Vector3 button1v, button2v, button3v, button4v;
    int menuNum = 0;
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    void control();
    bool pushButton = false;
};

