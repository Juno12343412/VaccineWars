#include "DXUT.h"
#include "LoadingScene.h"
#include <thread>
#include <mutex>

mutex ImageThreadMutex;
mutex AniThreadMutex;
mutex MeshThreadMutex;

LoadingScene::LoadingScene()
	:ThreadEnable(true)
{
	int ThreadCount = std::thread::hardware_concurrency();
	ImageThread.reserve(ThreadCount);
	AniThread.reserve(ThreadCount);
	MeshThread.reserve(ThreadCount);
	for (int i = 0; i < ThreadCount; ++i)
	{
		ImageThread.push_back(thread([this]() {
			while (ThreadEnable)
			{
				unique_lock<mutex> lock(ImageThreadMutex);
				if (imageList.empty())
					continue;

				auto front = imageList.front();
				imageList.pop_front();
				lock.unlock();

				IMAGE->AddImage(front.key, front.path);
				imageCount++;
			}
			}));

		AniThread.push_back(thread([this]() {
			while (ThreadEnable)
			{
				unique_lock<mutex> lock(AniThreadMutex);
				if (aniList.empty())
					continue;

				auto front = aniList.front();
				aniList.pop_front();
				lock.unlock();

				IMAGE->ADDVECIMAGE(front.key, front.path, front.size);
				imageCount++;
			}
			}));

		MeshThread.push_back(thread([this]() {
			while (ThreadEnable)
			{
				unique_lock<mutex> lock(MeshThreadMutex);
				if (meshList.empty())
					continue;

				auto front = meshList.front();
				meshList.pop_front();
				lock.unlock();

				IMAGE->AddMesh(front.key, front.path);
				imageCount++;
			}
			}));
	}

}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{
	CAMERA->Reset();
	delay = new Timer;
	delay->SetTimer(3.f);
	IMAGE->AddImage(L"loadingBg", L"Loading/Background");
	IMAGE->AddImage(L"loadingBar", L"Loading/LoadingBar");
	img = IMAGE->FindImage(L"loadingBg");
	ImageLoad(L"START", L"Title/START", Type::LTWO);
	ImageLoad(L"HOWTO", L"Title/HOWTO", Type::LTWO);
	ImageLoad(L"RANKING", L"Title/RANKING", Type::LTWO);
	ImageLoad(L"EXIT", L"Title/EXIT", Type::LTWO);
	ImageLoad(L"TitleBG", L"Title/Background", Type::LTWO);
	ImageLoad(L"HowToBG", L"Title/BackgroundHowTo", Type::LTWO);
	ImageLoad(L"RankingBG", L"Title/BackgroundRanking", Type::LTWO);
	ImageLoad(L"player", L"Player/Player", Type::LTWO);
	ImageLoad(L"map", L"Map/Map", Type::LTWO);
	ImageLoad(L"map2", L"Map/Map2", Type::LTWO);
	ImageLoad(L"drawMap", L"Map/DrawMap", Type::LTWO);
	ImageLoad(L"bossImage", L"Enemy/boss", Type::LTWO);
	ImageLoad(L"enemy1Image", L"Enemy/enemy1", Type::LTWO);
	ImageLoad(L"enemy2Image", L"Enemy/enemy2", Type::LTWO);
	ImageLoad(L"enemy3Image", L"Enemy/enemy3", Type::LTWO);
	ImageLoad(L"rock1", L"Rocks/(1)", Type::LTWO);
	ImageLoad(L"rock2", L"Rocks/(2)", Type::LTWO);
	ImageLoad(L"rock3", L"Rocks/(3)", Type::LTWO);
	ImageLoad(L"UiBase", L"Ui/UiBase", Type::LTWO);
	ImageLoad(L"fade", L"Ui/Background", Type::LTWO);
	ImageLoad(L"rgague", L"Ui/rgague", Type::LTWO);
	ImageLoad(L"ggague", L"Ui/ggague", Type::LTWO);
	ImageLoad(L"stageclear", L"Ui/StageClear", Type::LTWO);
	ImageLoad(L"youdied", L"Ui/YouDied", Type::LTWO);
	ImageLoad(L"explosion", L"Effects/explosion", Type::LTWO, 31);
	ImageLoad(L"BulletEffect", L"Effects/BulletEffect", Type::LTWO);
	ImageLoad(L"sky2", L"Sky/SpaceSky", Type::LTHREE);
	ImageLoad(L"sky1", L"Sky/EarthSky", Type::LTHREE);
	ImageLoad(L"earth", L"Earth/earth", Type::LTHREE);
	ImageLoad(L"earth2", L"Earth/earth2", Type::LTHREE);
	ImageLoad(L"earth3", L"Earth/earth3", Type::LTHREE);
	ImageLoad(L"human", L"Earth/human", Type::LTHREE);
	ImageLoad(L"human2", L"Earth/human2", Type::LTHREE);
	ImageLoad(L"human3", L"Earth/human3", Type::LTHREE);
	ImageLoad(L"Bomb", L"Bomb/Bomb", Type::LTHREE);
	ImageLoad(L"shield1", L"Effects/shield1", Type::LTWO);
	ImageLoad(L"shield2", L"Effects/shield2", Type::LTWO);
	ImageLoad(L"shield3", L"Effects/shield3", Type::LTWO);
	ImageLoad(L"Bullet1", L"Player/Bullet/Bullet1", Type::LTWO);
	ImageLoad(L"Bullet2", L"Player/Bullet/Bullet2", Type::LTWO);
	ImageLoad(L"ReTry", L"Ui/ReTry", Type::LTWO);
	ImageLoad(L"Count", L"Ui/Count", Type::LTWO, 10);
	ImageLoad(L"EnemyHp", L"Ui/EnemyHp", Type::LTWO);
	ImageLoad(L"BombWarning", L"Player/Bullet/BombWarning", Type::LTWO);
	ImageLoad(L"Intro1(0)", L"Intro/Intro1(0)", Type::LTWO);
	ImageLoad(L"Intro1(1)", L"Intro/Intro1(1)", Type::LTWO);
	ImageLoad(L"Intro1(2)", L"Intro/Intro1(2)", Type::LTWO);
	ImageLoad(L"Intro1(3)", L"Intro/Intro1(3)", Type::LTWO);
	ImageLoad(L"Intro2(0)", L"Intro/Intro2(0)", Type::LTWO);
	ImageLoad(L"Intro2(1)", L"Intro/Intro2(1)", Type::LTWO);
	ImageLoad(L"Intro2(2)", L"Intro/Intro2(2)", Type::LTWO);
	ImageLoad(L"Intro2(3)", L"Intro/Intro2(3)", Type::LTWO);
	ImageLoad(L"Intro2(4)", L"Intro/Intro2(4)", Type::LTWO);
	ImageLoad(L"Intro3(0)", L"Intro/Intro3(0)", Type::LTWO);
	ImageLoad(L"Intro3(1)", L"Intro/Intro3(1)", Type::LTWO);
	ImageLoad(L"Intro3(2)", L"Intro/Intro3(2)", Type::LTWO);
	ImageLoad(L"Intro3(3)", L"Intro/Intro3(3)", Type::LTWO);
	ImageLoad(L"Intro3(4)", L"Intro/Intro3(4)", Type::LTWO);
	ImageLoad(L"Intro3(5)", L"Intro/Intro3(5)", Type::LTWO);
	ImageLoad(L"BGIntro", L"Intro/Background", Type::LTWO);

	SOUND->AddSound("Main", L"./Resource/SOUND/Main Music 9000.wav");
	SOUND->AddSound("Start", L"./Resource/SOUND/Bell Ring 2.wav");
	SOUND->AddSound("Area", L"./Resource/SOUND/zone enter.wav");
	SOUND->AddSound("Shoot1", L"./Resource/SOUND/impact-4.wav");
	SOUND->AddSound("Shoot2", L"./Resource/SOUND/shoot.wav");
	SOUND->AddSound("Shoot3", L"./Resource/SOUND/TD EMP Idle.wav");
	SOUND->AddSound("Victory", L"./Resource/SOUND/TD Victory.wav");
	SOUND->AddSound("Explosion", L"./Resource/SOUND/explosion5.wav");
	SOUND->AddSound("Lose", L"./Resource/SOUND/TD Defeat.wav");
	SOUND->AddSound("Skill", L"./Resource/SOUND/Powerup Collect.wav");
}

void LoadingScene::Update()
{
	
	if (imageCount == maxImageCount)
	{
		if(delay->Update())
			SCENE->ChageScene("intro");
	}
}

void LoadingScene::Render()
{
	IMAGE->ReBegin(true, false);
	img->CenterRender(Vector3(WINSIZEX / 2, WINSIZEY / 2, 0));
	WCHAR a[20];
	wsprintf(a, L"Loading... %d/%d", imageCount, maxImageCount);
	IMAGE->TextDraw(a, Vector3(WINSIZEX / 2-270, WINSIZEY / 2, 0), 1000, D3DCOLOR_XRGB(255, 255, 255), false);
	RECT rc = {0,0,1000 * ((float)imageCount / (float)maxImageCount),100};
	IMAGE->FindImage(L"loadingBar")->Render({ WINSIZEX / 2 - 500, WINSIZEY / 2 + 300 ,0 }, { 0, 0, 0 }, { 1,1,1 }, rc);
	IMAGE->ReBegin(false, false);
}

void LoadingScene::Release()
{
	ThreadEnable = false;

	for (auto& iter : ImageThread)
	{
		iter.join();
	}
	for (auto& iter : AniThread)
	{
		iter.join();
	}
	for (auto& iter : MeshThread)
	{
		iter.join();
	}
	SAFE_DELETE(delay);
}

void LoadingScene::ImageLoad(const wstring& key, const wstring& path, Type tp, int size)
{
	if (tp == Type::LTWO)
	{
		if (size == 0)
		{
			lock_guard<mutex> lock(ImageThreadMutex);
			imageList.push_back(Load(key, path));
			maxImageCount++;
		}
		else
		{
			lock_guard<mutex> lock(AniThreadMutex);
			aniList.push_back(Load(key, path, size));
			maxImageCount++;
		}
	}
	else
	{
		lock_guard<mutex> lock(MeshThreadMutex);
		meshList.push_back(Load(key, path));
		maxImageCount++;
	}
}
