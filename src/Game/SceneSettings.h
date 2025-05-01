#pragma once
////
////#include "Entity.h"
////#include "ButtonMenu.h"
////
////class SceneTest;
////class ScenePause;
////
////class ReturnButton : public Button
////{
////	bool m_isClicked = false;
////
////public:
////	void OnClick() override;
////
////	friend ScenePause;
////};
////
////class MainMenuButton : public Button
////{
////
////public:
////	void OnClick() override;
////};
////
////class ScenePause : public Entity
////{
////	// 4 (5) Buttons (Return, Save ,Settings, MainMenu, Quit)
////	
////	UIText* m_pTitle = nullptr; // Pause
////
////	ReturnButton* m_pReturnButton = nullptr;
////	SettingsButton* m_pSettigns = nullptr;
////	MainMenuButton* m_pMainMenu = nullptr;
////	QuitButton* m_pQuit = nullptr;
////
////	UIEntity* m_pBackGround = nullptr;
////
////	bool m_isClosed = false;
////	// 1/3
////public:
////	void Init();
////
////	void OnUpdate() override;
////
////	void OpenMenu();
////	void CloseMenu();
////
////	friend SceneTest;
////
////};
////
