#include "pch.h"
#include "Machine.h"
#include "Pipe.h"

void Machine::OnFixedUpdate()
{
	m_wasCollidingLastFrame = false;
}

Machine::Machine()
{
	m_name = "Machine";
	SetLayer(4);
	SetSpriteTexture("PlacedMachine");
}

void Machine::UpdateObject()
{
	if (m_allPipeSelected)
		MachineEffect();
}

void Machine::Init(int width, int height)
{
	PlaceableObject::Init(width, height);
	m_pText = m_pScene->CreateUIText();
	m_pText->SetColor(sf::Color::White);
	m_pText->SetSize(30);
	m_pText->SetText("Press E To Open Machine");
	m_pText->Hide();
	m_pText->SetPosOnCanva({ GameManager::Get()->GetWindowSize().x * 0.5f, GameManager::Get()->GetWindowSize().y - 150.0f });
	//SetScale(width, height);
}

void Machine::RotateObjectClockWise()
{
}

void Machine::ReceiveProp(Prop* pProp)
{
	//
}

bool Machine::AllPipeSelected()
{
	return m_allPipeSelected;
}

bool Machine::IsUIOpen()
{
	return m_isUIOopen;
}

void Machine::OpenMachineUI()
{
}

void Machine::HasCollisionWithPlayer()
{
	m_wasCollidingLastFrame = true;
}
