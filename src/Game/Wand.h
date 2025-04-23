#pragma once

class UIText;
class Player;
class RessourcesProp;

class Wand
{
	RessourcesProp* m_pFarmTarget = nullptr;

	bool m_canFarm = false;
	bool m_isFarming = false;

	int m_tickToFarm = 10;

	UIText* m_pText = nullptr;

	Player* m_pPlayer = nullptr;

public:
	Wand() = default;
	virtual ~Wand() = default;

	void Init(Scene* pScene, Player* pPlayer);

	void SetFarmTarget(RessourcesProp* pEntity);
	void Update();

	void Farm();

	void Hide();
	void Draw();

	friend class Player;
};

