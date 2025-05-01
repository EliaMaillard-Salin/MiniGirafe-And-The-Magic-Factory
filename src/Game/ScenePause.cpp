#include "pch.h"
#include "SceneTest.h"
#include "ScenePause.h"
#include "Text.h"
#include "Shape.h"

void ReturnButton::Init()
{
	m_pText = m_pScene->CreateUIText();
	m_pText->SetText("Return");
	m_pText->SetFont("Magic.ttf");
	m_pText->SetColor(sf::Color::Black);
	m_pText->SetSize(80);
	m_pText->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y });
	m_pText->Draw();
}

void ReturnButton::OnClick()
{
	m_isClicked = true;
}

void ScenePause::OnInitialize()
{
	// BG + Title
	// 3 Buttons
	//
	sf::Vector2u winSize = GameManager::Get()->GetWindowSize();
	sf::RenderWindow* m_pWindow = GameManager::Get()->GetWindow();

	m_pBackGround = CreateEntity<UIEntity>();
	m_pBackGround->SetUIVisible();
	m_pBackGround->SetSpriteTexture("PauseMenu");
	m_pBackGround->SetPosOnCanva({ (m_pBackGround->GetWidth() * 0.5f), winSize.y * 0.5f });

	float offset = winSize.y * 0.15f;
	float start = winSize.y * 0.30f;


	// #TODO 1920 1080 placement

	m_pReturnButton = CreateEntity<ReturnButton>();
	m_pReturnButton->SetSize(160.0f, 75.0f);
	m_pReturnButton->SetPosOnCanva({(m_pBackGround->GetWidth() * 0.5f), start + offset *0});
	m_pReturnButton->Init();

	m_pSettigns = CreateEntity<SettingsButtonPause>();
	m_pSettigns->SetSize(200.0f, 75.0f);
	m_pSettigns->SetPosOnCanva({ (m_pBackGround->GetWidth() * 0.5f), start + offset * 1});
	m_pSettigns->Init();

	m_pMainMenu = CreateEntity<MainMenuButton>();
	m_pMainMenu->SetSize(295.0f, 75.0f);
	m_pMainMenu->SetPosOnCanva({ (m_pBackGround->GetWidth() * 0.5f),start + offset * 2});
	m_pMainMenu->Init();

	m_pQuit = CreateEntity<QuitButtonPause>();
	m_pQuit->SetSize(115.0f, 75.0f);
	m_pQuit->SetPosOnCanva({ (m_pBackGround->GetWidth() * 0.5f),start + offset * 3 });
	m_pQuit->Init();


	m_updateUI = true;
}

void ScenePause::SetGameScene(SceneTest* pScene)
{
	m_pGameScene = pScene;
}


void ScenePause::OnUpdate()
{
	if (m_pReturnButton->m_isClicked == true)
	{
		m_isClosed = true;
		m_pGameScene->UnpauseGame();
		m_pReturnButton->m_isClicked = false;
	}
}

void ScenePause::OnEvent(std::optional<sf::Event> pEvent)
{
	if (pEvent->is<sf::Event::KeyPressed>())
	{
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
		{
			m_isClosed = true;
			m_pGameScene->UnpauseGame();
		}
	}
}


void MainMenuButton::Init()
{
	m_pText = m_pScene->CreateUIText();
	m_pText->SetText("Main Menu");
	m_pText->SetFont("Magic.ttf");
	m_pText->SetColor(sf::Color::Black);
	m_pText->SetSize(80);
	m_pText->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y });
	m_pText->Draw();
}

void MainMenuButton::OnClick()
{
	GetScene<SceneTest>()->SwitchScene();
}

void SettingsButtonPause::Init()
{
	m_pText = m_pScene->CreateUIText();
	m_pText->SetText("Settings");
	m_pText->SetFont("Magic.ttf");
	m_pText->SetColor(sf::Color::Black);
	m_pText->SetSize(80);
	m_pText->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y });
	m_pText->Draw();
}

void QuitButtonPause::Init()
{
	m_pText = m_pScene->CreateUIText();
	m_pText->SetText("Quit");
	m_pText->SetFont("Magic.ttf");
	m_pText->SetColor(sf::Color::Black);
	m_pText->SetSize(80);
	m_pText->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y });
	m_pText->Draw();
}
