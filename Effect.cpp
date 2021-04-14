#include "DXUT.h"
#include "Effect.h"

Effect::Effect(int num, float size)
	:num(num), size(size)
{
}

Effect::~Effect()
{
}

void Effect::Init()
{
	aniT = new Timer;

	switch (num)
	{
	case 1:
		aniImg = IMAGE->FINDVECIMAGE(L"explosion");
		if (vPos.x < 200)
		{
			SOUND->Copy("Explosion", 1000, -10000);
		}
		else if (vPos.x > 300)
		{
			SOUND->Copy("Explosion", 1000, 10000);
		}
		else
		{
			SOUND->Copy("Explosion", 1000, 0);
		}
		aniF = 0;
		aniMaxF = 31;
		CAMERA->CameraShake(300, 10);
		aniT->SetTimer(0.02f);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 11:
	case 12:
		img = IMAGE->FindImage(L"fade");
		alpha = 0;
		break;
	case 9:
		img = IMAGE->FindImage(L"shield2");
		break;
	case 10:
		img = IMAGE->FindImage(L"shield3");
		break;
	}
	str = IMAGE->FindImage(L"stageclear");
	str2 = IMAGE->FindImage(L"youdied");
	if (num == 3)
	{
		SOUND->Copy("Lose", 1000, 0);
		CAMERA->CameraShake(600, 20);
	}
	if (num == 2 || num == 6)
	{
		SOUND->Copy("Victory", 1000, 0);
	}
}

void Effect::Update()
{
	if (num == 1) { // 폭발
		if (aniT->Update())
		{
			aniF++;
		}
		if (aniF >= aniMaxF) {
			isDestroy = true;
			aniF = 0;
		}
	}
	else if (num == 2) // 스테이지 1깻을때
	{
		if (alpha < 255) alpha+= D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("stage2");
		}
	}
	else if (num == 3) // 죽었을때
	{
		if (alpha < 255) alpha+= D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			OBJECT->rankOver = true;
			SCENE->ChageScene("ranking");
		}
	}
	else if (num == 4) // 게임시작
	{
		if (alpha < 255) alpha+= D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("stage1");
		}
	}
	else if (num == 5) // 타이틀 갈 때
	{
		if (alpha < 255) alpha+= D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("title");
		}
	}
	else if (num == 6) // 스테이지 2깻을떄
	{
		if (alpha < 255) alpha+= D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			OBJECT->rankOver = true;
			SCENE->ChageScene("ranking");
		}
	}
	else if (num == 7) // 타이틀에서 랭킹
	{
		if (alpha < 255) alpha += D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("ranking");
		}
	}
	else if (num == 8) // 타이틀에서 하우투
	{
		if (alpha < 255) alpha += D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("howto");
		}
	}
	else if (num == 9 || num == 10)
	{
		if (size > 0) size -= 0.2f;
		else
		{
			size = 0;
			isDestroy = true;
			
		}
	}
	else if (num == 11)
	{
		if (alpha < 255) alpha += D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("intro2");
		}
	}
	else if (num == 12)
	{
		if (alpha < 255) alpha += D_TIME * 200;
		else {
			alpha = 255;
			isDestroy = true;
			SCENE->ChageScene("intro3");
		}
	}
	
}

void Effect::Render()
{
	IMAGE->ReBegin(false, true);
	if (num == 1) {
		aniImg->FINDIMAGE(aniF)->CenterRender({ vPos.x, 12, vPos.z }, { 90,0,0 }, { 3,3,3 });
		aniImg->FINDIMAGE(aniF)->CenterRender({ vPos.x + 30, 41, vPos.z + 30 }, { 0,0,0 }, { 2,2,2 });
		aniImg->FINDIMAGE(aniF)->CenterRender({ vPos.x - 30, 40, vPos.z - 30 }, { 0,0,0 }, { 2,2,2 });
	}
	else if (num == 2)
	{
		IMAGE->ReBegin(true, false);

		img->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 }, { 0,0,0 }, { 1,1,1 }, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		str->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 });
	}
	else if (num == 3)
	{
		IMAGE->ReBegin(true, false);

		img->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 }, { 0,0,0 }, { 1,1,1 }, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		str2->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 });

	}
	else if (num == 4 || num == 5 || num == 7 || num == 8 || num == 11 || num == 12)
	{
		IMAGE->ReBegin(true, false);

		img->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 }, { 0,0,0 }, { 1,1,1 }, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
	else if (num == 6)
	{
		IMAGE->ReBegin(true, false);

		img->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 }, { 0,0,0 }, { 1,1,1 }, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		str->CenterRender({ WINSIZEX / 2, WINSIZEY / 2,0 });

	}
	else if (num == 9 || num == 10)
	{
		IMAGE->ReBegin(false, false);
		//img->CenterRender({ vPos.x, 15, vPos.z }, { 0,0,0 }, { size,size,1 });
		img->CenterRender({ vPos.x, 15, vPos.z }, { 90,0,0 }, { size,size,1 });
	}
	IMAGE->ReBegin(false, false);
}

void Effect::Release()
{
	SAFE_DELETE(aniT);
}
