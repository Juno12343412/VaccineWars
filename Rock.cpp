#include "DXUT.h"
#include "Rock.h"
#include "Effect.h"
Rock::Rock(int num)
	:num(num)
{
}

Rock::~Rock()
{
}

void Rock::Init()
{
	switch (num)
	{
	case 1:
		img = IMAGE->FindImage(L"rock1");
		sizeX = 70; sizeY = 61;
		break;
	case 2:
		img = IMAGE->FindImage(L"rock2");
		sizeX = 53; sizeY = 45;

		break;
	case 3:
		img = IMAGE->FindImage(L"rock3");
		sizeX = 67; sizeY = 60;

		break;
	}
	for (int i = (int)vPos.x - sizeX * 0.5f; i < (int)vPos.x + sizeX * 0.5f; i++)
	{
		for (int j = (int)vPos.z - sizeY * 0.5f; j < (int)vPos.z + sizeY * 0.5f; j++)
		{
			OBJECT->map[i][j] = 7;
		}
	}

}

void Rock::Update()
{
	if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 2)
	{
		OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
		isDestroy = true;
	}
}

void Rock::Render()
{
	for (float i = 0; i <= (sizeX * 0.3); i++)
	{
		IMAGE->ReBegin(false, false);

		img->CenterRender({ vPos.x, 1 + i,vPos.z }, { 90,0,0 });
		IMAGE->ReBegin(false, false);

	}
}

void Rock::Release()
{
}
