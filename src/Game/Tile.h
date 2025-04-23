#pragma once

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
#include <list>

class Prop;
struct Map;
class Pipe;
class Chunk;

class Tile : public Entity
{

    sf::Sprite* m_pSpriteOver = nullptr;
    sf::Sprite* m_pSpriteNotOver = nullptr;

    float size = 10.0f;
    bool m_hasCollision = false;
    Entity* m_pObjectOnTile = nullptr;

    std::list<Pipe*> m_pPipesOnTile = {};

    int m_x;
    int m_y;
    
    Map* m_pMap = nullptr;
    Chunk* m_pChunk = nullptr;
    Entity* m_tileover = nullptr;

public:
    Tile();
    ~Tile();

    void Init(Map* pMap, Chunk* pChunk,Entity* tileover);

    void SetObjectOnTile(Entity* pProp);
    void SetOrderInVector(int x, int y);

    Entity* GetObjectOnTile();

    std::list<Pipe*> GetPipesOnTile();

    void OnUpdate() override;

    void AddPipe(Pipe* pPipe);

    sf::Vector2i GetPosInChunk();

    Chunk* GetChunk();
    Map* GetMap();
};
