#pragma once

#include "UIEntity.h"
class GrimoirePages;
class Grimoire;

class BookMark : public UIEntity
{
	int m_idInGrimoireList = -1;
	Grimoire* m_pGrimoire = nullptr;
	float m_leftpos = 0.0f;
	float m_rightpos = 0.0f;
	float m_heightpos = 0.0f;

public:
	BookMark();
	~BookMark() = default;

	void Init(const char* texturePath, int id, Grimoire* pGrimoire, float leftpos, float rightpos, float height);

	void GoLeft();
	void GoRight();
	void OnUpdate() override;

	friend GrimoirePages;
};

