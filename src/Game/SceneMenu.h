#pragma once

#include "Scene.h"
#include "ButtonMenu.h"

class UIText;
class SceneTest;

class SceneMenu : public Scene
{
	UIText* m_pTitle = nullptr;
	PlayButton* m_pPlay = nullptr;
	SettingsButton* m_pSettigns = nullptr;
	QuitButton* m_pQuit = nullptr;
	
	SceneTest* m_pPlayScene = nullptr;

public:
	SceneMenu() = default;
	~SceneMenu();

	void LoadAssets() override {};
	void OnInitialize() override;
	void OnUpdate() override {};
	void OnFixedUpdate() override {};

	void SwitchScene();
};

