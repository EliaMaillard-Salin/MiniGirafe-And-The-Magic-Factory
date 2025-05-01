#include "pch.h"
//#include "SceneTest.h"
//#include "PauseMenu.h"
//
//void ReturnButton::OnClick()
//{
//	m_isClicked = true;
//}
//
//void PauseMenu::Init()
//{
//	// BG + Title
//	// 3 Buttons
//	//
//	m_isActive = false;
//
//	sf::Vector2u winSize = GameManager::Get()->GetWindowSize();
//
//	m_pBackGround = CreateEntity<UIEntity>();
//	m_pBackGround->SetSpriteTexture("PauseMenu");
//	m_pBackGround->SetWidth(winSize.x * 0.3f);
//	m_pBackGround->SetHeight(winSize.y);
//	m_pBackGround->SetPosOnCanva({ winSize.x * 0.3f - (m_pBackGround->GetWidth() * 0.5f), winSize.y * 0.5f });
//
//	m_pReturnButton = CreateEntity<ReturnButton>();
//}
//
//void PauseMenu::OpenMenu()
//{
//	m_isActive = true;
//	m_pBackGround->SetUIVisible();
//}
//
//void PauseMenu::CloseMenu()
//{
//	m_isActive = false;
//}
//
//void PauseMenu::OnUpdate()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || m_pReturnButton->m_isClicked)
//		m_isClosed = true;
//
//}
//
//void MainMenuButton::OnClick()
//{
//	GetScene<SceneTest>()->SwitchScene();
//}
