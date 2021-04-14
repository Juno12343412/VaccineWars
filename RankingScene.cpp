#include "DXUT.h"
#include "RankingScene.h"
#include "Effect.h"

void RankingScene::Init()
{
	img = IMAGE->FindImage(L"RankingBG");
	ch = L"";
	result = OBJECT->score;
}

void RankingScene::Update()
{
	if (!OBJECT->rankOver) {
		if (INPUT->KeyDown(VK_SPACE))
		{
			OBJECT->AddObject(new Effect(5), { 0,0,0 }, RenderType::TWO);
		}
	}
	else {
		
		if (ch.size() < 3)
		{
			if (result == resultW) {
				for (int i = 65; i <= 90; i++)
				{
					if (INPUT->KeyDown(i))
					{
						WCHAR ch1[20];
						wsprintf(ch1, L"%c", i);
						ch += ch1;
					}
				}
			}
			else
			{
				if (resultW < result - 10)
					MATH->Lerp<int>(&resultW, resultW, result, 10.f);
				else
					resultW = result;
			}
		}
		else
		{
			OBJECT->Ranking.insert(make_pair(result, ch));

			OBJECT->AddObject(new Effect(5), { 0,0,0 }, RenderType::TWO);
		}
	}
}

void RankingScene::Render()
{
	IMAGE->ReBegin(true, false);
	
	img->CenterRender({ WINSIZEX / 2, WINSIZEY/2,0 });
	if (!OBJECT->rankOver)
	{
		rank = 1;
		for (auto iter : OBJECT->Ranking)
		{
			IMAGE->TextDraw(to_wstring(rank) + L".  " + iter.second + L"  " + to_wstring(iter.first), { WINSIZEX / 2 - 250, 300 + (float)rank * 100,0 }, 100, D3DCOLOR_XRGB(255, 255, 255), false);
			rank++;
			if (rank >= 6) break;
		}
		IMAGE->ReBegin(false, false);
	}
	else
	{
		IMAGE->TextDraw(L" 영역 치료 점수 : " + to_wstring((int)OBJECT->areaScore), { WINSIZEX / 2 - 600, 400,0 }, 250, D3DCOLOR_XRGB(255, 255, 0), false);
		IMAGE->TextDraw(L" 적 처치 보너스 : " + to_wstring((int)OBJECT->enemyScore), { WINSIZEX / 2 - 600, 550,0 }, 250, D3DCOLOR_XRGB(255, 255, 0), false);
		IMAGE->TextDraw(L" 아이템 보너스 : " + to_wstring((int)OBJECT->hpItemScore), { WINSIZEX / 2 - 600, 700,0 }, 250, D3DCOLOR_XRGB(255, 255, 0), false);
		IMAGE->TextDraw(ch + L"  " + to_wstring(resultW) + L"점", { WINSIZEX / 2 - 200, 850,0 }, 300, D3DCOLOR_XRGB(255, 0, 0), false);
	}

}

void RankingScene::Release()
{
	if (OBJECT->rankOver)
		OBJECT->rankOver = false;
}
