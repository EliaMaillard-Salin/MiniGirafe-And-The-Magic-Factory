#include "pch.h"
#include "ButtonMenu.h"
#include "SceneMenu.h"

PlayButton::~PlayButton()
{
	if (m_pTitle != nullptr)
		m_pTitle->Destroy();
	m_pTitle = nullptr;
}

void PlayButton::Init(std::string text)
{
	m_pTitle = m_pScene->CreateUIText();
	m_pTitle->SetText(text);
	m_pTitle->SetFont("Magic.ttf");
	m_pTitle->SetColor(sf::Color::Black);
	m_pTitle->SetSize(80);
	m_pTitle->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y - 30.0f });
	m_pTitle->Draw();
}

void PlayButton::OnClick()
{
	GetScene<SceneMenu>()->SwitchScene();
}

QuitButton::~QuitButton()
{
	if (m_pTitle != nullptr)
		m_pTitle->Destroy();
	m_pTitle = nullptr;
}

void QuitButton::Init(std::string text)
{
	m_pTitle = m_pScene->CreateUIText();
	m_pTitle->SetText(text);
	m_pTitle->SetFont("Magic.ttf");
	m_pTitle->SetColor(sf::Color::Black);
	m_pTitle->SetSize(80);
	m_pTitle->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y - 50.0f });
	m_pTitle->Draw();
}

SettingsButton::~SettingsButton()
{
	if (m_pTitle != nullptr)
		m_pTitle->Destroy();
	m_pTitle = nullptr;
}

void SettingsButton::Init(std::string text)
{
	m_pTitle = m_pScene->CreateUIText();
	m_pTitle->SetText(text);
	m_pTitle->SetFont("Magic.ttf");
	m_pTitle->SetColor(sf::Color::Black);
	m_pTitle->SetSize(80);
	m_pTitle->SetPosOnCanva({ m_posOnCanva.x, m_posOnCanva.y - 50.0f });
	m_pTitle->Draw();
}
