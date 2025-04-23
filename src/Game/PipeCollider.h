#pragma once

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Tile;
class Pipe;

class PipeCollider : public Entity
{
public:
	Pipe* m_pipe = nullptr;

	float m_relativex;
	float m_relativey;

	PipeCollider();
	~PipeCollider() = default;

	void OnUpdate() override;

	void Init(Pipe* mpipe, float relativex, float relativey, float w, float h, bool IsWall);

	void RotateCW(float angle);
};

