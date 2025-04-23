#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>

class Tile;
struct Map;

class Chunk : public Entity
{

public:
    enum CHUNK_TYPE
    {
        PLAINS,
        FOREST,
        MOUNTAINS,
        VOLCAN,
        NONE,
    };

private:
    int posX = 0;
    int posY = 0;

    Map* m_pMap = nullptr;

    int m_tileCount = 0;

    std::vector<std::vector<Tile*>> m_tiles = {};

    sf::Vector2i m_posInList = sf::Vector2i(0,0);

    bool m_isUnlock = true;

    CHUNK_TYPE m_type;

public:

    Chunk();
    virtual ~Chunk() = default;
    
    void Init(int tileCount, Entity* tileover);

    int GetTileCount();

    Tile* GetTile(int x, int y);

    sf::Vector2i GetPosInList();

    Map* GetMap();

    friend Map;
};
