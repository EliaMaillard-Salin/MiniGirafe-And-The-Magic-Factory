#pragma once

#include <list>

class UIEntity;
class Entity;

namespace sf {
	class RenderWindow;
}

class UICanva
{
	int m_maxLayer = 6;

	bool m_hasmoved = false;
	std::vector<std::list<UIEntity*>> m_uiElementByLayer = std::vector<std::list<UIEntity*>>(m_maxLayer);

	sf::RenderWindow* m_pWindow = nullptr;

public: 

	UICanva();
	~UICanva() = default;

	void Draw();
	void AddUIElement(Entity* pEntity);
	void RemoveUIElement(UIEntity* pEntity);

	void ChangeEntityLayer(UIEntity* pEntity, int newLayer);

	void UpdateUIPos();

	void MoveCanva();
};

