#pragma once

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Pipe;

class MovingItem : public Entity
{
public:

	Pipe* m_pPipeToGoTo = nullptr;

	std::vector<Entity*> doorpassed;

	MovingItem();
	~MovingItem() = default;

	void Init(const char* texturepath,int x,int y, Pipe* pipetogoto);

	void OnFixedUpdate() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
};

