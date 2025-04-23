#include "pch.h"
#include "GrimoirePages.h"
#include "Grimoire.h"

#include "SceneTest.h"
#include "BookMark.h"
#include "Inventory.h"


GrimoirePages::~GrimoirePages()
{
	m_pBookmark = nullptr;
}

void GrimoirePages::OpenGrimoire()
{
	m_pBookmark->SetUIVisible();
	m_grimoireIsOpen = true;
	if (m_pageOpen)
		OpenPage();
}


RockPage::~RockPage()
{
	m_rockList.clear();
}

void RockPage::Init(int id, Grimoire* pGrimoire)
{
	m_idInGrimoireList = id;

	sf::Vector2f grimoirePos = pGrimoire->GetPosOnCanva();
	sf::Vector2u grimoireSize = pGrimoire->GetSprite()->getTexture().getSize();

	m_pBookmark = CreateEntity<BookMark>();
	m_pBookmark->Init("BookMark", id, pGrimoire, grimoirePos.x - (grimoireSize.x / 2.0f) + 70, grimoirePos.x + (grimoireSize.x / 2.0f) - 70, grimoirePos.y - grimoireSize.y * 0.5f - 20);
	
	m_pBookmark->GoRight();
	m_pBookmark->SetLayer(0);
	
	m_posOnCanva = grimoirePos;

	m_rockList[0] = CreateEntity<UIEntity>();
	m_rockList[0]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[1] = CreateEntity<UIEntity>();
	m_rockList[1]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[2] = CreateEntity<UIEntity>();
	m_rockList[2]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[3] = CreateEntity<UIEntity>();
	m_rockList[3]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[4] = CreateEntity<UIEntity>();
	m_rockList[4]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[5] = CreateEntity<UIEntity>();
	m_rockList[5]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[6] = CreateEntity<UIEntity>();
	m_rockList[6]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[7] = CreateEntity<UIEntity>();
	m_rockList[7]->SetSpriteTexture("Materials/Rocks/RockType");

	m_rockList[8] = CreateEntity<UIEntity>();
	m_rockList[8]->SetSpriteTexture("Materials/Rocks/RockType");

	for (int i = 0; i < 9; i++)
	{
		if (i <5)
			m_rockList[i]->SetPosOnCanva({ grimoirePos.x - (grimoireSize.x / 2.0f) + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 5.f + i*100.f });
		else
			m_rockList[i]->SetPosOnCanva({ grimoirePos.x + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 25.f + (i-5) * 100.f });
		m_rockList[i]->SetLayer(3);
	}


	SetSpriteTexture("Page"); // PageBackGround
	SetLayer(1);
}

void RockPage::OpenPage()
{
	m_pageOpen = true;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_rockList[i]->SetUIVisible();
	}
	SetUIVisible();
}

void RockPage::ClosePage()
{
	m_pageOpen = false;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_rockList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

void RockPage::CloseGrimoire()
{
	m_pBookmark->SetUIInvisible();

	m_grimoireIsOpen = false;

	for (int i = 0; i < 9; i++) {
		m_rockList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

PlantPage::~PlantPage()
{
	m_plantList.clear();
}

void PlantPage::Init(int id, Grimoire* pGrimoire)
{
	m_idInGrimoireList = id;

	sf::Vector2f grimoirePos = pGrimoire->GetPosOnCanva();
	sf::Vector2u grimoireSize = pGrimoire->GetSprite()->getTexture().getSize();

	m_pBookmark = CreateEntity<BookMark>();
	m_pBookmark->Init("BookMark",id,pGrimoire, grimoirePos.x - (grimoireSize.x / 2.0f) + 70 + 64 + (64 * 0.5f),grimoirePos.x + (grimoireSize.x / 2.0f) - 70 - 64 - (64 * 0.5f), grimoirePos.y - grimoireSize.y * 0.5f - 20);

	m_pBookmark->GoRight();
	m_pBookmark->SetLayer(0);

	m_posOnCanva = grimoirePos;

	m_plantList[0] = CreateEntity<UIEntity>();
	m_plantList[0]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[1] = CreateEntity<UIEntity>();
	m_plantList[1]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[2] = CreateEntity<UIEntity>();
	m_plantList[2]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[3] = CreateEntity<UIEntity>();
	m_plantList[3]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[4] = CreateEntity<UIEntity>();
	m_plantList[4]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[5] = CreateEntity<UIEntity>();
	m_plantList[5]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[6] = CreateEntity<UIEntity>();
	m_plantList[6]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[7] = CreateEntity<UIEntity>();
	m_plantList[7]->SetSpriteTexture("Materials/Plants/PlantType");

	m_plantList[8] = CreateEntity<UIEntity>();
	m_plantList[8]->SetSpriteTexture("Materials/Plants/PlantType");

	for (int i = 0; i < 9; i++)
	{
		if (i < 5)
			m_plantList[i]->SetPosOnCanva({ grimoirePos.x - (grimoireSize.x / 2.0f) + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 5.f + i * 100.f });
		else
			m_plantList[i]->SetPosOnCanva({ grimoirePos.x + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 25.f + (i - 5) * 100.f });
		m_plantList[i]->SetLayer(3);
	}

	SetSpriteTexture("VoidPage");// PageBackGround
	SetLayer(1);
}

void PlantPage::OpenPage()
{
	m_pageOpen = true;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_plantList[i]->SetUIVisible();
	}
	SetUIVisible();
}

void PlantPage::ClosePage()
{
	m_pageOpen = false;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_plantList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

void PlantPage::CloseGrimoire()
{
	m_pBookmark->SetUIInvisible();

	m_grimoireIsOpen = false;

	for (int i = 0; i < 9; i++) {
		m_plantList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

TreePage::~TreePage()
{
	m_treeList.clear();
}

void TreePage::Init(int id, Grimoire* pGrimoire)
{
	m_idInGrimoireList = id;


	sf::Vector2f grimoirePos = pGrimoire->GetPosOnCanva();
	sf::Vector2u grimoireSize = pGrimoire->GetSprite()->getTexture().getSize();

	m_pBookmark = CreateEntity<BookMark>();
	m_pBookmark->Init("BookMark", id, pGrimoire, grimoirePos.x - (grimoireSize.x / 2.0f) + 70 + 64 * 2 + (64 * 0.5f) * 2, grimoirePos.x + (grimoireSize.x / 2.0f) - 70 - 64 * 2 - (64 * 0.5f) * 2, grimoirePos.y - grimoireSize.y * 0.5f - 20);

	m_pBookmark->GoRight();
	m_pBookmark->SetLayer(0);

	m_posOnCanva = grimoirePos;

	m_treeList[0] = CreateEntity<UIEntity>();
	m_treeList[0]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[1] = CreateEntity<UIEntity>();
	m_treeList[1]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[2] = CreateEntity<UIEntity>();
	m_treeList[2]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[3] = CreateEntity<UIEntity>();
	m_treeList[3]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[4] = CreateEntity<UIEntity>();
	m_treeList[4]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[5] = CreateEntity<UIEntity>();
	m_treeList[5]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[6] = CreateEntity<UIEntity>();
	m_treeList[6]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[7] = CreateEntity<UIEntity>();
	m_treeList[7]->SetSpriteTexture("Materials/Trees/TreeType");

	m_treeList[8] = CreateEntity<UIEntity>();
	m_treeList[8]->SetSpriteTexture("Materials/Trees/TreeType");

	for (int i = 0; i < 9; i++)
	{
		if (i < 5)
			m_treeList[i]->SetPosOnCanva({ grimoirePos.x - (grimoireSize.x / 2.0f) + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 5.f + i * 100.f });
		else
			m_treeList[i]->SetPosOnCanva({ grimoirePos.x + 100.0f,grimoirePos.y - grimoireSize.y * 0.5f + 25.f + (i - 5) * 100.f });
		m_treeList[i]->SetLayer(3);
	}

	SetSpriteTexture("PageTREE");// PageBackGround

	SetLayer(1);
}

void TreePage::OpenPage()
{
	m_pageOpen = true;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_treeList[i]->SetUIVisible();
	}
	SetUIVisible();
}

void TreePage::ClosePage()
{
	m_pageOpen = false;

	if (m_grimoireIsOpen == false)
		return;

	for (int i = 0; i < 9; i++) {
		m_treeList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

void TreePage::CloseGrimoire()
{
	m_pBookmark->SetUIInvisible();

	m_grimoireIsOpen = false;

	for (int i = 0; i < 9; i++) {
		m_treeList[i]->SetUIInvisible();
	}
	SetUIInvisible();
}

InventoryPage::~InventoryPage()
{
	m_pInventory = nullptr;
}

void InventoryPage::Init(int id, Grimoire* pGrimoire)
{
	m_idInGrimoireList = id;

	sf::Vector2f grimoirePos = pGrimoire->GetPosOnCanva();
	sf::Vector2u grimoireSize = pGrimoire->GetSprite()->getTexture().getSize();

	m_pBookmark = CreateEntity<BookMark>();
	m_pBookmark->Init("BookMark", id, pGrimoire, grimoirePos.x - (grimoireSize.x / 2.0f) + 70 + 64 * 3 + (64 * 0.5f) * 3, grimoirePos.x + (grimoireSize.x / 2.0f) - 70 - 64 * 3 - (64 * 0.5f) * 3, grimoirePos.y - grimoireSize.y * 0.5f - 20);

	m_pBookmark->GoRight();
	m_pBookmark->SetLayer(0);

	m_posOnCanva = grimoirePos;

	m_pInventory = GetScene<SceneTest>()->GetInventory();

	SetSpriteTexture("Invent");// PageBackGround
	SetLayer(1);
}

void InventoryPage::OpenPage()
{
	m_pageOpen = true;

	if (m_grimoireIsOpen == false)
		return;
	m_pInventory->Draw();

	SetUIVisible();
}

void InventoryPage::ClosePage()
{
	m_pageOpen = false;

	if (m_grimoireIsOpen == false)
		return;

	m_pInventory->Hide();

	SetUIInvisible();
}

void InventoryPage::CloseGrimoire()
{
	m_pBookmark->SetUIInvisible();

	m_grimoireIsOpen = false;

	if (m_pageOpen == false)
		return;

	m_pInventory->Hide();

	SetUIInvisible();
}
