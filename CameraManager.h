#pragma once
#include "singleton.h"
class CameraManager :
    public singleton<CameraManager>
{
public:
    CameraManager();
    virtual ~CameraManager();
    Matrix matProj, matView;
    Vector3 camPos, camRot, vPos;
    bool shakeCam = false;
    float shakeTime = 0.0f;
    float shakeScale = 0.0f;

    void SetTransform();
    void MoveCamera(const Vector3& plusPos);
    void RotateCamera(const Vector3& plusPos);
    void SetCamera(const Vector3& setPos);

    void Update();
    void Reset();
    void CameraShake(float time, float scale);
};

#define CAMERA CameraManager::GetInstance()