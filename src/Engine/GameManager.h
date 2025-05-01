#pragma once

#include <list>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>


struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;

class Entity;
class Scene;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}



class GameManager
{

	sf::RenderWindow* m_pWindow;

	bool m_isRunning = true;

	sf::View m_cameraCustom = {};
	bool m_useCustomCamera = false;
	bool m_viewHastoBeUpdated = false;

	Scene* m_pActiveScene;

	std::list<Scene*> m_sceneList = {};
	std::list<Scene*> m_sceneToDestroy = {};
	std::list<Scene*> m_loadedScene = {};

	float mDeltaTime;

	bool m_changeActiveScene;
	Scene* m_pNewActiveScene;

	float m_accumulatedTime;
	float m_checkfpsTime;

	int m_fps;

	float m_tickTimeElapsed = 0.0f;

	bool m_onPause = false;


private:
	GameManager();

	void Run();
	
	void HandleEvent();
	void Update();
	void FixedUpdate();
	void Draw();
	void UpdateViewCamera();
	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }
	void UpdateTickEvent();

	bool IsRunning();

	void CheckScene();

public:
	~GameManager();
	static GameManager* Get();

	void CreateNewWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60);
	sf::RenderWindow* GetWindow() const { return m_pWindow; }

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetActiveScene() const { return m_pActiveScene; }

	void PauseGame(bool state) { m_onPause = state; }

	void SetCameraPos(sf::Vector2f pos);
	void SetCameraViewSize(sf::Vector2f size);
	void ZoomCamera(float ratio);

	void UseCustomCamera();
	void UseDefaultCamera();

	void LoadScene(Scene* pScene);
	void UnloadScene(Scene* pScene);

	template<typename T>
	T* CreateScene();

	void SetActiveScene(Scene* pScene);

	sf::Vector2i GetMousePosCenter();

	sf::Vector2u GetWindowSize();

	void Quit();

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"