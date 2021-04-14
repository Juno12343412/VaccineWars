#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	map = new int* [MAPSIZEX];
	for (int i = 0; i < MAPSIZEX; i++)
	{
		map[i] = new int[MAPSIZEX];
		memset(map[i], 0, sizeof(int) * MAPSIZEZ);
	}
}

ObjectManager::~ObjectManager()
{
	Release();
	for (int i = 0; i < MAPSIZEX; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

int ObjectManager::GetPercent()
{
	int temp1 = MAPSIZEX * MAPSIZEZ;
	int temp2 = 0;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (map[i][j] == 2 || map[i][j] == 3)
				temp2++;
		}
	}
	return temp2 * 100 / temp1;
}

void ObjectManager::SetPercent()
{
	percentText = to_wstring(GetPercent()) + L"%";

}

void ObjectManager::Update()
{
	for (int i = RenderType::FIRST + 1; i < RenderType::FINSH; i++)
	{
		for (auto iter = objList[i].begin(); iter != objList[i].end();)
		{
			if ((*iter)->CheckDestroy())
			{
				(*iter)->Release();
				SAFE_DELETE(*iter);
				iter = objList[i].erase(iter);
			}
			else
			{
				(*iter)->Update();
				iter++;
			}
		}
	}
	score = enemyScore + areaScore + hpItemScore;
}

void ObjectManager::Render()
{
	for (int i = RenderType::FIRST + 1; i < RenderType::FINSH; i++)
	{
		for (auto iter : objList[i])
		{
			iter->TransformUpdate();
			iter->Render();
		}
	}
}

void ObjectManager::Release()
{
	for (int i = RenderType::FIRST + 1; i < RenderType::FINSH; i++)
	{
		for (auto iter : objList[i])
		{
			(iter)->Release();
			SAFE_DELETE(iter);
		}
	}
	objList->clear();
}

void ObjectManager::ClearAllObject()
{
	for (int i = RenderType::FIRST + 1; i < RenderType::FINSH; i++) {
		for (auto iter : objList[i])
		{
			iter->isDestroy = true;
		}
	}
}

void ObjectManager::ResetGame()
{
	enemy2Live = false;
	enemy3Live = false;
	enemy4Live = false;
	rankOver = false;
	addEnemy2 = false;
	addEnemy3 = false;
	addEnemy4 = false;
	playerDie = false;
	gameOver = false;
	enemy1y = 1;
	enemy2y = 2;
	enemy3y = 3;
	percentText = L"0%";
	timeScale = 1;
	speedItem = 2;
	invinItem = 1;
	hpItem = 2;
	randomItem = 5;
	shoot2 = false;
	shoot1Item = 2;
	shoot2Item = 2;
	shoot3Item = 1;
	shoot4Item = 1;
	coin = 1;
	stage2 = false;
}