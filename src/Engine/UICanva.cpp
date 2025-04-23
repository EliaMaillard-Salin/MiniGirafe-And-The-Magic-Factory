#include "pch.h"
#include "UICanva.h"
#include "UIEntity.h"

UICanva::UICanva() : m_pWindow(GameManager::Get()->GetWindow())
{}


void UICanva::Draw()
{
	for (std::list<UIEntity*> pEntityLayer : m_uiElementByLayer)
	{
		for (UIEntity* pEntity : pEntityLayer)
		{
			if (pEntity->m_uiIsDrawable)
			{
				m_pWindow->draw(*pEntity->GetSprite());
			}
		}
	}
}

void UICanva::AddUIElement(Entity* pEntity)
{
	UIEntity* pUIEntity = dynamic_cast<UIEntity*>(pEntity);
	m_uiElementByLayer[pUIEntity->m_layer].push_back(pUIEntity);
	pUIEntity->m_listIterator = &--m_uiElementByLayer[pUIEntity->m_layer].end();
}

void UICanva::RemoveUIElement(UIEntity* pEntity)
{
	m_uiElementByLayer[pEntity->GetLayer()].remove(pEntity);
}

void UICanva::ChangeEntityLayer(UIEntity* pEntity, int newLayer)
{
	if (newLayer >= m_maxLayer) {
		std::cout << "Max Layer is" << m_maxLayer << std::endl;
		return;
	}

	m_uiElementByLayer[pEntity->GetLayer()].remove(pEntity);
	m_uiElementByLayer[newLayer].push_back(pEntity);
	pEntity->m_listIterator = &--m_uiElementByLayer[newLayer].end();
}

void UICanva::UpdateUIPos()
{
	for (std::list<UIEntity*> pEntityLayer : m_uiElementByLayer)
	{
		for (UIEntity* pEntity : pEntityLayer)
		{
			sf::Vector2f posOnCanva = pEntity->m_posOnCanva;
			posOnCanva.x += m_pWindow->getView().getCenter().x - (m_pWindow->getView().getSize().x * 0.5f);
			posOnCanva.y += m_pWindow->getView().getCenter().y - (m_pWindow->getView().getSize().y * 0.5f);
			pEntity->SetPosition(posOnCanva.x, posOnCanva.y, 0.5f, 0.5f);
		}
	}
}

void UICanva::MoveCanva()
{
	m_hasmoved = true;
}
