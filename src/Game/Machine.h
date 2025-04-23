#pragma once

#include "Placable.h"

#include <list>

class Pipe;
class Prop;


class Machine : public PlaceableObject
{
public:
	enum MACHINE_TAG : int
	{
		DECANTING_MACHINE = 50,
	};

protected:
	enum PipePosInMachine : int
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
	};
	
	bool m_hasProp = false;

	std::vector<std::vector<Tile*>> m_machineTiles = {};

	float m_elapsedTimeTogive = 0.0f;
	float m_transferSpeed = 0.5f;

	std::list<Pipe*> m_listInPipes = {};
	std::list<Pipe*> m_listOutPipes = {};

	bool m_allPipeSelected = false;

	bool m_isUIOopen = false;

	bool m_wasCollidingLastFrame = false;

	UIText* m_pText = nullptr;

	void UpdateObject() override;

	virtual void MachineEffect() = 0;

	void OnFixedUpdate() override;
public:
	Machine();
	~Machine() = default;


	virtual bool CheckPlaceCondition(Tile* pTile) = 0;
	
	void Init(int width, int height);

 // Transfers to Out
	void RotateObjectClockWise() override;

	void ReceiveProp(Prop* pProp);

	bool AllPipeSelected();

	virtual void SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide) = 0;

	virtual void DrawUI() {};

	bool IsUIOpen();

	virtual void OpenMachineUI();

	void HasCollisionWithPlayer();

};

