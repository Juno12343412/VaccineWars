#include "DXUT.h"
#include "Sky.h"

Sky::Sky(int num)
	:num(num)
{
}

Sky::~Sky()
{
}

void Sky::Init()
{
	if (num == 1)
		mesh = IMAGE->FindMesh(L"sky1");
	else if (num == 2)
		mesh = IMAGE->FindMesh(L"sky2");
	vRot = { 0,0,90 };
	vSize = { 30,30,30 };
}

void Sky::Update()
{
	RotatePos({ 0,-10,0 }, true);
}

void Sky::Render()
{
	IMAGE->MeshRender(mesh, matWorld, false);
}

void Sky::Release()
{
}
