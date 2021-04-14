#include "DXUT.h"
#include "BulletEffect.h"

BulletEffect::BulletEffect(float size, int r, int g, int b)
	:size(size),r(r), g(g), b(b)
{
}

BulletEffect::~BulletEffect()
{
}

void BulletEffect::Init()
{
	alpha = 255;
	
}

void BulletEffect::Update()
{
	size -= D_TIME * 1.5f;
	alpha -= (int)(D_TIME * 20);
	if (size <= 0 || alpha <= 0)
	{
		size = 0;
		alpha = 0;
		isDestroy = true;
	}
}

void BulletEffect::Render()
{
	IMAGE->FindImage(L"BulletEffect")->CenterRender({ vPos.x, 7, vPos.z }, { 0,0,0 }, { size,size,1 }, D3DCOLOR_ARGB(alpha, r, g, b));
}

void BulletEffect::Release()
{
}
