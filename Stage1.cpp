#include "DXUT.h"
#include "Stage1.h"
#include "Sky.h"
#include "Map.h"
#include "Earth.h"
#include "Player.h"
#include "Effect.h"
#include "Rock.h"
#include "Enemy.h"

void Stage1::Init()
{
	CAMERA->Reset();

	OBJECT->areaScore = 0;
	OBJECT->enemyScore = 0;
	OBJECT->hpItemScore = 0;
	OBJECT->ResetGame();
	OBJECT->AddObject(new Player(), { 0,0,0 }, RenderType::TWO);
	OBJECT->AddObject(new Sky(1), { 250,0,250 }, RenderType::THREE);
	OBJECT->AddObject(new Earth(1), { 250,-250,250 }, RenderType::THREE);
	OBJECT->AddObject(new Map(1), { 250,250,0 }, RenderType::THREE);
	OBJECT->AddObject(new Enemy(1), { 100,0,100 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(2), { 50,0,100 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(3), { 150,0,150 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(4), { 200,0,200 }, RenderType::TWO);
	OBJECT->AddObject(new Rock(2), { 250,0,250 }, RenderType::TWO);
	OBJECT->stage = 1;
	SOUND->Play("Main", true);
}

void Stage1::Update()
{
	if (INPUT->KeyDown(VK_F9))
	{
		OBJECT->AddObject(new Effect(2), { 0,0,0 }, RenderType::TWO);
	}
}

void Stage1::Render()
{
}

void Stage1::Release()
{
	SOUND->Stop("Main");
}
