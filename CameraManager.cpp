#include "DXUT.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
	camPos = Vector3(250, 500, -400);
	camRot = Vector3(0, -0.7f, 1);
	shakeTime = 0; shakeScale = 0;
	srand(time(NULL));

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 1000000);
}

CameraManager::~CameraManager()
{
}

void CameraManager::SetTransform()
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::MoveCamera(const Vector3& plusPos)
{
	camPos += plusPos;

}

void CameraManager::RotateCamera(const Vector3& plusPos)
{
	camRot += plusPos;
	D3DXVec3Normalize(&camRot, &camRot);
}

void CameraManager::SetCamera(const Vector3& setPos)
{
	camPos = setPos;

}

void CameraManager::Update()
{
	if (shakeTime >= timeGetTime() && shakeScale > 0)
	{
		shakeCam = true;
		camPos += Vector3(rand() % (int)shakeScale - (int)shakeScale * 0.5f, rand() % (int)shakeScale - (int)shakeScale * 0.5f, 0);
	}
	else if (shakeCam)
	{
		shakeCam = false;
		
		Reset();
	}

	D3DXMatrixLookAtLH(&matView, &camPos, &(camPos + camRot), &Vector3(0, 1, 0));
}

void CameraManager::Reset()
{
	camPos = Vector3(250, 500, -400);
	camRot = Vector3(0, -0.7f, 1);
	shakeTime = 0; shakeScale = 0;

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 1000000);
}

void CameraManager::CameraShake(float time, float scale)
{
	if (shakeTime <= time + timeGetTime())
		shakeTime = time + timeGetTime();
	vPos = camPos;
	shakeScale = scale;
}
