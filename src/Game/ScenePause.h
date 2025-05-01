#pragma once

#include "Scene.h"
#include "ButtonMenu.h"

class SceneTest;
class ScenePause;
class UIText;

class ReturnButton : public Button
{
	bool m_isClicked = false;
	UIText* m_pText = nullptr;

public:
	void Init();

	void OnClick() override;

	friend ScenePause;
};

class SettingsButtonPause : public Button
{
	UIText* m_pText = nullptr;

public:
	void Init();

	void OnClick() override {};

	friend ScenePause;
};

class MainMenuButton : public Button
{

	UIText* m_pText = nullptr;
public:

	void Init();
	void OnClick() override;
};

class QuitButtonPause : public Button
{
	UIText* m_pText = nullptr;

public:
	void Init();

	void OnClick() override {};

	friend ScenePause;
};

class ScenePause : public Scene
{
	
	SceneTest* m_pGameScene = nullptr;

	UIText* m_pTitle = nullptr; // Pause

	ReturnButton* m_pReturnButton = nullptr;
	SettingsButtonPause* m_pSettigns = nullptr;
	MainMenuButton* m_pMainMenu = nullptr;
	QuitButtonPause* m_pQuit = nullptr;

	UIEntity* m_pBackGround = nullptr;

	bool m_isClosed = false;

	int m_canLeave = 0;

public:
	void OnInitialize() override;
	void SetGameScene(SceneTest* pScene);

	void OnUpdate() override;
	void OnEvent(std::optional<sf::Event> pEvent) override;

	friend SceneTest;

};

