#pragma once
#include "Scene.h"
#include <thread>

enum Type
{
	LTWO,
	LTHREE
};

struct Load
{
public:
	Load(const wstring& key, const wstring& path, int size = 0) : key(key), path(path), size(size) { }
	virtual ~Load() {}

	wstring key, path;
	int size = 0;
};

class LoadingScene :
	public Scene
{
public:
	LoadingScene();
	virtual ~LoadingScene();

	bool ThreadEnable;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void Release() override;

	void ImageLoad(const wstring& key, const wstring& path, Type tp, int size = 0);
	int imageCount = 0;
	int maxImageCount = 0;
	list<Load> imageList;
	list<Load> aniList;
	list<Load> meshList;

	vector<thread> ImageThread;
	vector<thread> AniThread;
	vector<thread> MeshThread;
	texture* img;
	Timer* delay;
};

