#include "pch.h"

#include "Player.h"
#include "Shape.h"
#include "SceneTest.h"
#include "RessourcesSpawner.h"
#include "Inventory.h"
#include "DecantingMachine.h"

Player::Player()
{
	m_isDrawable = true;
	m_hasCollision = true;
	m_name = "Player";
	m_hasTickEvent = true;
	SetLayer(5);
	SetSpriteTexture("Player");
	AddTagWithoutCollision(SceneTest::GAME_TAG::PIPEWALL);
}


void Player::Init()
{
	GameManager* pGameManager = GameManager::Get();
	pGameManager->UseCustomCamera();
	pGameManager->SetCameraPos(m_pos);
	pGameManager->SetCameraViewSize(sf::Vector2f(pGameManager->GetWindowSize()));
	m_wand.Init(m_pScene, this);
	m_pInventory = GetScene<SceneTest>()->GetInventory();

}

void Player::OnUpdate()
{
	GameManager::Get()->SetCameraPos(m_pos);
	if (m_pSprite != nullptr) {
		m_pSprite->setPosition(m_pos);
	}

	if (m_wasCollidingLastFrame == false)
	{
		m_wand.m_canFarm = false;
	}
	m_wand.Update();
}


void Player::OnEvent(std::optional<sf::Event> pEvent)
{
}

void Player::OnFixedUpdate()
{
	sf::Vector2f tmp = { 0,0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		tmp.y += -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		tmp.x += -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		tmp.y += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		tmp.x += 1.f;
	}

	if (tmp.x != 0.f || tmp.y != 0.f) {
		Utils::Normalize(tmp);
	}

	SetVelocity(tmp * 500.f);

	m_wasCollidingLastFrame = false;
}

void Player::OnTick()
{
	if (m_wand.m_isFarming)
		m_wand.m_tickToFarm -= 1;
}

void Player::OnCollision(Entity* pEntity)
{
	if (pEntity->GetTag() == SceneTest::GAME_TAG::RESOURCE_SPAWNER)
	{
		if (m_wand.m_canFarm == false)
		{
			RessourcesSpawner* pResSpawn = dynamic_cast<RessourcesSpawner*>(pEntity);
			m_wand.SetFarmTarget(pResSpawn->GetProp());
		}
		m_wasCollidingLastFrame = true;
	}

	if (pEntity->GetTag() == (SceneTest::GAME_TAG::MACHINE))
	{
		Machine* pMachine = dynamic_cast<Machine*>(pEntity);
		pMachine->DrawUI();
		if (pMachine->IsUIOpen() == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			pMachine->OpenMachineUI();
		}
		pMachine->HasCollisionWithPlayer();
	}
}

void Player::AddRessourcesInInventory(Prop* pEntity)
{
	if (m_pInventory->AddElementInInventory(pEntity, 1) == false)
	{
		// Print Inventory Full
	}
}
