#include "pch.h"
#include "DecantingMachine.h"
#include "PotionSelector.h"
#include "Pipe.h"
#include "Prop.h"
#include "SceneTest.h"


PotionRecipe* PotionRecipe::Get()
{
	static PotionRecipe mInstance;

	return &mInstance;
}

PotionRecipe::PotionRecipe()
{
	m_recipes.insert(std::pair<POTION_TYPES, std::list<PotionIngredient>>(POTION_TYPES::LUCK_I, {{20,RESSOURCES_PROPS::TREFLE}}));
	m_timeToDecant.insert(std::pair<POTION_TYPES,int>(POTION_TYPES::LUCK_I,25));
}

PotionRecipe::~PotionRecipe()
{
	m_recipes.clear();
	m_timeToDecant.clear();
}

std::list<PotionIngredient> PotionRecipe::GetRecipeOfPotion(POTION_TYPES potion)
{
    return PotionRecipe::Get()->m_recipes[potion];
}

int PotionRecipe::GetTimeToDecant(POTION_TYPES potion)
{
	return PotionRecipe::Get()->m_timeToDecant[potion];
}

void DecantingMachine::Init()
{
	SetSpriteTexture("Machine/DecantingMachine");
	Machine::Init(2, 2);

	sf::Vector2u winSize = GameManager::Get()->GetWindowSize();

	m_pUIDecantMachine = CreateEntity<UIEntity>();
	m_pUIDecantMachine->SetSpriteTexture("DecantingUI");
	m_pUIDecantMachine->SetPosOnCanva({ winSize.x * 0.5f,winSize.y * 0.5f });
	m_pUIDecantMachine->SetUIInvisible();
	m_pUIDecantMachine->SetLayer(2);

	sf::Vector2f uiPos = m_pUIDecantMachine->GetPosOnCanva();
	sf::Vector2f uiSize = { m_pUIDecantMachine->GetWidth(), m_pUIDecantMachine->GetHeight() };

	m_pPotionList = GetScene<SceneTest>()->GetPotionListSelector();
	m_pPotionList->SetPosOnCanva({ uiPos.x + (uiSize.x * 0.5f) - (m_pPotionList->GetWidth() * 0.5f),uiPos.y });
	m_pPotionList->SetLayer(3);

	m_pSlot1 = CreateEntity<UIEntity>();
	m_pSlot1->SetSpriteTexture("SlotDecanting");
	m_pSlot1->SetPosOnCanva({ uiPos.x - uiSize.x * 0.25f, uiPos.y });
	m_pSlot1->SetUIInvisible();
	m_pSlot2 = CreateEntity<UIEntity>();
	m_pSlot2->SetSpriteTexture("SlotDecanting");
	m_pSlot2->SetPosOnCanva({ uiPos.x - uiSize.x * 0.40f, uiPos.y - uiSize.y * 0.25f });
	m_pSlot2->SetUIInvisible();
	m_pSlot3 = CreateEntity<UIEntity>();
	m_pSlot3->SetSpriteTexture("SlotDecanting");
	m_pSlot3->SetPosOnCanva({ uiPos.x - uiSize.x * 0.40f, uiPos.y + uiSize.y * 0.25f });
	m_pSlot3->SetUIInvisible();
	m_pSlot1->SetLayer(3);
	m_pSlot2->SetLayer(3);
	m_pSlot3->SetLayer(3);

	m_pResultSlot = CreateEntity<UIEntity>();
	m_pResultSlot->SetSpriteTexture("SlotDecanting");
	m_pResultSlot->SetPosOnCanva({ uiPos.x, uiPos.y});
	m_pResultSlot->SetLayer(3);
	m_pResultSlot->SetUIInvisible();

}

void DecantingMachine::MachineEffect()
{
	if (m_wasCollidingLastFrame == false)
		m_pText->Hide();

	ReceiveFromInPipes();

	if (m_currentTick <= 0)
	{
		m_currentTick = m_tickToDecant;
		ConsumIngredients();
		m_potionCraftedCount += 1;
	}

	for (Pipe* pPipe : m_listOutPipes)
	{
		if (m_potionCraftedCount > 0)
		{
			if (pPipe->CheckIfCanReceive(m_pPotionCrafted))
			{
				m_potionCraftedCount -= 1;
				pPipe->ReceiveProp(m_pPotionCrafted);
			}
		}
	}

	if (m_wasCollidingLastFrame == false)
		m_pText->Hide();

	if (m_isOpen == false)
		return;

	m_wasCollidingLastFrame = false;

}

bool DecantingMachine::CheckPlaceCondition(Tile* pTile)
{
	return true;
}

void DecantingMachine::OpenCraftingMachine()
{
	m_pText->Draw();
}

void DecantingMachine::PlaceObject()
{
	Chunk* pChunk = m_pTileOfMachine->GetChunk();
	m_machineTiles = std::vector<std::vector<Tile*>>(m_heightInTiles);
	for (int i = 0; i < m_widthInTiles; i++)
	{
		m_machineTiles[i] = std::vector<Tile*>(m_widthInTiles);
		for (int j = 0; j < m_widthInTiles; j++)
		{
			if (m_pTileOfMachine->GetPosInChunk().x + j >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x + 1][pChunk->GetPosInList().y];
			}

			if (m_pTileOfMachine->GetPosInChunk().y + i >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y + 1];
			}

			m_machineTiles[i][j] = pChunk->GetTile(m_pTileOfMachine->GetPosInChunk().x + j, m_pTileOfMachine->GetPosInChunk().y + i);

		}
	}

	GetScene<SceneTest>()->OpenSelectPipeMenu(m_machineTiles, this);
}

void DecantingMachine::AddIngredient(int potionIngredient,int ammount, int slot)
{
	if (slot == -1)
	{
		for (int i = 0; i < m_ingredientsSlot.size(); i++)
		{
			if (m_ingredientsSlot[i].propID == -1 || (potionIngredient == m_ingredientsSlot[i].propID) )
			{
				slot = i;
				break;
			}
		}
		if (slot == -1)
			return;
	}

	m_ingredientsSlot[slot].propID = potionIngredient;
	m_ingredientsSlot[slot].ammount += ammount;

}

void DecantingMachine::ConfirmPotion(POTION_TYPES potion)
{
	m_potionToCraft = potion;
	m_pPotionCrafted = CreateEntity<Potion>();
	m_pPotionCrafted->Init(potion);

	m_necessaryIngredients = PotionRecipe::GetRecipeOfPotion(potion);
	m_tickToDecant = PotionRecipe::GetTimeToDecant(potion);
	m_canDecant = true;
}

void DecantingMachine::ReceiveFromInPipes()
{
	for (Pipe* pPipe: m_listInPipes)
	{
		if (pPipe->GetPropInPipe() == nullptr)
			continue;

		for ( PotionIngredient slots : m_ingredientsSlot)
		{
			if (slots.propID == NONE || pPipe->GetPropInPipe()->GetID() == slots.propID)
			{
				slots.propID = pPipe->GetPropInPipe()->GetID();
				slots.ammount += 1;
				break;
			}
		}
	}
}

DecantingMachine::DecantingMachine()
{
	m_hasCollision = true;
	SetTag(SceneTest::GAME_TAG::MACHINE);
}


bool DecantingMachine::CheckIfCanDecant()
{
	int validIngredients = 0;

	for (PotionIngredient it : m_necessaryIngredients)
	{
		for (int i = 0; i < m_ingredientsSlot.size(); i++)
		{
			if (m_ingredientsSlot[i].propID == it.propID && m_ingredientsSlot[i].ammount >= it.ammount)
			{
				validIngredients += 1;
				break;
			}

		}
	}

	return validIngredients == m_necessaryIngredients.size();
}

void DecantingMachine::ConsumIngredients()
{
	for (PotionIngredient it : m_necessaryIngredients)
	{
		for (int i = 0; i < m_ingredientsSlot.size(); i++)
		{
			if (m_ingredientsSlot[i].propID == it.propID)
			{
				m_ingredientsSlot[i].ammount -= it.ammount;
				break;
			}

		}
	}
}

void DecantingMachine::OnTick()
{
	if (CheckIfCanDecant())
	{
		m_currentTick -= 1;
	}
	else
		m_currentTick = m_tickToDecant;
}

void DecantingMachine::SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide)
{
	sf::Vector2f pos = GetPosition(0.25f,0.25f);

	if (pipeID == 0)
	{
		Pipe* pPipeIn = CreateEntity<Pipe>();
		pPipeIn->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeIn->SetPosition(pos.x + (pipeTilePos.x * 64.0f), pos.y + (pipeTilePos.y * 64.0f));
		pPipeIn->GetSprite()->setOrigin({ 0, 0 });
		pPipeIn->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeIn->PlaceObject();
		pPipeIn->SetLayer(4);
		m_listInPipes.push_back(pPipeIn);
	}
	if (pipeID == 1)
	{
		Pipe* pPipeIn = CreateEntity<Pipe>();
		pPipeIn->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeIn->SetPosition(pos.x + (pipeTilePos.x * 64.0f), pos.y + (pipeTilePos.y * 64.0f));
		pPipeIn->GetSprite()->setOrigin({ 0, 0 });
		pPipeIn->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeIn->PlaceObject();
		pPipeIn->SetLayer(4);
		m_listInPipes.push_back(pPipeIn);
	}
	if (pipeID == 2)
	{
		Pipe* pPipeIn = CreateEntity<Pipe>();
		pPipeIn->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeIn->SetPosition(pos.x + (pipeTilePos.x * 64.0f), pos.y + (pipeTilePos.y * 64.0f));
		pPipeIn->GetSprite()->setOrigin({ 0, 0 });
		pPipeIn->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeIn->PlaceObject();
		pPipeIn->SetLayer(4);
		m_listInPipes.push_back(pPipeIn);
	}
	if (pipeID == 3)
	{
		m_outPipePos = (PipePosInMachine)(pipeTilePos.x + pipeTilePos.y * 2.0f);
		Pipe* pPipeOut = CreateEntity<Pipe>();
		pPipeOut->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeOut->SetPosition(pos.x + (pipeTilePos.x * 64.0f), pos.y + (pipeTilePos.y * 64.0f));
		pPipeOut->GetSprite()->setOrigin({ 0, 0 });
		pPipeOut->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeOut->PlaceObject();
		pPipeOut->SetLayer(4);
		m_listInPipes.push_back(pPipeOut);
		m_allPipeSelected = true;
	}


}

void DecantingMachine::DrawUI()
{
	m_pText->Draw();

	m_wasCollidingLastFrame = true; 
}

void DecantingMachine::OpenMachineUI()
{
	m_pUIDecantMachine->SetUIVisible();
	m_pPotionList->Open(this);
	m_pSlot1->SetUIVisible();
	m_pSlot2->SetUIVisible();
	m_pSlot3->SetUIVisible();
	m_pResultSlot->SetUIVisible();

}
