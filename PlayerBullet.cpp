#include "DXUT.h"
#include "PlayerBullet.h"
#include "BulletEffect.h"

PlayerBullet::PlayerBullet(int num, Vector3 moveDir)
	:num(num), moveDir(moveDir)
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init()
{
	eT = new Timer;
	eT->SetTimer(0.03f);
	udoT = new Timer;
	if (num == 1)
	{
		speed = 600;
		if (vPos.x < 200)
		{
			SOUND->Copy("Shoot1", 1000, -10000);
		}
		else if (vPos.x > 300)
		{
			SOUND->Copy("Shoot1", 1000, 10000);
		}
		else
		{
			SOUND->Copy("Shoot1", 1000, 0);
		}
		radius = 5.f;

	}
	else if (num == 2)
	{
		speed = 300;
		udo = false;
		
		udoT->SetTimer(1.f);
		if (vPos.x < 200)
		{
			SOUND->Copy("Shoot2", 1000, -10000);
		}
		else if (vPos.x > 300)
		{
			SOUND->Copy("Shoot2", 1000, 10000);
		}
		else
		{
			SOUND->Copy("Shoot2", 1000, 0);
		}
		radius = 5.f;

	}
	else if (num == 3)
	{
		speed = 500;
		radius = 13.f;
		SOUND->Copy("Shoot3", 1000, 0);
		CAMERA->CameraShake(100, 20);
	}
	desT = new Timer;
	desT->SetTimer(3.f);
	img = IMAGE->FindImage(L"Bullet1");

}

void PlayerBullet::Update()
{
	if (eT->Update() && num != 3)
		OBJECT->AddObject(new BulletEffect(1,0,0,255), vPos, RenderType::TWO);
	if (num == 1)
	{
		Vector3 temp = OBJECT->enemy2Pos - vPos;
		Vector3 temp2 = OBJECT->enemy3Pos - vPos;
		Vector3 temp3 = OBJECT->enemy4Pos - vPos;

		vPos += moveDir * D_TIME * speed;
		if (D3DXVec3Length(&temp) < OBJECT->enemy2Radius + radius)
		{
			OBJECT->enemy2Hp--;
			isDestroy = true;
		}
		else if (D3DXVec3Length(&temp2) < OBJECT->enemy3Radius + radius)
		{
			OBJECT->enemy3Hp--;
			isDestroy = true;
		}
		else if (D3DXVec3Length(&temp3) < OBJECT->enemy4Radius + radius)
		{
			OBJECT->enemy4Hp--;
			isDestroy = true;
		}
		if (desT->Update())
			isDestroy = true;
	}
	else if (num == 2)
	{

		if (udoT->Update())
		{
			udo = true;
		}
		Vector3 temp = OBJECT->enemy2Pos - vPos;
		Vector3 temp2 = OBJECT->enemy3Pos - vPos;
		Vector3 temp3 = OBJECT->enemy4Pos - vPos;
		if (D3DXVec3Length(&temp) < OBJECT->enemy2Radius + radius && OBJECT->enemy2Live)
		{
			OBJECT->enemy2Hp--;
			isDestroy = true;
		}
		else if (D3DXVec3Length(&temp2) < OBJECT->enemy3Radius + radius && OBJECT->enemy3Live)
		{
			OBJECT->enemy3Hp--;

			isDestroy = true;
		}
		else if (D3DXVec3Length(&temp3) < OBJECT->enemy4Radius + radius && OBJECT->enemy4Live)
		{
			OBJECT->enemy4Hp--;

			isDestroy = true;
		}
		if (!udo) {
			if (OBJECT->enemy2Live)
			{

				D3DXVec3Normalize(&temp, &temp);
				MATH->Lerp<Vector3>(&moveDir, moveDir, temp, 3.f);
			}
			else if (OBJECT->enemy3Live)
			{
				D3DXVec3Normalize(&temp2, &temp2);
				MATH->Lerp<Vector3>(&moveDir, moveDir, temp2, 3.f);
			}
			else if (OBJECT->enemy4Live)
			{
				D3DXVec3Normalize(&temp3, &temp3);
				MATH->Lerp<Vector3>(&moveDir, moveDir, temp3, 3.f);
			}
		}
		vPos += moveDir * speed * D_TIME;


		if (desT->Update())
			isDestroy = true;

	}
	if (num == 3)
	{
		Vector3 temp = OBJECT->enemy2Pos - vPos;
		Vector3 temp2 = OBJECT->enemy3Pos - vPos;
		Vector3 temp3 = OBJECT->enemy4Pos - vPos;

		vPos += moveDir * D_TIME * speed;
		if (D3DXVec3Length(&temp) < OBJECT->enemy2Radius + radius)
		{
			OBJECT->enemy2Hp -= 10;
		}
		else if (D3DXVec3Length(&temp2) < OBJECT->enemy3Radius + radius)
		{
			OBJECT->enemy3Hp -= 10;
		}
		else if (D3DXVec3Length(&temp3) < OBJECT->enemy4Radius + radius)
		{
			OBJECT->enemy4Hp -= 10;
		}
		if (desT->Update())
			isDestroy = true;
	}
}

void PlayerBullet::Render()
{
	IMAGE->ReBegin(false, false);
	if (num == 1 || num == 2) {
		img->CenterRender({ vPos.x, 13, vPos.z }, { 90,0,0 }, { 0.7,0.7,0.7 });
	}
	else if (num == 3)
	{
		IMAGE->ReBegin(false, false);

		IMAGE->FindImage(L"Bullet2")->CenterRender({ vPos.x, 13, vPos.z }, { 90.0f,moveDir.x * 90 + 2,0 });
	}
	IMAGE->ReBegin(false, false);

}

void PlayerBullet::Release()
{
	SAFE_DELETE(desT);
	SAFE_DELETE(udoT);
	SAFE_DELETE(eT);
}
