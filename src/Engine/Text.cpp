#include "pch.h"
#include "Text.h"
#include "AssetManager.h"
#include "GameManager.h"


UIText::UIText()
{
	m_isUI = true;
}

void UIText::SetPosOnCanva(sf::Vector2f posOnCanva)
{
	m_posOnCanva = posOnCanva;
}

Text::Text()
{
	m_pText = new sf::Text(*AssetManager::GetFont("arial.ttf"), "");
	m_pText->setCharacterSize(30);
}

Text::~Text()
{
	delete m_pText;
}


void Text::SetText(std::string str)
{
	m_pText->setString(str);
}

void Text::Draw()
{
	m_isDrawable = true;
}

void Text::Hide()
{
	m_isDrawable = false;
}

void Text::SetPosition(sf::Vector2f pos)
{
	pos.x -= m_pText->getGlobalBounds().size.x * 0.5f;
	pos.y -= m_pText->getGlobalBounds().size.y * 0.5f;
	m_pos = pos;
	m_pText->setPosition(pos);
}

void Text::SetFont(const char* fontName)
{
	m_pText->setFont(*AssetManager::GetFont(fontName));
}

void Text::SetSize(int size)
{
	m_pText->setCharacterSize(size);
}

void Text::SetColor(sf::Color color)
{
	m_pText->setFillColor(color);
}

void Text::SetOutline(sf::Color color , int thickness)
{
	m_pText->setOutlineColor(color);
	m_pText->setOutlineThickness(thickness);

}

void Text::Destroy()
{
	m_pScene->DeleteText(this);
}