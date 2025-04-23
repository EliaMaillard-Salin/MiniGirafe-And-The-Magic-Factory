#include "pch.h"
#include "Inventory.h"
#include "Prop.h"
#include "SceneTest.h"
#include "Grimoire.h"
#include "Text.h"

sf::Vector2i Inventory::CheckIfPropInInventory(Prop* pProp)
{
	sf::Vector2i res(-1, -1);

	for (int i = 0; i < m_inventoryTilesList.size(); i++)
	{
		for (int j = 0; j < m_inventoryTilesList[0].size(); j++)
		{
			if (m_inventoryTilesList[i][j]->IsEmpty() == true)
				continue;

			if (m_inventoryTilesList[i][j]->GetProp()->GetID() == pProp->GetID())
				return sf::Vector2i(i, j);
		}
	}

	return res;
}

void Inventory::Init(SceneTest* pScene)
{

	sf::Vector2f grimoirePos = pScene->GetGrimoire()->GetPosOnCanva();
	sf::Vector2u grimoireSize = pScene->GetGrimoire()->GetSprite()->getTexture().getSize();

	m_inventoryTilesList = std::vector<std::vector<InventoryTile*>>(6);
	for (int i = 0; i <m_inventoryTilesList.size(); i++)
	{
		m_inventoryTilesList[i] = std::vector<InventoryTile*>(8);
		for (int j = 0; j < m_inventoryTilesList[i].size(); j++)
		{
			m_inventoryTilesList[i][j] = pScene->CreateEntity<InventoryTile>();
			m_inventoryTilesList[i][j]->Init();
			if (j < m_inventoryTilesList[i].size()/2)
				m_inventoryTilesList[i][j]->SetTilePosition(grimoirePos.x - (grimoireSize.x / 2.0f) + 50.0f + j * 75.0f + 10.0f ,grimoirePos.y - (grimoireSize.y * 0.5f) + i * 75.f - 10.0f);
			else
				m_inventoryTilesList[i][j]->SetTilePosition(grimoirePos.x + 50.0f + (j - m_inventoryTilesList[i].size() / 2) * 75.0f + 40.0f,grimoirePos.y - (grimoireSize.y * 0.5f) + i * 75.f - 10.0f );

		}

	}
}

bool Inventory::AddElementInInventory(Prop* pProp, int propCount)
{
	if (m_isFull)
		return false;

	sf::Vector2i isInInvent = CheckIfPropInInventory(pProp);
	if (isInInvent != sf::Vector2i(-1,-1))
	{
		m_inventoryTilesList[isInInvent.x][isInInvent.y]->AddElement(propCount);
		return true;
	}


	while (m_inventoryTilesList[m_firstEmptyRow][m_firstEmptyCol]->IsEmpty() == false) {
		
		if (m_firstEmptyRow == 4 && m_firstEmptyCol == m_inventoryTilesList[0].size()) {
			m_isFull = true;
			return false;
		}

		if (m_firstEmptyCol == m_inventoryTilesList[0].size()) 
		{
			m_firstEmptyRow += 1;
			m_firstEmptyCol = 0;
			continue;
		}

		m_firstEmptyCol += 1;
	}

	m_inventoryTilesList[m_firstEmptyRow][m_firstEmptyCol]->AddElement(pProp, propCount);

	if (m_firstEmptyRow == 4 && m_firstEmptyCol == m_inventoryTilesList[0].size())
	{
		m_isFull = true;
		return true;
	}

	if (m_firstEmptyCol == m_inventoryTilesList[0].size()) {
		m_firstEmptyCol = 0;
		m_firstEmptyRow += 1;
		return true;
	}
	m_firstEmptyCol += 1;

	return true;
}

void Inventory::RemoveElementInInventory(Prop* pProp, int propCount)
{
	sf::Vector2i isInInvent = CheckIfPropInInventory(pProp);
	if (isInInvent != sf::Vector2i(-1, -1))
	{
		RemoveElementInInventory(isInInvent.x, isInInvent.y);
		return;
	}
	return;
}

void Inventory::RemoveElementInInventory(int row, int col)
{
	m_inventoryTilesList[row][col]->RemoveElement(1);

	if (m_firstEmptyRow > row)
	{
		m_firstEmptyRow = row;
		m_firstEmptyCol = col;
	}

	if (m_firstEmptyCol > col && m_firstEmptyRow >= row)
	{
		m_firstEmptyRow = row;
		m_firstEmptyCol = col;
	}

	m_isFull = false;
}

void Inventory::Draw()
{
	for (int i = 0; i < m_inventoryTilesList.size(); i++)
	{
		for (int j = 0; j < m_inventoryTilesList[i].size();j++)
		{
			m_inventoryTilesList[i][j]->Draw();
		}
	}
}

void Inventory::Hide()
{
	for (int i = 0; i < m_inventoryTilesList.size(); i++)
	{
		for (int j = 0; j < m_inventoryTilesList[i].size(); j++)
		{
			m_inventoryTilesList[i][j]->Hide();
		}
	}
}

InventoryTile::InventoryTile()
{
	m_layer = 2;
}

InventoryTile::~InventoryTile()
{
}

void InventoryTile::Init()
{
	SetSpriteTexture("EmptyTile");
	m_pAmmount = m_pScene->CreateUIText();
	m_pAmmount->SetSize(20);
}

bool InventoryTile::IsEmpty()
{
	return m_isEmpty;
}

void InventoryTile::AddElement(Prop* pProp, int count)
{
	if (m_isEmpty == false)
	{
		m_count += count;
		return;
	}
	m_isEmpty = false;
	m_pProp = pProp;
	m_count = count;
	m_pAmmount->SetText(std::to_string(m_count));
}

void InventoryTile::AddElement(int count)
{
	m_count += count;

	float padding = 0.0f;
	if (m_count == 10)
	{
		padding = 10.0f;
		m_pAmmount->SetPosOnCanva({ m_posOnCanva.x + 50.0f - padding,m_posOnCanva.y + 40.0f });
	}
	if (m_count == 100)
	{
		padding = 20.0f;
		m_pAmmount->SetPosOnCanva({ m_posOnCanva.x + 50.0f - padding,m_posOnCanva.y + 40.0f });
	}
	m_pAmmount->SetText(std::to_string(m_count));
}

void InventoryTile::RemoveElement(int count)
{
	if (m_count < count)
	{
		return;
	}
	m_count -= count;

	if (m_count < 100)
	{
		m_pAmmount->SetPosOnCanva({ m_posOnCanva.x + 50.0f - 10.0f,m_posOnCanva.y + 40.0f });
	}
	if (m_count < 10)
	{
		m_pAmmount->SetPosOnCanva({ m_posOnCanva.x + 50.0f,m_posOnCanva.y + 40.0f });
	}

	m_pAmmount->SetText(std::to_string(m_count));
	if (m_count > 0)
		return;

	m_isEmpty = true;
	m_pProp = nullptr;
	m_pAmmount->SetText("");
	m_pProp->SetUIVisible();
	m_pProp->SetPosOnCanva(m_posOnCanva);
}

void InventoryTile::SetTilePosition(float x, float y)
{
	SetLayer(4);
	SetPosOnCanva({ x,y });
	m_pAmmount->SetPosOnCanva({ x + 50.0f,y+40.0f });
}

void InventoryTile::Draw()
{
	SetUIVisible();
	m_pAmmount->Draw();
}

void InventoryTile::Hide()
{
	SetUIInvisible();
	m_pAmmount->Hide();
}

Prop* InventoryTile::GetProp()
{
	return m_pProp;
}
