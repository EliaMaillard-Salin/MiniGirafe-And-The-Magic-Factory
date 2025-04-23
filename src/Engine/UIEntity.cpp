#include "pch.h"
#include "UIEntity.h"

UIEntity::UIEntity()
{
	m_isUI = true;
	m_isDrawable = false;
}

UIEntity::~UIEntity()
{
	m_listIterator = nullptr;
}

void UIEntity::Init()
{}

void UIEntity::SetPosOnCanva(sf::Vector2f pos)
{
	m_posOnCanva = pos;
}

sf::Vector2f UIEntity::GetPosOnCanva()
{
	return m_posOnCanva;
}

void UIEntity::SetUIVisible()
{
	m_uiIsDrawable = true;
}
void UIEntity::SetUIInvisible()
{
	m_uiIsDrawable = false;
}

void UIEntity::SetLayer(int layer)
{
	if (m_listIterator != nullptr)
		GetScene()->ChangeUIEntityLayer(this, layer);
	m_layer = layer;
}
