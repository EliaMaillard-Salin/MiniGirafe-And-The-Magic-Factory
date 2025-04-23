#include "pch.h"
#include "SceneMenu.h"

#include "SceneTest.h"
#include "Text.h"
#include "ButtonMenu.h"

SceneMenu::~SceneMenu()
{
	m_pTitle = nullptr;
	m_pPlay = nullptr;
	m_pSettigns = nullptr;
	m_pQuit = nullptr;

	m_pPlayScene = nullptr;
}

void SceneMenu::OnInitialize()
{
	m_pPlayScene = GameManager::Get()->CreateScene<SceneTest>();
	m_pTitle = CreateUIText();
	m_pTitle->SetText("MINI GIRAFE AND THE MAGIC FACTORY");
	m_pTitle->SetColor(sf::Color::Black);
	m_pTitle->SetFont("Magic.ttf");
	m_pTitle->SetSize(100);
	sf::Vector2f posTile = sf::Vector2f(GameManager::Get()->GetWindowSize().x * 0.5f, 50.0f);
	m_pTitle->SetPosOnCanva(posTile);
	m_pTitle->Draw();

	sf::Vector2f winSize = (sf::Vector2f)GameManager::Get()->GetWindowSize();
	m_pPlay = CreateEntity<PlayButton>();
	m_pPlay->SetPosOnCanva({ winSize.x * 0.5f, winSize.y * 0.3f });
	m_pPlay->SetSpriteTexture("Buttons/Play");
	m_pPlay->Init("Play");

	m_pSettigns = CreateEntity<SettingsButton>();
	m_pSettigns->SetPosOnCanva({ winSize.x * 0.5f, winSize.y * 0.5f });
	m_pSettigns->SetSpriteTexture("Buttons/Settings");
	m_pSettigns->Init("Settings");

	m_pQuit = CreateEntity<QuitButton>();
	m_pQuit->SetPosOnCanva({ winSize.x * 0.5f, winSize.y * 0.7f });
	m_pQuit->SetSpriteTexture("Buttons/Quit");
	m_pQuit->Init("Quit");

	m_pPlay->SetUIVisible();
	m_pSettigns->SetUIVisible();
	m_pQuit->SetUIVisible();

	m_backGroundColor = sf::Color(219,172,107,255);
}

void SceneMenu::SwitchScene()
{
	GameManager::Get()->SetActiveScene(m_pPlayScene);
}
