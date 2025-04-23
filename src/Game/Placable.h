#pragma once

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Tile;
class Pipe;
class PipeCollider;

class PlaceableObject : public Entity
{
public:
	enum IN_OUT_SIDE : int
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};
private:



	bool m_canBePlaced = false;
	
	bool m_Rtoggle = false;

protected:
	bool m_onGround = false;

	int m_widthInTiles = 1;
	int m_heightInTiles = 1;

	Tile* m_pTileOfMachine = nullptr; // UpperLeft

	virtual bool CheckPlaceCondition(Tile* pTile) = 0;
	bool m_canBeRotated = false;
public :

	PlaceableObject();
	virtual ~PlaceableObject() = default;

	void Init(int width, int height);

	void OnUpdate() override;

	virtual void PlaceObject() = 0;
	virtual void RotateObjectClockWise() = 0;

	virtual void UpdateObject() = 0;

	void SetTileOfMachine(Tile* pTile);

	sf::Vector2i GetTilePosition();

};

