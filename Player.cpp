#include "DXUT.h"
#include "Player.h"
#include "Effect.h"
#include "PlayerBullet.h"
#include "Bomb.h"
void Player::Init()
{
	vSize = { 1,1,1 };
	pimg = IMAGE->FindImage(L"player");
	speed = 2;
	hp = 5;
	maxHp = 5;
	srand(time(NULL));
	vPos.x = rand() % 499;
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			OBJECT->map[i][j] = 0;
		}
	}
	for (int i = 0; i < 500; i++)
	{
		OBJECT->map[0][i] = 3;
		OBJECT->map[MAPSIZEX - 1][i] = 3;
		OBJECT->map[i][0] = 3;
		OBJECT->map[i][MAPSIZEZ - 1] = 3;
	}
	invinT = new Timer;
	attackT = new Timer;
	shootT = new Timer;
	OBJECT->AddObject(new Effect(9, 10), vPos, RenderType::TWO);
	moveHp = 5;
	maxMoveHp = 5;

	noMove = new Timer;
	noMove->SetTimer(3.f);
	stageT = new Timer;
	stageT->SetTimer(1.f);
	stageC = 180;
	gameOverT = new Timer;
	gameOverT->SetTimer(1.f);
	gameOverC = 10;
	shoot3MoveT = new Timer;
}

void Player::Update()
{
	if (stageT->Update())
	{
		if (stageC > 0)
			stageC--;
		else
		{
			stageC = 0;
			OBJECT->AddObject(new Effect(3), vPos, RenderType::TWO);
			OBJECT->timeScale = 0;
		}
		stageCtext = L"제한시간 : " + to_wstring(stageC) + L"초";
	}
	if (INPUT->KeyDown(VK_F1))
	{
		OBJECT->cheet1 = !OBJECT->cheet1;
	}
	if (INPUT->KeyDown(VK_F2))
	{
		SOUND->Copy("Skill", 1000);
		int randomItem = rand() % 7 + 1;
		if (randomItem == 1)
		{
			itemStr = L"Speed Buff";
			speed = 3;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
			shootC = 0;
		}
		else if (randomItem == 2)
		{
			itemStr = L"Invin Buff";
			speed = 2;
			invinT->SetTimer(1.0f);
			invinC = 10;
			invin = true;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
			shootC = 0;
		}
		else if (randomItem == 3)
		{
			itemStr = L"Hp Buff";
			speed = 2;
			invin = false;
			if (hp >= 5)
			{
				hp = 5;
				OBJECT->score += 300;
				OBJECT->hpItemScore += 300;
			}
			else
			{
				hp++;
				if (hp >= 5)
				{
					hp = 5;
				}
			}
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
			shootC = 0;
		}
		else if (randomItem == 4)
		{
			itemStr = L"Shoot1 Buff 5초";
			speed = 2;
			invin = false;
			shoot1 = true;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
			attackT->SetTimer(0.3f);
			shootT->SetTimer(1.f);
			shootC = 5;
		}
		else if (randomItem == 5)
		{
			itemStr = L"Shoot2 Buff 5초";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = true;
			shoot3 = false;
			shoot4 = false;
			attackT->SetTimer(0.7f);
			shootT->SetTimer(1.f);
			shootC = 5;
		}
		else if (randomItem == 6)
		{
			itemStr = L"Shoot3 Buff";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = true;
			shoot4 = false;
			shootC = 0;
		}
		else if (randomItem == 7)
		{
			itemStr = L"Shoot4 Buff";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = true;
			shootC = 0;
		}
	}
	if (INPUT->KeyDown(VK_F3))
	{
		hp++;
		if (hp > 5)
			hp = 5;
	}
	if (INPUT->KeyDown(VK_F4))
	{
		hp--;
		if (hp <= 0) {
			OBJECT->gameOver = true;
			hp = 0;
		}
	}
	if (INPUT->KeyDown(VK_F5))
	{
		moveHp++;
		if (moveHp > 5)
			moveHp = 5;
	}
	if (INPUT->KeyDown(VK_F6))
	{
		moveHp--;
		if (moveHp < 0) {
			moveHp = 0;
			if (areaPlus)
				BackEvent();
		}
	}
	if (!OBJECT->gameOver)
	{
		if (invin) {
			OBJECT->playerDie = false;
			if (invinT->Update())
			{
				invinC--;
			}
			if (invinC > 0)
				itemStr = L"Invin Buff " + to_wstring(invinC) + L"초";
			else {
				invinC = 0;
				invin = false;
				itemStr = L"No Buff";

			}
		}
		if (shootC > 0)
		{
			if (shootT->Update())
			{
				shootC--;
				if (shoot1)
					itemStr = L"Shoot1 Buff " + to_wstring(shootC) + L"초";
				else if (shoot2)
					itemStr = L"Shoot2 Buff " + to_wstring(shootC) + L"초";

				if (shootC <= 0)
				{
					shootC = 0;
					shoot1 = false;
					shoot2 = false;
					shoot3 = false;
					shoot4 = false;
					itemStr = L"No Buff";
					if (!areaPlus)
						BackEvent();
				}

			}
		}
		if (OBJECT->playerDie && !invin)
		{
			if (hp > 1)
			{
				hp--;
				OBJECT->playerDie = false;
				OBJECT->AddObject(new Effect(1), vPos, RenderType::TWO);
				BackEvent();
			}
			else
			{
				OBJECT->playerDie = false;
				hp = 0;
				OBJECT->gameOver = true;
				if (!areaPlus)
					BackEvent();
			}

		}
		else
		{
			if (shoot4)
			{
				if (INPUT->KeyDown(VK_SPACE))
				{
					shoot4 = false;
					OBJECT->AddObject(new Bomb(), vPos, RenderType::THREE);
					BackEvent();
					itemStr = L"No Buff";
				}
			}
			if (!reTry && !shoot3Move) {

				Move();
				if (shoot3)
				{
					if (INPUT->KeyDown(VK_SPACE))
					{
						shoot3Move = true;
						shoot3MoveT->SetTimer(2.f);
					}
				}
			}
			if (shoot3Move)
			{
				OBJECT->AddObject(new PlayerBullet(3, moveDir), { vPos.x + moveDir.x * 10,vPos.y,vPos.z + moveDir.z }, RenderType::TWO);
				if (shoot3MoveT->Update())
				{
					shoot3Move = false;
					shoot3 = false;
					itemStr = L"No Buff";
					BackEvent();
				}
			}
		}

	}
	else
	{
		OBJECT->timeScale = 0;

		if (OBJECT->coin > 0)
		{
			reTry = true;
			if (gameOverT->Update())
			{
				if (gameOverC > 0)
					gameOverC--;

			}
			if (gameOverC <= 0)
			{
				gameOverC = 0;
				if (!playerDes) {
					playerDes = true;
					OBJECT->AddObject(new Effect(3), vPos, RenderType::TWO);
				}
				reTry = false;
			}
			gameOverText = to_wstring(gameOverC);

			if (INPUT->KeyDown(VK_SPACE)) {
				OBJECT->coin--;
				hp = 5;
				moveHp = 5;
				BackEvent();
				reTry = false;
				OBJECT->timeScale = 1;
				OBJECT->gameOver = false;
			}
		}
		else
		{
			if (!playerDes) {
				playerDes = true;
				OBJECT->AddObject(new Effect(3), vPos, RenderType::TWO);
			}
		}
	}

}

void Player::Render()
{
	IMAGE->ReBegin(true, false);
	IMAGE->FindImage(L"UiBase")->CenterRender(Vector3(WINSIZEX / 2, 135, 0));
	RECT rrect = { 0,0,317 * (hp / maxHp),42 };
	RECT grect = { 0,0,317 * (moveHp / maxMoveHp),42 };
	IMAGE->FindImage(L"rgague")->Render(Vector3(300, 65, 0), { 0,0,0 }, { 1,1,1 }, rrect);
	IMAGE->FindImage(L"ggague")->Render(Vector3(330, 170, 0), { 0,0,0 }, { 1,1,1 }, grect);
	if (OBJECT->cheet1)
		IMAGE->TextDraw(L"무적", { WINSIZEX / 2, 600,0 }, 100, D3DCOLOR_XRGB(255, 0, 0), true);
	IMAGE->TextDraw(L"Me : " + OBJECT->percentText, { WINSIZEX / 2- 140, 500,0 }, 60, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->TextDraw(L"Boss : " + OBJECT->bossPercentText, { WINSIZEX / 2 + 140, 500,0 }, 60, D3DCOLOR_XRGB(255, 0, 0), true);
	IMAGE->TextDraw(to_wstring(OBJECT->score) + L" Score", { WINSIZEX / 2, 200,0 }, 100, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->TextDraw(itemStr, { 1500, 200,0 }, 100, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->TextDraw(stageCtext, { 360, 1900,0 }, 100, D3DCOLOR_XRGB(0, 0, 255), true);
	IMAGE->ReBegin(false, false);
	for (int i = 0; i < 5; i++)
	{
		IMAGE->ReBegin(false, false);

		pimg->CenterRender(vPos + Vector3(0, 4 + i, 0), { 90,imgDir,0 });
		IMAGE->ReBegin(false, false);

	}
	if (reTry)
	{
		IMAGE->ReBegin(true, false);
		IMAGE->FindImage(L"ReTry")->CenterRender({ WINSIZEX / 2, WINSIZEY / 2 ,0 });
		IMAGE->FINDVECIMAGE(L"Count")->FINDIMAGE(gameOverC)->CenterRender({ WINSIZEX / 2, WINSIZEY / 2 ,0 });
	}
	IMAGE->ReBegin(false, false);
}

void Player::Release()
{
	SAFE_DELETE(invinT);
	SAFE_DELETE(attackT);
	SAFE_DELETE(shootT);
	SAFE_DELETE(noMove);
	SAFE_DELETE(gameOverT);
	SAFE_DELETE(stageT);
	SAFE_DELETE(shoot3MoveT);
}

void Player::Move()
{
	if (INPUT->KeyPress(VK_UP) && vPos.z != MAPSIZEZ - 1)
	{
		imgDir = 180;
		int temp;
		if (vPos.z + speed > (MAPSIZEZ - 1))
		{
			temp = (MAPSIZEZ - 1) - vPos.z;
		}
		else
		{
			temp = speed;
		}
		int searchUp = OBJECT->map[(int)vPos.x][(int)vPos.z + temp];
		switch (searchUp)
		{
		case 0:
		case 10:

			if (INPUT->KeyPress(VK_SPACE))
			{
				if (!areaPlus)
				{
					areaPlus = true;
					vStart = vPos;
				}
				vPos.z += temp;
				for (int i = 0; i < temp; i++)
				{
					if (OBJECT->map[(int)vPos.x][(int)vPos.z - i] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z - i] == 10)
						OBJECT->map[(int)vPos.x][(int)vPos.z - i] = 1;
				}
			}
			break;
		case 2:


			if (OBJECT->map[(int)vPos.x][(int)vPos.z + 1] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z + 1] == 10)
			{
				vPos.z += 1;
				OBJECT->map[(int)vPos.x][(int)vPos.z + 1] = 1;
			}
			else if (OBJECT->map[(int)vPos.x][(int)vPos.z + 1] == 3)
			{
				vPos.z += 1;
				if (areaPlus)
				{
					AreaPlus(1);
				}
			}
			else
			{
				if (shoot1 || shoot2 || shoot3 || shoot4) {
					if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 3)
						vStart = vPos;
					vPos.z += temp;
				}
			}
			break;
		case 3:
			vPos.z += temp;
			for (int i = 0; i < temp; i++)
			{
				if (OBJECT->map[(int)vPos.x][(int)vPos.z - i] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z - i] == 10)
					OBJECT->map[(int)vPos.x][(int)vPos.z - i] = 3;
			}

			if (areaPlus) {
				AreaPlus(1);
			}
			break;
		case 7:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		}
		moveDir = { 0,0,1 };

	}
	else if (INPUT->KeyPress(VK_DOWN) && vPos.z != 0)
	{
		imgDir = 0;

		int temp;
		if (vPos.z - speed < 0)
		{
			temp = vPos.z;
		}
		else
		{
			temp = speed;
		}
		int searchDown = OBJECT->map[(int)vPos.x][(int)vPos.z - temp];
		switch (searchDown)
		{
		case 0:
		case 10:

			if (INPUT->KeyPress(VK_SPACE))
			{
				if (!areaPlus)
				{
					areaPlus = true;
					vStart = vPos;
				}
				vPos.z -= temp;
				for (int i = 0; i < temp; i++)
				{
					if (OBJECT->map[(int)vPos.x][(int)vPos.z + i] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z + i] == 10)
						OBJECT->map[(int)vPos.x][(int)vPos.z + i] = 1;
				}
			}
			break;
		case 2:

			if (OBJECT->map[(int)vPos.x][(int)vPos.z - 1] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z - 1] == 10)
			{
				vPos.z -= 1;
				OBJECT->map[(int)vPos.x][(int)vPos.z] = 1;
			}
			else if (OBJECT->map[(int)vPos.x][(int)vPos.z - 1] == 3)
			{
				vPos.z -= 1;
				if (areaPlus)
				{
					AreaPlus(2);
				}
			}
			else
			{
				if (shoot1 || shoot2 || shoot3 || shoot4) {
					if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 3)
						vStart = vPos;
					vPos.z -= temp;
				}
			}
			break;
		case 3:
			vPos.z -= temp;
			for (int i = 0; i < temp; i++)
			{
				if (OBJECT->map[(int)vPos.x][(int)vPos.z + i] == 0 || OBJECT->map[(int)vPos.x][(int)vPos.z + i] == 10)
					OBJECT->map[(int)vPos.x][(int)vPos.z + i] = 3;
			}

			if (areaPlus) {
				AreaPlus(2);
			}
			break;
		case 7:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		}
		moveDir = { 0,0,-1 };

	}
	else if (INPUT->KeyPress(VK_RIGHT) && vPos.x != MAPSIZEX - 1)
	{
		imgDir = 270;

		int temp;
		if (vPos.x + speed > MAPSIZEX - 1)
		{
			temp = (MAPSIZEX - 1) - vPos.x;
		}
		else
		{
			temp = speed;
		}
		int searchRight = OBJECT->map[(int)vPos.x + temp][(int)vPos.z];
		switch (searchRight)
		{
		case 0:
		case 10:

			if (INPUT->KeyPress(VK_SPACE))
			{
				if (!areaPlus)
				{
					areaPlus = true;
					vStart = vPos;
				}
				vPos.x += temp;
				for (int i = 0; i < temp; i++)
				{
					if (OBJECT->map[(int)vPos.x - i][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x - i][(int)vPos.z] == 10)
						OBJECT->map[(int)vPos.x - i][(int)vPos.z] = 1;
				}
			}
			break;
		case 2:

			if (OBJECT->map[(int)vPos.x + 1][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x + 1][(int)vPos.z] == 10)
			{
				vPos.x += 1;
				OBJECT->map[(int)vPos.x][(int)vPos.z] = 1;
			}
			else if (OBJECT->map[(int)vPos.x + 1][(int)vPos.z] == 3)
			{
				vPos.x += 1;
				if (areaPlus)
				{
					AreaPlus(3);
				}
			}
			else
			{
				if (shoot1 || shoot2 || shoot3 || shoot4) {
					if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 3)
						vStart = vPos;
					vPos.x += temp;
				}
			}
			break;
		case 3:
			vPos.x += temp;
			for (int i = 0; i < temp; i++)
			{
				if (OBJECT->map[(int)vPos.x - i][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x - i][(int)vPos.z] == 10)
					OBJECT->map[(int)vPos.x - i][(int)vPos.z] = 3;
			}

			if (areaPlus) {
				AreaPlus(3);
			}
			break;
		case 7:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		}
		moveDir = { 1,0,0 };

	}
	else if (INPUT->KeyPress(VK_LEFT) && vPos.x != 0)
	{
		imgDir = 90;

		int temp;
		if (vPos.x - speed < 0)
		{
			temp = vPos.x;
		}
		else
		{
			temp = speed;
		}
		int searchLeft = OBJECT->map[(int)vPos.x - temp][(int)vPos.z];
		switch (searchLeft)
		{
		case 0:
		case 10:
			if (INPUT->KeyPress(VK_SPACE))
			{
				if (!areaPlus)
				{
					areaPlus = true;
					vStart = vPos;
				}
				vPos.x -= temp;
				for (int i = 0; i < temp; i++)
				{
					if (OBJECT->map[(int)vPos.x + i][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x + i][(int)vPos.z] == 10)
						OBJECT->map[(int)vPos.x + i][(int)vPos.z] = 1;
				}
			}
			break;
		case 2:

			if (OBJECT->map[(int)vPos.x - 1][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x - 1][(int)vPos.z] == 10)
			{
				vPos.x -= 1;
				OBJECT->map[(int)vPos.x][(int)vPos.z] = 1;
			}
			else if (OBJECT->map[(int)vPos.x - 1][(int)vPos.z] == 3)
			{
				vPos.x -= 1;
				if (areaPlus)
				{
					AreaPlus(4);
				}
			}
			else
			{
				if (shoot1 || shoot2 || shoot3 || shoot4) {
					if (OBJECT->map[(int)vPos.x][(int)vPos.z] == 3)
						vStart = vPos;
					vPos.x -= temp;
				}
			}
			break;
		case 3:
			vPos.x -= temp;
			for (int i = 0; i < temp; i++)
			{
				if (OBJECT->map[(int)vPos.x + i][(int)vPos.z] == 0 || OBJECT->map[(int)vPos.x + i][(int)vPos.z] == 10)
					OBJECT->map[(int)vPos.x + i][(int)vPos.z] = 3;
			}

			if (areaPlus) {
				AreaPlus(4);
			}
			break;
		case 7:
			if (!OBJECT->cheet1)
				OBJECT->playerDie = true;
			break;
		}
		moveDir = { -1,0,0 };
	}
	if (areaPlus && !INPUT->KeyPress(VK_SPACE))
	{
		BackEvent();
	}
	if (areaPlus)
	{
		if (moveHp > 0)
			moveHp -= 0.015f;
		else
		{
			moveHp = 0;
			BackEvent();
		}
		noMove->SetTimer(3.f);
		noMoveb = false;
	}
	else
	{
		if (moveHp < 5)
			moveHp += 0.03f;
		else
			moveHp = 5;
		if (noMove->Update())
		{
			noMoveb = true;
		}
		if (noMoveb && !invin && !OBJECT->cheet1)
		{
			hp -= 0.005f;
			if (hp <= 0)
			{
				hp = 0;
				OBJECT->gameOver = true;
			}
		}

	}
	if (shoot1)
	{
		if (INPUT->KeyPress(VK_SPACE))
		{
			if (attackT->Update())
			{
				OBJECT->AddObject(new PlayerBullet(1, moveDir), vPos, RenderType::TWO);
			}
		}
	}
	else if (shoot2)
	{
		if (INPUT->KeyPress(VK_SPACE))
		{
			if (attackT->Update())
			{
				OBJECT->AddObject(new PlayerBullet(2, { 1,0,0 }), vPos, RenderType::TWO);
				OBJECT->AddObject(new PlayerBullet(2, { -1,0,0 }), vPos, RenderType::TWO);
				OBJECT->AddObject(new PlayerBullet(2, { 0,0,1 }), vPos, RenderType::TWO);
				OBJECT->AddObject(new PlayerBullet(2, { 0,0,-1 }), vPos, RenderType::TWO);
			}
		}
	}
}

void Player::BackEvent()
{
	MATH->BackFloodFill(vPos.x, vPos.z);
	vPos = vStart;
	areaPlus = false;
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			if (OBJECT->map[i][j] == 6) OBJECT->map[i][j] = 0;
		}

	}
	OBJECT->AddObject(new Effect(9, 10), vPos, RenderType::TWO);
}

void Player::AreaPlus(int num)
{
	int bossCount = 0;
	int prevP, nowP, result = 0;
	Vector3 dir, dir2 = { 0,0,0 };
	areaPlus = false;
	for (int i = 0; i < MAPSIZEX; i++)
	{
		for (int j = 0; j < MAPSIZEZ; j++)
		{
			if (OBJECT->map[i][j] == 1) {
				OBJECT->map[i][j] = 3;
			}
		}
	}
	switch (num)
	{
	case 1:
		dir = { 1,0,-1 };
		dir2 = { -1,0,-1 };
		break;
	case 2:
		dir = { 1,0,1 };
		dir2 = { -1,0,1 };
		break;
	case 3:
		dir = { -1,0,1 };
		dir2 = { -1,0,-1 };
		break;
	case 4:
		dir = { 1,0,1 };
		dir2 = { 1,0,-1 };
		break;
	}

	MATH->SearchFloodFill(vPos.x + dir.x, vPos.z + dir.z, bossCount);

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			if (OBJECT->map[i][j] == 5)	OBJECT->map[i][j] = 0;
			else if (OBJECT->map[i][j] == 11)	OBJECT->map[i][j] = 10;
		}
	}

	prevP = OBJECT->GetPercent();

	if (bossCount > 0)
		MATH->FloodFill(vPos.x + dir2.x, vPos.z + dir2.z);
	else
		MATH->FloodFill(vPos.x + dir.x, vPos.z + dir.z);

	if (vPos.x < 200)
	{
		SOUND->Copy("Area", 1000, -10000);
	}
	else if (vPos.x > 300)
	{
		SOUND->Copy("Area", 1000, 10000);
	}
	else
	{
		SOUND->Copy("Area", 1000, 0);
	}
	OBJECT->SetPercent();
	nowP = OBJECT->GetPercent();
	result = nowP - prevP;

	OBJECT->areaScore += result * 100;
	if (result >= 2)
	{
		int randomItem = rand() % 7 + 1;
		if (randomItem == 1 && OBJECT->speedItem > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->speedItem--;
			itemStr = L"Speed Buff";
			speed = 3;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
		}

		else if (randomItem == 2 && OBJECT->invinItem > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->invinItem--;
			itemStr = L"Invin Buff";
			speed = 2;
			invinT->SetTimer(1.0f);
			invinC = 10;
			invin = true;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
		}
		else if (randomItem == 3 && OBJECT->hpItem > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->hpItem--;
			itemStr = L"Hp Buff";
			speed = 2;
			invin = false;
			if (hp >= 5)
			{
				hp = 5;

				OBJECT->hpItemScore += 300;
			}
			else
			{
				hp++;
				if (hp >= 5)
				{
					hp = 5;
				}
			}
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
		}
		else if (randomItem == 4 && OBJECT->shoot1Item > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->shoot1Item--;
			itemStr = L"Shoot1 Buff 5초";
			speed = 2;
			invin = false;
			shoot1 = true;
			shoot2 = false;
			shoot3 = false;
			shoot4 = false;
			attackT->SetTimer(0.3f);
			shootT->SetTimer(1.f);
			shootC = 5;
		}
		else if (randomItem == 5 && OBJECT->shoot2Item > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->shoot2Item--;
			itemStr = L"Shoot2 Buff 5초";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = true;
			shoot3 = false;
			shoot4 = false;
			attackT->SetTimer(0.7f);
			shootT->SetTimer(1.f);
			shootC = 5;

		}
		else if (randomItem == 6 && OBJECT->shoot3Item > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->shoot3Item--;
			itemStr = L"Shoot3 Buff";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = true;
			shoot4 = false;
		}
		else if (randomItem == 7 && OBJECT->shoot4Item > 0)
		{
			SOUND->Copy("Skill", 1000);
			OBJECT->shoot4Item--;
			itemStr = L"Shoot4 Buff";
			speed = 2;
			invin = false;
			shoot1 = false;
			shoot2 = false;
			shoot3 = false;
			shoot4 = true;
		}

	}
}
