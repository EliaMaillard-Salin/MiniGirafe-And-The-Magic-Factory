#include "pch.h"
#include "Wand.h"
#include "Scene.h"
#include "Player.h"

void Wand::Init(Scene* pScene, Player* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pText = pScene->CreateUIText();
	m_pText->SetColor(sf::Color::White);
	m_pText->SetSize(30);
	m_pText->SetText("Press E To Farm");
	m_pText->SetPosOnCanva({ GameManager::Get()->GetWindowSize().x * 0.5f, GameManager::Get()->GetWindowSize().y -150.0f });
}

void Wand::SetFarmTarget(RessourcesProp* pProp)
{
	if (pProp == nullptr)
		return;

	m_canFarm = true;
	m_pFarmTarget = pProp;
	Draw();
}

void Wand::Update()
{
	m_isFarming = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		m_isFarming = true;

	if (m_tickToFarm <= 0)
		Farm();

	if (m_canFarm == false)
		Hide();
}

void Wand::Farm()
{
	m_pPlayer->AddRessourcesInInventory((Prop*)m_pFarmTarget);
	m_tickToFarm = 10;
}

void Wand::Hide()
{
	m_pText->Hide();
}

void Wand::Draw()
{
	m_pText->Draw();
}
