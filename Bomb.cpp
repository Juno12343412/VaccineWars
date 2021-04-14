#include "DXUT.h"
#include "Bomb.h"
#include "Effect.h"

void Bomb::Init()
{
	mesh = IMAGE->FindMesh(L"Bomb");
	boom = new Timer;
	time = 3;
	boom->SetTimer(1.f);
}

void Bomb::Update()
{
	if (boom->Update())
	{
		time--;
	}
	if (time <= 0)
	{
		OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
		Vector3 temp = OBJECT->enemy2Pos - vPos;
		Vector3 temp2 = OBJECT->enemy3Pos - vPos;
		Vector3 temp3 = OBJECT->enemy4Pos - vPos;

		if (D3DXVec3Length(&temp) < OBJECT->enemy2Radius + radius)
		{
			OBJECT->enemy2Hp-= 10;
		}
		else if (D3DXVec3Length(&temp2) < OBJECT->enemy3Radius + radius)
		{
			OBJECT->enemy3Hp -= 10;
		}
		else if (D3DXVec3Length(&temp3) < OBJECT->enemy4Radius + radius)
		{
			OBJECT->enemy4Hp -= 10;
		}
		isDestroy = true;
	}
}

void Bomb::Render()
{
	IMAGE->MeshRender(mesh, matWorld, true);

	IMAGE->FindImage(L"BombWarning")->CenterRender({ vPos.x,2, vPos.z }, { 90,0,0 });
	IMAGE->ReBegin(false, true);
	IMAGE->TextDraw(to_wstring(time), { vPos.x,200 ,vPos.z }, 100, D3DCOLOR_XRGB(255, 0, 0), true, true);
	IMAGE->ReBegin(false, false);

}

void Bomb::Release()
{
	SAFE_DELETE(boom);
}
