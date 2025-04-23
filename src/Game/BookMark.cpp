#include "pch.h"
#include "BookMark.h"
#include "Grimoire.h"

BookMark::BookMark()
{
	m_name = "BookMark";
	SetLayer(1);
}

void BookMark::Init(const char* texturePath, int id, Grimoire* pGrimoire,float leftpos,float rightpos, float heightpos)
{
	SetSpriteTexture(texturePath);
	m_idInGrimoireList = id;
	m_pGrimoire = pGrimoire;
	m_leftpos = leftpos;
	m_rightpos = rightpos;
	m_heightpos = heightpos;
}

void BookMark::GoLeft()
{
	SetPosOnCanva({ m_leftpos,m_heightpos });
}

void BookMark::GoRight()
{
	SetPosOnCanva({ m_rightpos,m_heightpos });
}

void BookMark::OnUpdate()
{

	if (m_uiIsDrawable == false)
		return;

	sf::RenderWindow* pWindow = GameManager::Get()->GetWindow();

	sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);
	auto mouseworldPos = pWindow->mapPixelToCoords(mousePos);

	if (IsInside(mouseworldPos.x, mouseworldPos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_pGrimoire->SkipToPage(m_idInGrimoireList);

}
