#include "pch.h"
#include "Pipe.h"


Tile::Tile()
{
	m_isDrawable = true;
	SetLayer(0);

	if (rand() % 4 == 0) {
		SetSpriteTexture("Tile2");
	}
	else {
		SetSpriteTexture("Tile1");
	}
	
	m_pSpriteNotOver = GetSprite();

	m_pPipesOnTile = std::list<Pipe*>(0);

	m_x = 0;
	m_y = 0;

	

}

Tile::~Tile()
{
	delete m_pSpriteOver;
	delete m_pSpriteNotOver;
}

void Tile::Init(Map* pMap, Chunk* pChunk, Entity* tileover)
{
	m_pMap = pMap;
	m_pChunk = pChunk;
	m_tileover = tileover;
}

void Tile::SetObjectOnTile(Entity* pProp)
{
	m_pObjectOnTile = pProp;
}

void Tile::SetOrderInVector(int x, int y)
{
	m_x = x;
	m_y = y;
}

Entity* Tile::GetObjectOnTile()
{
	return m_pObjectOnTile;
}

std::list<Pipe*> Tile::GetPipesOnTile()
{
	return m_pPipesOnTile;
}

void Tile::OnUpdate()
{
	m_pSpriteNotOver->setPosition(m_pos);

	sf::RenderWindow* pWindow = GameManager::Get()->GetWindow();

	sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);
	auto mouseworldPos = pWindow->mapPixelToCoords(mousePos);

	if (IsInside(mouseworldPos.x, mouseworldPos.y)) {
		if (m_pMap->m_pTileOver == nullptr) {
			m_tileover->SetPosition(m_pos.x, m_pos.y, 0.f, 0.f);
			m_pMap->m_pTileOver = this;
		}
	}
	else {
		if (m_pMap->m_pTileOver == this) {
			m_tileover->SetPosition(-100000, -100000, 0.f, 0.f);
			m_pMap->m_pTileOver = nullptr;
		}
	}
		
}

void Tile::AddPipe(Pipe* pPipe)
{
	m_pPipesOnTile.push_back(pPipe);
}

sf::Vector2i Tile::GetPosInChunk()
{
	return sf::Vector2i(m_x,m_y);
}

Chunk* Tile::GetChunk()
{
	return m_pChunk;
}

Map* Tile::GetMap()
{
	return m_pMap;
}
