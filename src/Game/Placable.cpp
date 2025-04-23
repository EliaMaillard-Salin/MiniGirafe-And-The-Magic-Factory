#include "pch.h"

#include "Placable.h"
#include "SceneTest.h"

PlaceableObject::PlaceableObject()
{
	m_tag = SceneTest::MACHINE;
}

void PlaceableObject::Init(int width, int height)
{
	m_widthInTiles = width;
	m_heightInTiles = height;

	m_width = width * 64.0f;
	m_height = height * 64.0f;
	m_layer = 4;
	m_isDrawable = true;
}

void PlaceableObject::OnUpdate()
{
	if (m_onGround)
	{
		UpdateObject();
		return;
	}

	SceneTest* MyScene = GetScene<SceneTest>();//a changer le get scene
	Tile* pTileUnderMouse = MyScene->GetTileOver();
	int tilecount = MyScene->GetTileCount();
	m_canBePlaced = false;

	if (pTileUnderMouse != nullptr)
	{
		if (GetTag() == SceneTest::GAME_TAG::PIPE) {
			SetPosition(pTileUnderMouse->GetPosition().x, pTileUnderMouse->GetPosition().y);
			if (m_pSprite != nullptr) {
				m_pSprite->setPosition({ pTileUnderMouse->GetPosition().x, pTileUnderMouse->GetPosition().y });
			}
		}
		else
			SetPosition(pTileUnderMouse->GetPosition(0.0f,0.0f).x, pTileUnderMouse->GetPosition(0.0f,0.0f).y, 0, 0);
		if (pTileUnderMouse->GetPosInChunk().x + m_widthInTiles - 1 != tilecount && pTileUnderMouse->GetPosInChunk().y + m_widthInTiles - 1 != tilecount)
			m_canBePlaced = CheckPlaceCondition(pTileUnderMouse);
	}

	if (m_canBePlaced)
		SetSpriteTexture("PlacedMachine");
	else
		SetSpriteTexture("CantPlaceMachine");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && m_canBeRotated && m_Rtoggle) {
		RotateObjectClockWise();
		m_Rtoggle = false;
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))) {
		m_Rtoggle = true;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_canBePlaced)
	{
		m_onGround = true;
		m_pTileOfMachine = pTileUnderMouse;
		m_pTileOfMachine->SetObjectOnTile(this);
		PlaceObject();
	}
}

void PlaceableObject::SetTileOfMachine(Tile* pTile)
{
	m_pTileOfMachine = pTile;
}

sf::Vector2i PlaceableObject::GetTilePosition()
{
	return m_pTileOfMachine->GetPosInChunk();
}

