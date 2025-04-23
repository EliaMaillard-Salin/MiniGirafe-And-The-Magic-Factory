#pragma once

#include "Placable.h"

class Prop;
class Machine;

namespace sf
{
	class Sprite;
}

class Pipe : public PlaceableObject // ADD Animation
{
public:
private:
	bool m_hasProp = false;

	bool m_isFull = false;

	int m_count = 0;
	int m_maxItem = 2;

	Pipe* m_pIn = nullptr;
	Pipe* m_pOut = nullptr;

	Prop* m_pProp = nullptr;

	IN_OUT_SIDE m_inSide = LEFT;
	IN_OUT_SIDE m_outSide = RIGHT;
	
	sf::Texture* m_pHasResources = nullptr;
	sf::Texture* m_pPipeEmpty = nullptr;

	float m_elapsedTimeTogive = 0.0f;
	float m_transferSpeed = 0.5f;

	std::vector<PipeCollider*> m_listcolliders;
public:
	Pipe();
	~Pipe() = default;

	void Init(IN_OUT_SIDE in = LEFT, IN_OUT_SIDE out = RIGHT);

	bool CheckPlaceCondition(Tile* pTile);

	void UpdateObject() override; // Transfers to Out
	void PlaceObject() override;
	void RotateObjectClockWise() override;

	void ReceiveProp(Prop* pProp);

	Pipe::IN_OUT_SIDE GetOutPos();
	Pipe::IN_OUT_SIDE GetInPos();

	void ConnectInPipe(Pipe* pPipe);
	void ConnectOutPipe(Pipe* pPipe);

	Pipe* GetpIn();
	Pipe* GetpOut();

	Prop* GiveProp();

	Prop* GetPropInPipe();

	bool CheckIfCanReceive(Prop* pProp);

	friend class Machine;
};

