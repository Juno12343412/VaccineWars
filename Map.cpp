#include "DXUT.h"
#include "Map.h"

Map::Map(int num)
	:num(num)
{
}

Map::~Map()
{
}

void Map::Init()
{
	img = IMAGE->AddImage(L"map", L"Map/Map");
	img2 = IMAGE->AddImage(L"map2", L"Map/Map2");
	img3 = IMAGE->AddImage(L"drawMap", L"Map/DrawMap");
	img4 = IMAGE->AddImage(L"map3", L"Map/Map3");


}

void Map::Update()
{

	D3DLOCKED_RECT lr;
	img->texturePtr->LockRect(0, &lr, nullptr, D3DLOCK_DISCARD);

	DWORD* textureColor = (DWORD*)lr.pBits;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (OBJECT->map[i][j] == 0)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor[idx];

				targetPixel.a = 1;

				textureColor[idx] = targetPixel;
			}
			if (OBJECT->map[i][j] == 2)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor[idx];

				if (targetPixel > 0)
					targetPixel.a -= 0.05;
				targetPixel.r = 1;
				targetPixel.g = 1;
				targetPixel.b = 1;
				textureColor[idx] = targetPixel;
			}
			

		}
	}
	img->texturePtr->UnlockRect(0);

	D3DLOCKED_RECT lr2;
	img2->texturePtr->LockRect(0, &lr2, nullptr, D3DLOCK_DISCARD);

	DWORD* textureColor2 = (DWORD*)lr2.pBits;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (OBJECT->map[i][j] == 0 || OBJECT->map[i][j] == 4 || OBJECT->map[i][j] == 6 || OBJECT->map[i][j] == 7)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor2[idx];

				targetPixel.a = 0.3f;

				textureColor2[idx] = targetPixel;

			}
			if (OBJECT->map[i][j] == 2)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor2[idx];

				if (targetPixel > 0)
					targetPixel.a -= 0.05;
				targetPixel.r = 1;
				targetPixel.g = 1;
				targetPixel.b = 1;

				textureColor2[idx] = targetPixel;

			}
			else if (OBJECT->map[i][j] == 3)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor2[idx];

				targetPixel.a = 0.3f;
				targetPixel.r = 1;
				targetPixel.g = 0;
				targetPixel.b = 0;

				textureColor2[idx] = targetPixel;

			}
		}
	}
	img2->texturePtr->UnlockRect(0);

	D3DLOCKED_RECT lr3;
	img3->texturePtr->LockRect(0, &lr3, nullptr, D3DLOCK_DISCARD);

	DWORD* textureColor3 = (DWORD*)lr3.pBits;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (OBJECT->map[i][j] == 3)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor3[idx];

				targetPixel.a = 1;
				targetPixel.r = 0;
				targetPixel.g = 1;
				targetPixel.b = 0;

				textureColor3[idx] = targetPixel;

			}
			else if (OBJECT->map[i][j] == 1)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor3[idx];

				targetPixel.a = 1;
				targetPixel.r = 1;
				targetPixel.g = 0;
				targetPixel.b = 0;
				textureColor3[idx] = targetPixel;
			}
			else if (OBJECT->map[i][j] == 0 || OBJECT->map[i][j] == 7)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor3[idx];

				targetPixel.a = 0;
				targetPixel.r = 0;
				targetPixel.g = 0;
				targetPixel.b = 0;
				textureColor3[idx] = targetPixel;
			}

		}
	}
	img3->texturePtr->UnlockRect(0);
	D3DLOCKED_RECT lr4;
	img4->texturePtr->LockRect(0, &lr4, nullptr, D3DLOCK_DISCARD);

	DWORD* textureColor4 = (DWORD*)lr4.pBits;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (OBJECT->map[i][j] == 0)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor[idx];

				targetPixel.a = 0;

				textureColor4[idx] = targetPixel;
			}
			if (OBJECT->map[i][j] == 2 || OBJECT->map[i][j] == 3)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor4[idx];
				targetPixel.a = 0;

				textureColor4[idx] = targetPixel;

			}
			if (OBJECT->map[i][j] == 10)
			{
				int idx = j * MAPSIZEZ + i;
				D3DXCOLOR targetPixel = textureColor4[idx];
				targetPixel.a = 0.5;

				targetPixel.r = 1;
				targetPixel.g = 0;
				targetPixel.b = 1;
				textureColor4[idx] = targetPixel;
			}

		}
	}
	img4->texturePtr->UnlockRect(0);
}

void Map::Render()
{
	IMAGE->ReBegin(false, false);
	img2->CenterRender({ 250,-250,0 }, { 0,0,0 });
	img2->CenterRender({ 250,-250,500 }, { 0,0,0 });
	img2->CenterRender({ 0,-250,250 }, { 0,90,0 });
	img2->CenterRender({ 500,-250,250 }, { 0,90,0 });
	img2->CenterRender({ 250,-500,250 }, { 90,0,0 });
	img->CenterRender({ 250,0,250 }, { 90,0,0 });
	img4->CenterRender({ 250,0,250 }, { 90,0,0 });
	img3->CenterRender({ 250,0,250 }, { 90,0,0 });
	IMAGE->ReBegin(false, false);

}

void Map::Release()
{
}
