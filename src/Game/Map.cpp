#include "pch.h"

void Map::Init(Scene* pScene, Entity* tileover, int rows, int cols, int tileCountInChunk)
{
    m_chunks = std::vector<std::vector<Chunk*>>(rows);
    for (int i = 0; i < rows; i++)
    {
        m_chunks[i] = std::vector<Chunk*>(cols);
        for (int j = 0; j < cols; j++)
        {
            m_chunks[i][j] = pScene->CreateEntity<Chunk>();
            m_chunks[i][j]->m_pMap = this;
            m_chunks[i][j]->SetPosition(i* (64.0f * tileCountInChunk), j* (64.0f * tileCountInChunk),0.f,0.0f);
            m_chunks[i][j]->Init(tileCountInChunk, tileover);
            m_chunks[i][j]->m_posInList = sf::Vector2i(i, j);
        }
    }
}

