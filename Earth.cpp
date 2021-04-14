#include "DXUT.h"
#include "Earth.h"

Earth::Earth(int num)
	:num(num)
{
}

Earth::~Earth()
{
}

void Earth::Init()
{
	if (num == 1)
	{
		mesh = IMAGE->FindMesh(L"human3");
		vSize = { 1.5,1.5,1.5 };
		
		vPos.y = -320;

	}
	else if (num == 2)
	{
		mesh = IMAGE->FindMesh(L"earth3");
		vSize = { 2,2,2 };
		vRot = { 90,0,0 };
	}

}

void Earth::Update()
{
	
	if (num == 1)
	{
		RotatePos({ 0,10,0 }, true);
	}
	else if (num == 2)
	{
		RotatePos({ 0,0,10 }, true);
	}
	if (OBJECT->GetPercent() >= 80)
	{
		if (num == 1)
		{
			mesh = IMAGE->FindMesh(L"human");
			

		}
		else if (num == 2)
		{
			mesh = IMAGE->FindMesh(L"earth");
			
		}
	}
	
	else if (OBJECT->GetPercent() >= 40)
	{
		if (num == 1)
		{
			mesh = IMAGE->FindMesh(L"human2");

		}
		else if (num == 2)
		{
			mesh = IMAGE->FindMesh(L"earth2");
		}
	}
}

void Earth::Render()
{
	IMAGE->MeshRender(mesh, matWorld, false);
}

void Earth::Release()
{
}
