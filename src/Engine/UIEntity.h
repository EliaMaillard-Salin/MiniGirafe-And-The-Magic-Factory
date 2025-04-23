#pragma once
#include <SFML/System/Vector2.hpp>

#include "Entity.h"

class UICanva;

class UIEntity : public Entity
{

protected:
	std::list<UIEntity*>::iterator* m_listIterator = nullptr;
	bool m_uiIsDrawable = false;

	sf::Vector2f m_posOnCanva = sf::Vector2f(0.0f, 0.0f);

public:
	UIEntity();
	virtual ~UIEntity();

	void Init();

	void SetPosOnCanva(sf::Vector2f pos);
	sf::Vector2f GetPosOnCanva();

	void SetUIVisible();
	void SetUIInvisible();

	void SetLayer(int layer);

	friend UICanva;
};
