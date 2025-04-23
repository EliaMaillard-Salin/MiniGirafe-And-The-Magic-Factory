#include "pch.h"
#include "GameManager.h"

#include "Entity.h"
#include "AssetManager.h"
#include <string>


GameManager::GameManager()
{
	m_accumulatedTime = 0.0f;
	m_checkfpsTime = 0.0f;
	m_fps = 0;
	m_pWindow = nullptr;
	mDeltaTime = 0.0f;
	m_pActiveScene = nullptr;
	m_changeActiveScene = false;
	m_pNewActiveScene = nullptr;
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

void GameManager::CreateNewWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit)
{
	_ASSERT(m_pWindow == nullptr);

	m_pWindow = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), title);
	m_pWindow->setFramerateLimit(fpsLimit);

}


GameManager::~GameManager()
{
	 delete m_pWindow;
	
	 for (Scene* scene : m_sceneList)
	 {
	 	delete scene;
	 }
	 m_sceneList.clear();
}

void GameManager::SetCameraPos(sf::Vector2f pos)
{
	m_cameraCustom.setCenter(pos);
	m_viewHastoBeUpdated = true;
}

void GameManager::SetCameraViewSize(sf::Vector2f size)
{
	m_cameraCustom.setSize(size);
	m_viewHastoBeUpdated = true;
}

void GameManager::ZoomCamera(float ratio)
{
	m_cameraCustom.zoom(ratio);
	m_viewHastoBeUpdated = true;
}

void GameManager::UseCustomCamera()
{
	m_useCustomCamera = true;
	m_viewHastoBeUpdated = true;
}

void GameManager::UseDefaultCamera()
{
	m_useCustomCamera = false;
}

void GameManager::SetActiveScene(Scene* pScene)
{
	m_changeActiveScene = true;
	m_pNewActiveScene = pScene;
}

sf::Vector2i GameManager::GetMousePosCenter()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	mousePos.x += m_pWindow->getView().getCenter().x - (m_pWindow->getView().getSize().x * 0.5f) - 7.f;
	mousePos.y += m_pWindow->getView().getCenter().y - (m_pWindow->getView().getSize().y * 0.5f) - 30.f;

	return mousePos;
}

sf::Vector2u GameManager::GetWindowSize()
{
	return m_pWindow->getSize();
}


void GameManager::Run()
{
	if (m_pWindow == nullptr)
	{
		std::cout << "Window not created, creating SFML default window" << std::endl;
		CreateNewWindow(1280, 720, "Default window");
	}

	_ASSERT(m_pActiveScene != nullptr);

	sf::Clock clock;
	
	while (m_pWindow->isOpen())
	{
		float dt = clock.restart().asSeconds();
		SetDeltaTime(dt);
		
		m_fps += 1;

		if (m_onPause)
		{
			GameManager::Get()->mDeltaTime = 0.f;
			m_accumulatedTime = 0.f;
		}

		m_accumulatedTime += dt;
		m_tickTimeElapsed += dt;
		//m_checkfpsTime += dt;

		HandleEvent();

		if (m_tickTimeElapsed >= TICK_TIME)
		{
			UpdateTickEvent();
			m_tickTimeElapsed = 0.0f;
		}

		Update();

		m_pActiveScene->m_fps = 1/dt;

	/*	while (m_checkfpsTime >= 1.f)
		{
			m_pActiveScene->m_fps = m_fps;
			m_fps -= m_fps;
			m_checkfpsTime -= 1.f;
		}*/

		if (m_accumulatedTime > FIXED_DT)
		{
			
			FixedUpdate();
			m_accumulatedTime = 0.0f;
		}
		
		
		Draw();

		// ADD "TickManager"
	}

	m_pWindow->close();

}

void GameManager::HandleEvent()
{
	while ( std::optional event = m_pWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_pWindow->close();

		if (auto* resized = event->getIf<sf::Event::Resized>())
		{
			// update the view to the new size of the window

			sf::Vector2f BaseSize = m_pWindow->getDefaultView().getSize();
			sf::Vector2f BaseCenter = m_pWindow->getDefaultView().getCenter();

			sf::Vector2f NewSize(resized->size);

			//{ BaseCenter.x - BaseSize.x/2 + (BaseSize.x/2 - NewSize.x/2), BaseCenter.y - BaseSize.y / 2 + (BaseSize.y / 2 - NewSize.y / 2) }

			SetCameraViewSize(NewSize);
		}

		m_pActiveScene->HandleEvent(event);
	}
}

void GameManager::Update()
{
	if (m_changeActiveScene)
	{	
		//m_pActiveScene->UnloadScene();
		m_pActiveScene = m_pNewActiveScene;
		m_pNewActiveScene = nullptr;
		m_changeActiveScene = false;
	}
	
	m_pActiveScene->Update();
}

void GameManager::FixedUpdate()
{
	m_pActiveScene->FixedUpdate();


}

void GameManager::Draw()
{
	m_pWindow->clear(m_pActiveScene->m_backGroundColor);
	
	UpdateViewCamera();
	m_pActiveScene->Draw(m_pWindow);

	m_pWindow->display();
}

void GameManager::UpdateViewCamera()
{
	if (m_useCustomCamera == false)
		return;

	if (m_viewHastoBeUpdated)
	{
		m_pWindow->setView(m_cameraCustom);
		m_viewHastoBeUpdated = false;
		m_pActiveScene->m_updateUI = true;
	}
}

void GameManager::UpdateTickEvent()
{
	m_pActiveScene->CallTickEvent();
}
