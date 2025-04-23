#pragma once

#include <vector>
#include "UIEntity.h"

class Inventory;
class Page;
class BookMark;
class Scene;
class Grimoire;

namespace sf
{
	class Sprite;
}

class GrimoirePages
{
protected: 
	int m_idInGrimoireList = 0;

	bool m_pageOpen = false;

	bool m_grimoireIsOpen = false;

public:
	BookMark* m_pBookmark = nullptr;

	GrimoirePages() = default;
	virtual ~GrimoirePages();

	virtual void Init(int id, Grimoire* pGrimoire) = 0;

	virtual void OpenPage() = 0;
	virtual void ClosePage() = 0;
	virtual void CloseGrimoire() = 0;
	
	void OpenGrimoire();

};

class RockPage : public GrimoirePages, public UIEntity
{
	std::vector<UIEntity*> m_rockList = std::vector<UIEntity*>(9);

public: 

	RockPage() = default;
	~RockPage();

	void Init(int id, Grimoire* pGrimoire) override;

	void OpenPage() override;
	void ClosePage() override;
	void CloseGrimoire() override;
	
};

class PlantPage : public GrimoirePages, public UIEntity
{
	std::vector<UIEntity*> m_plantList = std::vector<UIEntity*>(9);

public:
	PlantPage() = default;
	~PlantPage();

	void Init(int id, Grimoire* pGrimoire) override;

	void OpenPage() override;
	void ClosePage() override;
	void CloseGrimoire() override;

};

class TreePage : public GrimoirePages, public UIEntity
{
	std::vector<UIEntity*> m_treeList = std::vector<UIEntity*>(9);

public:
	TreePage() = default;
	~TreePage();

	void Init(int id, Grimoire* pGrimoire) override;

	void OpenPage() override;
	void ClosePage() override;
	void CloseGrimoire() override;
};


class InventoryPage : public GrimoirePages, public UIEntity
{
	Inventory* m_pInventory = nullptr;

public:
	InventoryPage() = default;
	~InventoryPage();

	void Init(int id, Grimoire* pGrimoire) override;
	
	void OpenPage() override;
	void ClosePage() override;
	void CloseGrimoire() override;

};

//class CraftsPage : public GrimoirePages
//{
//
//};