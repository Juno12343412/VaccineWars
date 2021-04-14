#include "DXUT.h"
#include "MainGame.h"
#include "LoadingScene.h"
#include "TitleScene.h"
#include "HowTo.h"
#include "RankingScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Effect.h"
#include "IntroScene.h"

void MainGame::Init()
{
	ShowCursor(false);

	SCENE->AddScene("loading", new LoadingScene);
	SCENE->AddScene("title", new TitleScene);
	SCENE->AddScene("howto", new HowTo);
	SCENE->AddScene("ranking", new RankingScene);
	SCENE->AddScene("stage1", new Stage1);
	SCENE->AddScene("stage2", new Stage2);
	SCENE->AddScene("intro", new IntroScene(1));
	SCENE->AddScene("intro2", new IntroScene(2));
	SCENE->AddScene("intro3", new IntroScene(3));
	SCENE->ChageScene("loading");
}

void MainGame::Update()
{
	CAMERA->Update();
	SCENE->Update();
	INPUT->Update();
	OBJECT->Update();
	if (INPUT->KeyDown(VK_F10))
	{
		OBJECT->AddObject(new Effect(5), { 0,0,0 }, RenderType::TWO);
	}
}

void MainGame::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false, false);

	SCENE->Render();
	OBJECT->Render();

	IMAGE->End();
}

void MainGame::Release()
{
	ShowCursor(true);

	CameraManager::ReleaseInstance();
	ImageManager::ReleaseInstance();
	SoundManager::ReleaseInstance();
	MathManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
}

void MainGame::ResetDevice()
{
	IMAGE->ResetDevice();
}

void MainGame::LostDevice()
{
	IMAGE->LostDevice();
}
