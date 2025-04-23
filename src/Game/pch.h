#ifndef GAME_PCH_H
#define GAME_PCH_H

// Extern
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <map>
#include <list>


//Engine
#include "Utils.h"

#include "GameManager.h"
#include "Scene.h"
#include "AssetManager.h"
#include "AnimationManager.h"
#include "Animation.h"

//Entity
#include "Entity.h"
#include "UIEntity.h"
#include "Text.h"
#include "Button.h"


// Gameplay
//#include "SceneTest.h"
//#include "SceneMenu.h"
//#include "ButtonMenu.h"
//
#include "Map.h"
#include "Chunk.h"
#include "Tile.h"
//
//#include "Player.h"
//
//#include "Inventory.h"
//#include "Grimoire.h"
//#include "GrimoirePages.h"
//#include "BookMark.h"
//
//#include "MachineSelectPipe.h"
//#include "Placable.h"
//#include "Machine.h"
//#include "Pipe.h"
//#include "FarmingMachine.h"
//
//#include "Prop.h"

#pragma region PrefabResources

enum RESSOURCES_TYPES : int
{
	PLANT,
	TREE,
	ROCK,
};

enum RESSOURCES_BIOMES: int
{
	PLAINS,
	FOREST,
	MOUTAINS,
	VOLCAN,
};

enum RESSOURCES_RANK : int
{
	RANK_1,
	RANK_2,
	RANK_3,
};

enum RESSOURCES_PROPS : int
{
	TREFLE,
	MILLEPERTUIS,
	MUSHROOM,
	DATURA,
	ACONIT,
	AUBEPINE,
	EDELWEISS,
	PEYOTL,
	NUYTSIA_FLORIBUNDA,

	CHENE,
	SAULE,
	NOISETIER,
	AULNE,
	SUREAU,
	ERABLE,
	IF,
	SAPIN,
	HOUX,

	SILICE,
	ROCK_PROP,
	AVENTURINE,
	CITRINE,
	AMETHYSTE,
	AIGUE_MARINE,
	JASPE,
	QUARTZ,
	HELIOLITE,

	PROPS_COUNT,
	PROPS_NONE,
};

#pragma endregion

enum POTION_TYPES : int
{
	LUCK_I = RESSOURCES_PROPS::PROPS_COUNT,
	LUCK_II,
	LUCK_III,

	POTION_NONE,
	POTION_COUNT,
};

// Scrol start at POTION_TYPE::POTION_COUNT

#endif