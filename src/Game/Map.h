#pragma once

#include <vector>

class Chunk;
class Tile;
class Scene;

struct Map
{
    std::vector<std::vector<Chunk*>> m_chunks = {};
    Map() = default;
    virtual ~Map() = default;
    
    void Init(Scene* pScene, Entity* tileover, int rows = 4, int cols = 4, int tileCountInChunk = 15);

    
    Tile* m_pTileOver = nullptr;
};
