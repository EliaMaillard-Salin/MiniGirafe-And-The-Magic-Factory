#pragma once
#include "UIEntity.h"

class Button : public UIEntity
{
	sf::Mouse::Button m_buttonDetected = sf::Mouse::Button::Left;

public:
	Button() = default;
	virtual ~Button() = default;
	
	void SetButtonDetected(sf::Mouse::Button button);

	void OnUpdate() override;

	virtual void OnClick() = 0;
};