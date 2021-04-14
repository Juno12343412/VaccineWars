#include "DXUT.h"
#include "TitleScene.h"
#include "Effect.h"

void TitleScene::Init()
{
	menuNum = 0;
	img = IMAGE->FindImage(L"TitleBG");
	button1 = IMAGE->FindImage(L"START");
	button2 = IMAGE->FindImage(L"HOWTO");
	button3 = IMAGE->FindImage(L"RANKING");
	button4 = IMAGE->FindImage(L"EXIT");
	button1v = { 1400,400,0 };
	button2v = { 1400,550,0 };
	button3v = { 1400,700,0 };
	button4v = { 1400,850,0 };
	pushButton = false;
	SOUND->Play("Main", true);
}

void TitleScene::Update()
{
	control();
	if (pushButton)
	{
		switch (menuNum)
		{
		case 0:
			MATH->Lerp<Vector3>(&button1v, button1v, Vector3(3000, button1v.y, button1v.z), 2);
			MATH->Lerp<Vector3>(&button2v, button2v, Vector3(3000, button2v.y, button2v.z), 2);
			MATH->Lerp<Vector3>(&button3v, button3v, Vector3(3000, button3v.y, button3v.z), 2);
			MATH->Lerp<Vector3>(&button4v, button4v, Vector3(3000, button4v.y, button4v.z), 2);
			if (button1v.x > 1920)
			{
				OBJECT->AddObject(new Effect(11), { 0,0,0 }, RenderType::TWO);

			}
			break;
		case 1:
			MATH->Lerp<Vector3>(&button1v, button1v, Vector3(3000, button1v.y, button1v.z), 2);
			MATH->Lerp<Vector3>(&button2v, button2v, Vector3(3000, button2v.y, button2v.z), 2);
			MATH->Lerp<Vector3>(&button3v, button3v, Vector3(3000, button3v.y, button3v.z), 2);
			MATH->Lerp<Vector3>(&button4v, button4v, Vector3(3000, button4v.y, button4v.z), 2);
			if (button2v.x > 1920)
			{
				OBJECT->AddObject(new Effect(8), { 0,0,0 }, RenderType::TWO);

			}
			break;

		case 2:
			MATH->Lerp<Vector3>(&button1v, button1v, Vector3(3000, button1v.y, button1v.z), 2);
			MATH->Lerp<Vector3>(&button2v, button2v, Vector3(3000, button2v.y, button2v.z), 2);
			MATH->Lerp<Vector3>(&button3v, button3v, Vector3(3000, button3v.y, button3v.z), 2);
			MATH->Lerp<Vector3>(&button4v, button4v, Vector3(3000, button4v.y, button4v.z), 2);
			if (button3v.x > 1920)
			{
				OBJECT->AddObject(new Effect(7), { 0,0,0 }, RenderType::TWO);

			}
			break;
		}
	}
}

void TitleScene::Render()
{
	IMAGE->ReBegin(true, false);
	img->CenterRender(Vector3(WINSIZEX / 2, WINSIZEY / 2, 0));
	IMAGE->FindImage(L"player")->CenterRender({ WINSIZEX / 2 - 300, WINSIZEY / 2 + 300,0 }, { 0,0,0 }, { 10,10,1 });
	button1->CenterRender(button1v);
	button2->CenterRender(button2v);
	button3->CenterRender(button3v);
	button4->CenterRender(button4v);
	
	IMAGE->ReBegin(false, false);

}

void TitleScene::Release()
{
	SOUND->Stop("Main");
}

void TitleScene::control()
{
	if (INPUT->KeyDown(VK_UP))
	{
		menuNum--;
		if (menuNum < 0) menuNum = 3;
	}
	if (INPUT->KeyDown(VK_DOWN))
	{
		menuNum++;
		if (menuNum > 3) menuNum = 0;
	}
	switch (menuNum)
	{
	case 0:
		MATH->Lerp<Vector3>(&button1v, button1v, Vector3(1100, button1v.y, button1v.z), 2);
		MATH->Lerp<Vector3>(&button2v, button2v, Vector3(1400, button2v.y, button2v.z), 2);
		MATH->Lerp<Vector3>(&button3v, button3v, Vector3(1400, button3v.y, button3v.z), 2);
		MATH->Lerp<Vector3>(&button4v, button4v, Vector3(1400, button4v.y, button4v.z), 2);
		if (INPUT->KeyDown(VK_SPACE))
		{
			SOUND->Copy("Start");

			pushButton = true;
		}
		break;
	case 1:
		MATH->Lerp<Vector3>(&button1v, button1v, Vector3(1400, button1v.y, button1v.z), 2);
		MATH->Lerp<Vector3>(&button2v, button2v, Vector3(1100, button2v.y, button2v.z), 2);
		MATH->Lerp<Vector3>(&button3v, button3v, Vector3(1400, button3v.y, button3v.z), 2);
		MATH->Lerp<Vector3>(&button4v, button4v, Vector3(1400, button4v.y, button4v.z), 2);
		if (INPUT->KeyDown(VK_SPACE))
		{
			pushButton = true;

		}

		break;
	case 2:
		MATH->Lerp<Vector3>(&button1v, button1v, Vector3(1400, button1v.y, button1v.z), 2);
		MATH->Lerp<Vector3>(&button2v, button2v, Vector3(1400, button2v.y, button2v.z), 2);
		MATH->Lerp<Vector3>(&button3v, button3v, Vector3(1100, button3v.y, button3v.z), 2);
		MATH->Lerp<Vector3>(&button4v, button4v, Vector3(1400, button4v.y, button4v.z), 2);
		if (INPUT->KeyDown(VK_SPACE))
		{
			pushButton = true;

		}

		break;
	case 3:
		MATH->Lerp<Vector3>(&button1v, button1v, Vector3(1400, button1v.y, button1v.z), 2);
		MATH->Lerp<Vector3>(&button2v, button2v, Vector3(1400, button2v.y, button2v.z), 2);
		MATH->Lerp<Vector3>(&button3v, button3v, Vector3(1400, button3v.y, button3v.z), 2);
		MATH->Lerp<Vector3>(&button4v, button4v, Vector3(1100, button4v.y, button4v.z), 2);
		if (INPUT->KeyDown(VK_SPACE))
		{
			PostQuitMessage(0);
		}
		break;
	}
}
