#pragma once
#include "Entity.h"

#include "Wand.h"

class Inventory;

class Player :  public Entity
{
	Wand m_wand = {};

	Inventory* m_pInventory = nullptr;

	bool m_wasCollidingLastFrame = false;

public:
	Player();
	~Player() = default;

	void Init();
	void OnUpdate() override;
	void OnEvent(std::optional<sf::Event> pEvent);
	void OnFixedUpdate() override;
	void OnTick() override;

	void OnCollision(Entity* pEntity) override;

	void AddRessourcesInInventory(Prop* pEntity);

};

