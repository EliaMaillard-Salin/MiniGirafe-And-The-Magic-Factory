#pragma once

#include "UIEntity.h"

namespace sf
{
	class Sprite;
}

class Prop : public UIEntity
{

protected:
	int m_ID = -1;

public:
	Prop() = default;
	~Prop() = default;

	int GetID();
};


class RessourcesProp : public Prop
{
public:
	enum PROP_STATE : int
	{
		RAW = 0,
		RAFFINE = 1000,
	};

protected:
	RESSOURCES_PROPS m_ressourceID = RESSOURCES_PROPS::PROPS_NONE;
	PROP_STATE m_state = RAW;
public:
	void Init(RESSOURCES_PROPS propID = RESSOURCES_PROPS::TREFLE, PROP_STATE propState = PROP_STATE::RAW);
};

class Potion : public Prop
{
protected:
	POTION_TYPES m_type = POTION_TYPES::POTION_NONE;

public:

	void Init(POTION_TYPES type);
};