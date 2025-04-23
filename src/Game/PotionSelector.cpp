#include "pch.h"
#include "PotionSelector.h"
#include "DecantingMachine.h"
#include "Prop.h"


void PotionSelector::PotionSelected(POTION_TYPES potion)
{
	m_pMachine->ConfirmPotion(potion);
	Hide();
	m_isActive = false;
	m_pMachine = nullptr;
}

void PotionSelector::Init()
{
	SetSpriteTexture("PotionSelector");
	m_width = 320.0f;
	m_height = 512.0f;
}

void PotionSelector::AddAvailablePotion(POTION_TYPES potion)
{
	Potion* pPotion = CreateEntity<Potion>();
	pPotion->Init(potion);
	m_unlockedPotions.insert(std::pair<POTION_TYPES, Potion*>(potion, pPotion));
}

void PotionSelector::OnUpdate()
{
	sf::Vector2i mousePos = GameManager::Get()->GetMousePosCenter();
	for (auto pPotion : m_unlockedPotions)
	{
		if (pPotion.second->IsInside(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			PotionSelected(pPotion.first);
	}
}

void PotionSelector::Open(DecantingMachine* pMachine)
{
	m_isActive = true;
	Draw();
}

void PotionSelector::Draw()
{
	for (auto pPotion : m_unlockedPotions)
	{
		pPotion.second->SetUIVisible();
	}
	SetUIVisible();
}

void PotionSelector::Hide()
{
	for (auto pPotion : m_unlockedPotions)
	{
		pPotion.second->SetUIInvisible();
	}
	SetUIInvisible();
}

