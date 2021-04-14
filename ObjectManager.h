#pragma once
#include "singleton.h"
#include "Object.h"
#define MAPSIZEX 500
#define MAPSIZEZ 500

class ObjectManager :
	public singleton<ObjectManager>
{
	friend class Object;
public:
	ObjectManager();
	virtual ~ObjectManager();

	list<Object*> objList[RenderType::FINSH];

	Object* AddObject(Object* obj, Vector3 pos, RenderType tag)
	{
		obj->vPos = pos;
		obj->renderType = tag;
		obj->Init();
		objList[tag].emplace_back(obj);
		return obj;
	}

	map<int, wstring, std::greater<int>> Ranking;
	int** map;
	int GetPercent();
	void SetPercent();
	void Update();
	void Render();
	void Release();
	void ClearAllObject();

	bool    playerDie = false;
	bool    cheet1 = false;
	bool    gameOver = false;
	float   enemy1y = 1;
	float    enemy2y = 2;
	float   enemy3y = 3;
	int score = 0;
	wstring  percentText = L"0%";
	wstring  bossPercentText = L"0%";
	int      timeScale = 1;
	int speedItem = 2;
	int invinItem = 1;
	int hpItem = 2;
	int randomItem = 5;
	bool addEnemy2 = false;
	bool addEnemy3 = false;
	bool addEnemy4 = false;
	bool rankOver = false;
	int stage = 1;
	bool shoot2 = false;
	int shoot1Item = 2;
	int shoot2Item = 2;
	int shoot3Item = 1;
	int shoot4Item = 1;
	void ResetGame();
	Vector3 enemy2Pos;
	Vector3 enemy3Pos;
	Vector3 enemy4Pos;
	bool enemy2Live = false;
	bool enemy3Live = false;
	bool enemy4Live = false;
	float enemy2Radius = 20;
	float enemy3Radius = 40;
	float enemy4Radius = 25;
	float enemy2Hp = 0;
	float enemy2MaxHp = 0;
	float enemy3Hp = 0;
	float enemy3MaxHp = 0;
	float enemy4Hp = 0;
	float enemy4MaxHp = 0;
	int coin = 1;
	bool stage2 = false;
	float areaScore = 0;
	float enemyScore = 0;
	float hpItemScore = 0;
};

#define OBJECT ObjectManager::GetInstance()