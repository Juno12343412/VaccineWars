#include "DXUT.h"
#include "HowTo.h"
#include "Effect.h"

void HowTo::Init()
{
	img = IMAGE->FindImage(L"HowToBG");
}

void HowTo::Update()
{
	if (INPUT->KeyDown(VK_SPACE))
	{
		OBJECT->AddObject(new Effect(5), { 0,0,0 }, RenderType::TWO);
	}
}

void HowTo::Render()
{
	IMAGE->ReBegin(true, false);

	img->CenterRender({ WINSIZEX / 2, WINSIZEY / 2 ,0});

	IMAGE->ReBegin(false, false);
}

void HowTo::Release()
{
}
