#include "pch.h"

#include "Pipe.h"
#include "SceneTest.h"
#include "Machine.h"
#include "Prop.h"
#include "PipeCollider.h"

Pipe::Pipe()
{
	m_tag = SceneTest::PIPE;
	m_name = "Pipe";
	SetLayer(3);
}

void Pipe::Init(IN_OUT_SIDE in, IN_OUT_SIDE out)
{
	PlaceableObject::Init(1, 1);
	if (in == NONE)
	{
		if (out < 2)
			m_inSide = (IN_OUT_SIDE)(out + 2);
		if (out > 1)
			m_inSide = (IN_OUT_SIDE)(out - 2);
		m_outSide = out;
	}
	else if (out == NONE)
	{
		if (in < 2)
			m_outSide = (IN_OUT_SIDE)(in + 2);
		if (in > 1)
			m_outSide = (IN_OUT_SIDE)(in - 2);
		m_inSide = in;
	}
	else if (in != out)
	{
		m_inSide = in;
		m_outSide = out;
	}

	if ((m_outSide + 2) % 4 == m_inSide) {//straight
		PipeCollider* c1 = CreateEntity<PipeCollider>();
		c1->Init(this, 16, 0, 1, 64, true);
		PipeCollider* c2 = CreateEntity<PipeCollider>();
		c2->Init(this, -16, 0, 1, 64, true);
		PipeCollider* c3 = CreateEntity<PipeCollider>();
		c3->Init(this, 0, 32, 32, 1, false);

		for (int i = 0; i < m_inSide; i++) {
			c1->RotateCW(90);
			c2->RotateCW(90);
			c3->RotateCW(90);
		}

		m_listcolliders.push_back(c1);
		m_listcolliders.push_back(c2);
		m_listcolliders.push_back(c3);

	}
	else if(((m_inSide < m_outSide) || (m_inSide == 3) && (m_outSide == 0)) && !((m_inSide == 0) && (m_outSide == 3))){ //L 
		PipeCollider* c1 = CreateEntity<PipeCollider>();
		c1->Init(this, -16, -8, 1, 48, true);
		PipeCollider* c2 = CreateEntity<PipeCollider>();
		c2->Init(this, 8, 16, 48, 1, true);
		PipeCollider* c3 = CreateEntity<PipeCollider>();
		c3->Init(this, 16, -24, 1, 16, true);
		PipeCollider* c4 = CreateEntity<PipeCollider>();
		c4->Init(this, 24, -16, 16, 1, true);
		PipeCollider* c5 = CreateEntity<PipeCollider>();
		c5->Init(this, 32, 0, 1, 32, false);

		for (int i = 0; i < m_inSide; i++) {
			c1->RotateCW(90);
			c2->RotateCW(90);
			c3->RotateCW(90);
			c4->RotateCW(90);
			c5->RotateCW(90);
		}

		m_listcolliders.push_back(c1);
		m_listcolliders.push_back(c2);
		m_listcolliders.push_back(c3);
		m_listcolliders.push_back(c4);
		m_listcolliders.push_back(c5);

	}
	else {//inverted L
		PipeCollider* c1 = CreateEntity<PipeCollider>();
		c1->Init(this, 16, -8, 1, 48, true);
		PipeCollider* c2 = CreateEntity<PipeCollider>();
		c2->Init(this, -8, 16, 48, 1, true);
		PipeCollider* c3 = CreateEntity<PipeCollider>();
		c3->Init(this, -16, -24, 1, 16, true);
		PipeCollider* c4 = CreateEntity<PipeCollider>();
		c4->Init(this, -24, -16, 16, 1, true);
		PipeCollider* c5 = CreateEntity<PipeCollider>();
		c5->Init(this, -32, 0, 1, 32, false);

		for (int i = 0; i < in; i++) {
			c1->RotateCW(90);
			c2->RotateCW(90);
			c3->RotateCW(90);
			c4->RotateCW(90);
			c5->RotateCW(90);
		}

		m_listcolliders.push_back(c1);
		m_listcolliders.push_back(c2);
		m_listcolliders.push_back(c3);
		m_listcolliders.push_back(c4);
		m_listcolliders.push_back(c5);
		
	}
	std::string pipeImageType = "Pipes/Pipe_";

	pipeImageType += std::to_string(m_inSide);
	pipeImageType += "_";
	pipeImageType += std::to_string(m_outSide);

	m_pPipeEmpty = AssetManager::GetTexture(pipeImageType.c_str());
	m_canBeRotated = true;


	SetSpriteTexture(m_pPipeEmpty);
	sf::Vector2f Center = m_pSprite->getGlobalBounds().getCenter();
	m_pSprite->setOrigin(Center);

}

bool Pipe::CheckPlaceCondition(Tile* pTile)
{
	return true;
}

void Pipe::UpdateObject()
{
	if (m_hasProp && m_pOut != nullptr)
	{
		if (m_elapsedTimeTogive >= m_transferSpeed)
		{
			if (m_pOut->CheckIfCanReceive(m_pProp) && m_pProp != nullptr)
			{
				m_pOut->ReceiveProp(m_pProp);
				m_count -= 1;
				m_elapsedTimeTogive = 0.0f;
				if (m_count == 0)
				{
					m_hasProp = false;
					m_pProp = nullptr;
				}
			}
		}
	}

	m_elapsedTimeTogive += GameManager::Get()->GetDeltaTime();
}




void Pipe::PlaceObject()
{
	SetSpriteTexture(m_pPipeEmpty);

	m_onGround = true;
	m_pTileOfMachine->AddPipe(this);

	sf::Vector2i tilepos = GetTilePosition();
	Chunk* pChunk = m_pTileOfMachine->GetChunk();
	Map* pMap = pChunk->GetMap();
	Tile* pNextInTile = nullptr;
	std::list<Pipe*> pipesList = {};
	Chunk* pNextChunk = nullptr;

	switch (m_inSide)
	{
	case Pipe::LEFT:
		if (tilepos.x == 0)
		{
			if (pChunk->GetPosInList().x == 0)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x - 1][ pChunk->GetPosInList().y];
			pNextInTile = pNextChunk->GetTile(pNextChunk->GetTileCount() - 1, tilepos.y);
		}
		else
		{
			pNextInTile = pChunk->GetTile(tilepos.x - 1, tilepos.y);
		}
		
		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() ==  0)
			break;
		
		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetOutPos() == Pipe::RIGHT)
			{
				ConnectInPipe(pPipe);
				pPipe->ConnectOutPipe(this);
				break;
			}
		}

		break;


	case Pipe::RIGHT:
		if (tilepos.x == pChunk->GetTileCount() - 1)
		{
			if (pChunk->GetPosInList().x == pMap->m_chunks.size() - 1)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x + 1][pChunk->GetPosInList().y];
			pNextInTile = pNextChunk->GetTile(0, tilepos.y);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x + 1, tilepos.y);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetOutPos() == Pipe::LEFT)
			{
				ConnectInPipe(pPipe);
				pPipe->ConnectOutPipe(this);
				break;
			}
		}

		break;


	case Pipe::UP:
		if (tilepos.y == 0)
		{
			if (pChunk->GetPosInList().y == 0)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x ][pChunk->GetPosInList().y - 1];
			pNextInTile = pNextChunk->GetTile(tilepos.x, pChunk->GetTileCount() - 1);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x, tilepos.y -1);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetOutPos() == Pipe::DOWN)
			{
				ConnectInPipe(pPipe);
				pPipe->ConnectOutPipe(this);
				break;
			}
		}

		break;


	case Pipe::DOWN:
		if (tilepos.y == pChunk->GetTileCount())
		{
			if (pChunk->GetPosInList().y == pMap->m_chunks[0].size() - 1)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y + 1];
			pNextInTile = pNextChunk->GetTile(tilepos.x, 0);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x, tilepos.y +1);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetOutPos() == Pipe::UP)
			{
				ConnectInPipe(pPipe);
				pPipe->ConnectOutPipe(this);
				break;
			}
		}

		break;

	default:
		break;
	}


	switch (m_outSide)
	{
	case Pipe::LEFT:
		if (tilepos.x == 0)
		{
			if (pChunk->GetPosInList().x == 0)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x - 1][pChunk->GetPosInList().y];
			pNextInTile = pNextChunk->GetTile(pChunk->GetTileCount() - 1, tilepos.y);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x - 1, tilepos.y);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetInPos() == Pipe::RIGHT)
			{
				ConnectOutPipe(pPipe);
				pPipe->ConnectInPipe(this);
				break;
			}
		}

		break;

	case Pipe::RIGHT:
		if (tilepos.x == pChunk->GetTileCount() - 1)
		{
			if (pChunk->GetPosInList().x == pMap->m_chunks.size() - 1)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x + 1][pChunk->GetPosInList().y];
			pNextInTile = pNextChunk->GetTile(0, tilepos.y);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x + 1, tilepos.y);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetInPos() == Pipe::LEFT)
			{
				ConnectOutPipe(pPipe);
				pPipe->ConnectInPipe(this);
				break;
			}
		}

		break;


	case Pipe::UP:
		if (tilepos.y == 0)
		{
			if (pChunk->GetPosInList().y == 0)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y - 1];
			pNextInTile = pNextChunk->GetTile(tilepos.x, pChunk->GetTileCount() - 1);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x, tilepos.y - 1);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetInPos() == Pipe::DOWN)
			{
				ConnectOutPipe(pPipe);
				pPipe->ConnectInPipe(this);
				break;
			}
		}

		break;

	case Pipe::DOWN:
		if (tilepos.y == pChunk->GetTileCount())
		{
			if (pChunk->GetPosInList().y == pMap->m_chunks[0].size() - 1)
				break;
			pNextChunk = pMap->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y + 1];
			pNextInTile = pNextChunk->GetTile(tilepos.x, 0);
		}
		else
			pNextInTile = pChunk->GetTile(tilepos.x, tilepos.y + 1);

		pipesList = pNextInTile->GetPipesOnTile();
		if (pipesList.size() == 0)
			break;

		for (Pipe* pPipe : pipesList)
		{
			if (pPipe->GetInPos() == Pipe::UP)
			{
				ConnectOutPipe(pPipe);
				pPipe->ConnectInPipe(this);
				break;
			}
		}

		break;

	default:
		break;
	}

}

void Pipe::RotateObjectClockWise()
{
	m_pSprite->rotate(sf::degrees(90.f));
	m_inSide = (Pipe::IN_OUT_SIDE)((1 + m_inSide) % 4);
	m_outSide = (Pipe::IN_OUT_SIDE)((1 + m_outSide) % 4);

	for (int i = 0; i < m_listcolliders.size(); i++) {
		m_listcolliders[i]->RotateCW(90);
	}

}

void Pipe::ReceiveProp(Prop* pProp)
{

	if (m_pProp == nullptr)
	{
		m_hasProp = true;
		m_pProp = pProp;
		m_count += 1;
		m_elapsedTimeTogive = 0.0f;
		return;
	}

	if (m_pProp->GetID() == pProp->GetID())
	{
		m_count += 1;
	}

}

Pipe::IN_OUT_SIDE Pipe::GetOutPos()
{
	return m_outSide;
}

Pipe::IN_OUT_SIDE Pipe::GetInPos()
{
	return m_inSide;
}

void Pipe::ConnectInPipe(Pipe* pPipe)
{
	m_pIn = pPipe;
}

void Pipe::ConnectOutPipe(Pipe* pPipe)
{
	m_pOut = pPipe;
}

Pipe* Pipe::GetpIn()
{
	return m_pIn;
}

Pipe* Pipe::GetpOut()
{
	if (m_pOut != nullptr) {
		return m_pOut;
	}
	return this;
}

Prop* Pipe::GiveProp()
{
	m_count -= 1;

	if (m_count > 0)
		return m_pProp;

	Prop* pProp = m_pProp;
	m_hasProp = false;
	m_pProp = nullptr;
	
	SetSpriteTexture(m_pPipeEmpty);
	return pProp;
}

Prop* Pipe::GetPropInPipe()
{
	return m_pProp;
}

bool Pipe::CheckIfCanReceive(Prop* pProp)
{
	if (pProp == nullptr)
		return true;

	if (m_pProp == nullptr)
		return true;

	if (m_pProp->GetID() == pProp->GetID() && m_count < m_maxItem)
		return true;
	return false;
}
