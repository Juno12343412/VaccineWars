#include "DXUT.h"
#include "Stage2.h"
#include "Sky.h"
#include "Map.h"
#include "Earth.h"
#include "Player.h"
#include "Effect.h"
#include "Rock.h"
#include "Enemy.h"

void Stage2::Init()
{
	CAMERA->Reset();

	OBJECT->ResetGame();
	OBJECT->AddObject(new Player(), { 0,0,0 }, RenderType::TWO);
	OBJECT->AddObject(new Sky(2), { 250,0,250 }, RenderType::THREE);
	OBJECT->AddObject(new Earth(2), { 250,-250,250 }, RenderType::THREE); 
	OBJECT->AddObject(new Map(2), { 250,250,0 }, RenderType::THREE);
	OBJECT->AddObject(new Enemy(1), { 100,0,100 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(2), { 50,0,100 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(3), { 150,0,150 }, RenderType::TWO);
	OBJECT->AddObject(new Enemy(4), { 200,0,200 }, RenderType::TWO);
	OBJECT->AddObject(new Rock(1), { 100,0,100 }, RenderType::TWO);
	OBJECT->AddObject(new Rock(3), { 350,0,350 }, RenderType::TWO);
	OBJECT->stage = 1;
	SOUND->Play("Main", true);
	OBJECT->stage2 = true;
}

void Stage2::Update()
{
	if (INPUT->KeyDown(VK_F9))
	{
		OBJECT->AddObject(new Effect(6), { 0,0,0 }, RenderType::TWO);
	}
}

void Stage2::Render()
{
}

void Stage2::Release()
{
	OBJECT->stage2 = false;
	SOUND->Stop("Main");
}
