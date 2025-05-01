#pragma once

#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	//_ASSERT(m_pActiveScene == nullptr);

	T* newScene = new T();

	m_pActiveScene = newScene;
	newScene->LoadAssets();
	newScene->OnInitialize();
	m_sceneList.push_back(newScene);
	LoadScene(newScene);
	Run();
}

template<typename T>
T* GameManager::CreateScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	//_ASSERT(m_pActiveScene == nullptr);

	T* newScene = new T();

	newScene->LoadAssets();
	newScene->OnInitialize();
	m_sceneList.push_back(newScene);

	return newScene;
}
