#include "pch.h"

#include <vector>

Chunk::Chunk()
{
    m_isDrawable = false;
    m_name = "Chunk";
}

void Chunk::Init(int tileCount, Entity* tileover)
{
    m_tileCount = tileCount;
    m_tiles = std::vector<std::vector<Tile*>>(tileCount);
    for (int i = 0; i < tileCount; i++)
    {
        m_tiles[i] = std::vector<Tile*>(tileCount);
        for (int j = 0; j < tileCount; j++)
        {
            m_tiles[i][j] = CreateEntity<Tile>();
            m_tiles[i][j]->Init(m_pMap, this, tileover);
            m_tiles[i][j]->SetPosition(m_pos.x + (i * 64.0f), m_pos.y + (j * 64.0f), 0.f, 0.0f);
            m_tiles[i][j]->SetOrderInVector(i,j);
        }
    }
}

int Chunk::GetTileCount()
{
    return m_tileCount;
}

Tile* Chunk::GetTile(int x, int y)
{
    return m_tiles[x][y];
}

sf::Vector2i Chunk::GetPosInList()
{
    return m_posInList;
}

Map* Chunk::GetMap()
{
    return m_pMap;
}
