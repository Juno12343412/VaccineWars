#include "DXUT.h"
#include "IntroScene.h"
#include "Effect.h"

IntroScene::IntroScene(int num)
	:num(num)
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::Init()
{
	CAMERA->Reset();
	if (num == 1) {
		AddIntro(IMAGE->FindImage(L"Intro1(0)"));
		AddIntro(IMAGE->FindImage(L"Intro1(1)"));
		AddIntro(IMAGE->FindImage(L"Intro1(2)"));
		AddIntro(IMAGE->FindImage(L"Intro1(3)"));
	}
	else if (num == 2)
	{
		AddIntro(IMAGE->FindImage(L"Intro2(0)"));
		AddIntro(IMAGE->FindImage(L"Intro2(1)"));
		AddIntro(IMAGE->FindImage(L"Intro2(2)"));
		AddIntro(IMAGE->FindImage(L"Intro2(3)"));
		AddIntro(IMAGE->FindImage(L"Intro2(4)"));


	}
	else if (num == 3)
	{
		AddIntro(IMAGE->FindImage(L"Intro3(0)"));
		AddIntro(IMAGE->FindImage(L"Intro3(1)"));
		AddIntro(IMAGE->FindImage(L"Intro3(2)"));
		AddIntro(IMAGE->FindImage(L"Intro3(3)"));
		AddIntro(IMAGE->FindImage(L"Intro3(4)"));
		AddIntro(IMAGE->FindImage(L"Intro3(5)"));


	}
	delay = new Timer;
	delay->SetTimer(1.f);
	sceneStart = true;
}

void IntroScene::Update()
{
	if (introList.empty()) {
		if (num == 1 && sceneStart) {
			OBJECT->AddObject(new Effect(5), { 0,0,0 }, RenderType::TWO);
			sceneStart = false;
		}
		else if (num == 2 && sceneStart) {
			OBJECT->AddObject(new Effect(4), { 0,0,0 }, RenderType::TWO);
			sceneStart = false;
		}
		else if (num == 3 && sceneStart) {
			OBJECT->AddObject(new Effect(2), { 0,0,0 }, RenderType::TWO);
			sceneStart = false;
		}
	}
	if (size < maxSize)
	{
		size += 600 * D_TIME;
	}
	else
	{
		size = maxSize;
		if (delay->Update()) {
			if (!introList.empty()) {
				introList.pop_front();
			}
			size = 0;
		}
	}
}

void IntroScene::Render()
{
	IMAGE->ReBegin(true, false);
	IMAGE->FindImage(L"BGIntro")->CenterRender({ WINSIZEX / 2, WINSIZEY / 2, 0 });
	RECT rc = { 0,0,1920 * (size / maxSize),400 };
	if(!introList.empty())
		introList.front()->Render({ WINSIZEX / 2 - 1920 * 0.5f, 680,0 }, { 0,0,0 }, { 1,1,1 }, rc);
	IMAGE->ReBegin(false, false);

}

void IntroScene::Release()
{
	SAFE_DELETE(delay);
}

void IntroScene::AddIntro(texture* texture)
{
	introList.push_back(texture);
}
