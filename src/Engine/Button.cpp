#include "pch.h"
#include "Button.h"

void Button::SetButtonDetected(sf::Mouse::Button button)
{
	m_buttonDetected = button;
}

void Button::OnUpdate()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*GameManager::Get()->GetWindow());
	auto mouseworldPos = GameManager::Get()->GetWindow()->mapPixelToCoords(mousePos);

	if (IsInside(mouseworldPos.x, mouseworldPos.y) && sf::Mouse::isButtonPressed(m_buttonDetected))
		OnClick();
}
