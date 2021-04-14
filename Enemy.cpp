#include "DXUT.h"
#include "Enemy.h"
#include "Effect.h"
Enemy::Enemy(int num)
	:num(num)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	switch (num)
	{
	case 1:
		img = IMAGE->FindImage(L"bossImage");
		if (OBJECT->stage == 1)
			speed = 5;
		else if (OBJECT->stage == 2)
			speed = 7;
		OBJECT->map[(int)vPos.x][(int)vPos.z] = 4;
		imgSize = 106;
		myY = 5;
		break;
	case 2:
		img = IMAGE->FindImage(L"enemy1Image");
		speed = 10;
		imgSize = 41;
		myY = OBJECT->enemy1y;
		OBJECT->enemy1y += 0.1f;
		OBJECT->enemy2Live = true;
		OBJECT->enemy2Hp = 4;
		OBJECT->enemy2MaxHp = 4;
		break;
	case 3:
		img = IMAGE->FindImage(L"enemy2Image");
		speed = 4;
		imgSize = 80;
		myY = OBJECT->enemy2y;
		OBJECT->enemy2y += 0.1f;
		OBJECT->enemy3Live = true;
		OBJECT->enemy3Hp = 8;
		OBJECT->enemy3MaxHp = 8;
		break;
	case 4:
		img = IMAGE->FindImage(L"enemy3Image");
		plusSize = rand() % 1 + 0.3f;
		speed = 7;
		imgSize = 53;
		myY = OBJECT->enemy3y;
		OBJECT->enemy3y += 0.1f;
		OBJECT->enemy4Live = true;
		OBJECT->enemy4Hp = 6;
		OBJECT->enemy4MaxHp = 6;
		break;
	}
	vRot = Vector3(90, 0, 0);
	alpha = 255;
	OBJECT->AddObject(new Effect(10, 10), vPos, RenderType::TWO);
}

void Enemy::Update()
{
	for (int i = 0; i <= (int)((speed + (imgSize * (size / maxSize))) * 0.5f); i++)
	{
		Vector3 temp = moveDir;
		Vector3 checkPos = Vector3(vPos.x, 0, vPos.z) + temp * i * OBJECT->timeScale;

		switch (OBJECT->map[(int)checkPos.x][(int)vPos.z])
		{
		case 1:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		case 3:
		case 7:
			if (moveDir.x > 0)
				temp = temp + 2 * Vector3(1, 0, 0) * D3DXVec3Dot(&-moveDir, &Vector3(1, 0, 0));
			else
				temp = temp + 2 * Vector3(-1, 0, 0) * D3DXVec3Dot(&-moveDir, &Vector3(-1, 0, 0));
			moveDir = Vector3(temp.x, 0, temp.z);
			plusSpeed = 30;
			break;
		}
		switch (OBJECT->map[(int)vPos.x][(int)checkPos.z])
		{
		case 1:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		case 3:
		case 7:
			if (moveDir.x > 0)
				temp = temp + 2 * Vector3(0, 0, 1) * D3DXVec3Dot(&-moveDir, &Vector3(0, 0, 1));
			else
				temp = temp + 2 * Vector3(0, 0, -1) * D3DXVec3Dot(&-moveDir, &Vector3(0, 0, -1));
			moveDir = Vector3(temp.x, 0, temp.z);
			plusSpeed = 30;


			break;
		}
	}
	if (plusSpeed > 0.1)
	{
		MATH->Lerp<int>(&plusSpeed, plusSpeed, 0, 0.1);
	}
	else
	{
		plusSpeed = 0;
	}

	if (num == 1)
	{
		for (int i = 0; i < MAPSIZEX; i++)
		{
			for (int j = 0; j < MAPSIZEZ; j++)
			{
				if (OBJECT->map[i][j] == 4)
					OBJECT->map[i][j] = 0;
			}
		}

		vPos += moveDir * speed * 10 * D_TIME * OBJECT->timeScale;

		for (int i = -6; i <= 6; i++)
		{
			for (int j = -25; j <= 25; j++)
			{
				if(vPos.x + i < MAPSIZEX && vPos.x + i > 0){
					if (vPos.z + j < MAPSIZEX && vPos.z + j > 0)
					{
						if (OBJECT->map[(int)vPos.x + i][(int)vPos.z + j] == 0)
							OBJECT->map[(int)vPos.x + i][(int)vPos.z + j] = 10;
					}
				}
				
			}
		}
		if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z] == 10)
		{
			OBJECT->map[(int)vPos.x][(int)vPos.z] = 4;
		}


		if (OBJECT->GetPercent() >= 80 && OBJECT->timeScale != 0)
		{
			OBJECT->timeScale = 0;
			OBJECT->map[(int)vPos.x][(int)vPos.z] = 0;
			if (OBJECT->stage2) {
				OBJECT->AddObject(new Effect(6), vPos, RenderType::TWO);
			}
			else {
				OBJECT->AddObject(new Effect(12), vPos, RenderType::TWO);
			}
			MATH->FloodFill(vPos.x, vPos.z);
			OBJECT->SetPercent();
			OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
			OBJECT->AddObject(new Effect(1), { vPos.x + 50,vPos.y,vPos.z + 50 }, RenderType::TWO);
			OBJECT->AddObject(new Effect(1), { vPos.x - 50,vPos.y,vPos.z - 50 }, RenderType::TWO);
			isDestroy = true;
		}

		
		if (INPUT->KeyDown(VK_F7))
		{
			int Count = 0;
			for (int i = 0; i < MAPSIZEX; i++)
			{
				for (int j = 0; j < MAPSIZEZ; j++)
				{
					if (OBJECT->map[i][j] == 0)
					{
						if (Count < 1000) {
							Count++;
							OBJECT->map[i][j] = 10;
						}
					}
				}
			}
		}
		if (INPUT->KeyDown(VK_F8))
		{
			int Count = 0;
			for (int i = 0; i < MAPSIZEX; i++)
			{
				for (int j = 0; j < MAPSIZEZ; j++)
				{
					if (OBJECT->map[i][j] == 10)
					{
						if (Count < 1000) {
							Count++;
							OBJECT->map[i][j] = 0;
						}
					}
				}
			}
		}
		int temp1 = MAPSIZEX * MAPSIZEZ;
		int temp2 = 0;
		for (int i = 0; i < MAPSIZEX; i++)
		{
			for (int j = 0; j < MAPSIZEZ; j++)
			{
				if (OBJECT->map[i][j] == 10)
					temp2++;
			}
		}
		OBJECT->bossPercentText = to_wstring((temp2 * 100 / temp1) * 2) + L"%";
		if ((temp2 * 100 / temp1) * 2 >= 60 && !bossWin)
		{
			OBJECT->AddObject(new Effect(3), vPos, RenderType::TWO);
			bossWin = true;
		}
	}
	else if (num == 2)
	{
		if (OBJECT->enemy2Hp > 0) {
			vPos += moveDir * (speed + plusSpeed) * 10 * D_TIME * OBJECT->timeScale;
			OBJECT->enemy2Pos = vPos;
			if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 2)
			{
				OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
				isDestroy = true;
				OBJECT->enemy2Live = false;


				OBJECT->enemyScore += 300;
			}
		}
		else
		{
			OBJECT->enemy2Hp = 0;
			OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
			isDestroy = true;
			OBJECT->enemy2Live = false;
			OBJECT->enemyScore += 300;
		}
	}

	else if (num == 3)
	{
		if (OBJECT->enemy3Hp > 0) {
			
			vPos += moveDir * speed * 10 * D_TIME * OBJECT->timeScale;
			OBJECT->enemy3Pos = vPos;
			if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 2)
			{
				OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
				isDestroy = true;
				OBJECT->enemy3Live = false;


				OBJECT->enemyScore += 300;
			}
		}
		else
		{
			OBJECT->enemy3Hp = 0;
			OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
			isDestroy = true;
			OBJECT->enemy3Live = false;


			OBJECT->enemyScore += 300;
		}
	}

	else if (num == 4)
	{
		if (OBJECT->enemy4Hp > 0) {
			vPos += moveDir * (speed) * 10 * D_TIME * OBJECT->timeScale;
			OBJECT->enemy4Pos = vPos;
			if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 2)
			{
				OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
				isDestroy = true;
				OBJECT->enemy4Live = false;
			}
			if (alpha < 10 && !alphaUp) {
				alphaUp = true;
			}
			else if (alpha > 245 && alphaUp)
			{
				alphaUp = false;
			}
			if (alphaUp) alpha = 255;
			else alpha -= D_TIME * 20;
		}
		else
		{
			OBJECT->enemy4Hp = 0;
			OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
			isDestroy = true;
			OBJECT->enemy4Live = false;

			OBJECT->enemyScore += 300;
		}
	}
	bodyRot += (50 / (size / maxSize)) * D_TIME * OBJECT->timeScale;
	if (OBJECT->GetPercent() >= 80)
	{
		OBJECT->timeScale = 0;
	}
	else if (OBJECT->GetPercent() >= 60 && !OBJECT->addEnemy4 && !OBJECT->enemy4Live)
	{
		size = 7;
		if (num == 1)
		{
			for (int i = 0; i < MAPSIZEX; i++)
			{
				for (int j = 0; j < MAPSIZEZ; j++)
				{
					if (OBJECT->map[i][j] == 0 && !OBJECT->addEnemy4)
					{
						OBJECT->AddObject(new Enemy(4), { (float)i,0,(float)j }, RenderType::TWO);
						OBJECT->addEnemy4 = true;
						OBJECT->AddObject(new Effect(10, 10), vPos, RenderType::TWO);
					}
				}
			}
		}
	}
	else if (OBJECT->GetPercent() >= 40 && !OBJECT->addEnemy3 && !OBJECT->enemy3Live)
	{

		size = 10;
		if (num == 1)
		{
			for (int i = 0; i < MAPSIZEX; i++)
			{
				for (int j = 0; j < MAPSIZEZ; j++)
				{
					if (OBJECT->map[i][j] == 0 && !OBJECT->addEnemy3)
					{
						OBJECT->AddObject(new Enemy(3), { (float)i,0,(float)j }, RenderType::TWO);
						OBJECT->addEnemy3 = true;
						OBJECT->AddObject(new Effect(10, 10), vPos, RenderType::TWO);
					}
				}
			}
		}
	}
	else if (OBJECT->GetPercent() >= 20 && !OBJECT->addEnemy2 && !OBJECT->enemy2Live)
	{
		size = 13;
		if (num == 1)
		{
			for (int i = 0; i < MAPSIZEX; i++)
			{
				for (int j = 0; j < MAPSIZEZ; j++)
				{
					if (OBJECT->map[i][j] == 0 && !OBJECT->addEnemy2)
					{
						OBJECT->AddObject(new Enemy(2), { (float)i,0,(float)j }, RenderType::TWO);
						OBJECT->addEnemy2 = true;
						OBJECT->AddObject(new Effect(10, 10), vPos, RenderType::TWO);
					}
				}
			}
		}
	}
}

void Enemy::Render()
{
	for (int i = 0; i <= (imgSize / 5) * (size / maxSize); i++)
	{
		IMAGE->ReBegin(false, false);
		img->CenterRender(Vector3(vPos.x, myY + i, vPos.z), { 90,bodyRot,0 }, { plusSize + (size / maxSize),plusSize + (size / maxSize) ,1 }, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		IMAGE->ReBegin(false, false);

	}
	if (num != 1)
	{
		IMAGE->ReBegin(false, true);
		//RECT rc = {0,0,0,0};
		if (num == 2)
		{
			RECT rc = { 0,0, 283 * (OBJECT->enemy2Hp / OBJECT->enemy2MaxHp),57 };
			IMAGE->FindImage(L"EnemyHp")->Render({ vPos.x- 30, 60, vPos.z }, { 0,0,0 }, { 0.3f * (size / maxSize),-0.3f * (size / maxSize),1 }, rc);
		}
		else if (num == 3)
		{
			RECT rc = { 0,0, 283 * (OBJECT->enemy3Hp / OBJECT->enemy3MaxHp),57 };
			IMAGE->FindImage(L"EnemyHp")->Render({ vPos.x - 30, 60, vPos.z }, { 0,0,0 }, { 0.3f * (size / maxSize),-0.3f * (size / maxSize),1 }, rc);
		}
		else if (num == 4)
		{
			RECT rc = { 0,0, 283 * (OBJECT->enemy4Hp / OBJECT->enemy4MaxHp),57 };
			IMAGE->FindImage(L"EnemyHp")->Render({ vPos.x - 30, 60, vPos.z }, { 0,0,0 }, { 0.3f * (size / maxSize),-0.3f * (size / maxSize),1 }, rc);
		}
		
		IMAGE->ReBegin(false, false);
	}
}

void Enemy::Release()
{
}
