#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	:nowScene(nullptr), nextScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	Release();
}

Scene* SceneManager::AddScene(const string& key, Scene* scenePtr)
{
	if (!scenePtr) return nullptr;
	if (sceneMap.find(key) != sceneMap.end()) return nullptr;
	sceneMap.insert(make_pair(key, scenePtr));
	return scenePtr;
}

Scene* SceneManager::ChageScene(const string& key)
{
	auto find = sceneMap.find(key);
	if (find == sceneMap.end()) return nullptr;

	OBJECT->ClearAllObject();

	nextScene = find->second;
	return nextScene;
}

void SceneManager::Update()
{

	if (nextScene)
	{
		if (nowScene) nowScene->Release();
		nextScene->Init();
		nowScene = nextScene;
		nextScene = nullptr;
	}
	if (nowScene) nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene) {

		nowScene->Render();
	}
}

void SceneManager::Release()
{
	if (nowScene) nowScene->Release();

	for (auto iter : sceneMap) SAFE_DELETE(iter.second);

	sceneMap.clear();
}
