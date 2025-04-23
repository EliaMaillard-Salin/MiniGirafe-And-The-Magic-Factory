#pragma once

#include "Machine.h"
#include <SFML/System/Vector2.hpp>

class WoodFarmer : public Machine
{

private:
	int m_maxitemcount = 5;

	int m_itemCount = 0;

	int m_speedInTick = 5;

	Prop* m_pProp = nullptr;

	bool m_pipePlaced = false;

	PipePosInMachine m_outPipePos = TOP_RIGHT;

protected:
	bool CheckPlaceCondition(Tile* pTile) override;
	
public:
	WoodFarmer();
	virtual ~WoodFarmer() = default;

	void Init(int widht, int height);

	void MachineEffect() override;

	void OnTick() override;

	void PlaceObject() override;

	void SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide) override;

};


class PlantFarmer : public Machine
{

private:
	int m_itemCount = 0;

	int m_speedInTick = 5;

	Prop* m_pProp = nullptr;

	bool m_pipePlaced = false;

	PipePosInMachine m_outPipePos = TOP_RIGHT;

protected:
	bool CheckPlaceCondition(Tile* pTile) override;

public:
	PlantFarmer();
	virtual ~PlantFarmer() = default;

	void Init(int widht, int height);

	void MachineEffect() override;

	void OnTick() override;

	void PlaceObject() override;

	void SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide) override;
};

