#include "pch.h"
#include "Grimoire.h"
#include "GrimoirePages.h"
#include "BookMark.h"

Grimoire::Grimoire()
{
	m_uiIsDrawable = false;
	m_layer = 0;
	SetSpriteTexture("Grimoire");
	sf::Vector2u winSize = GameManager::Get()->GetWindow()->getSize();
	m_posOnCanva = sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.5f);
}

Grimoire::~Grimoire()
{
	m_pages.clear();
}

void Grimoire::Init()
{
	m_currentFrameIndex = 0;
	m_pages = std::vector<GrimoirePages*>(4);
	m_pages[0] = CreateEntity<RockPage>();
	m_pages[0]->Init(0, this);
	m_pages[1] = CreateEntity<PlantPage>();
	m_pages[1]->Init(1, this);
	m_pages[2] = CreateEntity<TreePage>();
	m_pages[2]->Init(2, this);
	m_pages[3] = CreateEntity<InventoryPage>();
	m_pages[3]->Init(3, this);

	m_pages[0]->OpenPage();
}

void Grimoire::Opengrimoire()
{
	if (m_uiIsDrawable == true)
		return;

	for (int i = 0; i < m_pages.size(); i++)
	{
		m_pages[i]->OpenGrimoire();
	}
	Bookmarksupdate();
	m_uiIsDrawable = true;
}

void Grimoire::CloseGrimoire()
{
	if (m_uiIsDrawable == false)
		return;
	for (int i = 0; i < m_pages.size(); i++)
	{
		m_pages[i]->CloseGrimoire();
	}
	m_uiIsDrawable = false;
}

void Grimoire::Nextpage()
{
	if (m_currentOpenPage == m_pages.size() - 1)
		return;

	m_pages[m_currentOpenPage]->ClosePage();
	m_currentOpenPage += 1;
	m_pages[m_currentOpenPage]->OpenPage();

	for (int i = 0; i < m_currentOpenPage-1; i++) {
		m_pages[i]->m_pBookmark ;
	}
	Bookmarksupdate();
}

void Grimoire::PreviousPage()
{
	if (m_currentOpenPage == 0)
		return;
	m_pages[m_currentOpenPage]->ClosePage();
	m_currentOpenPage -= 1;
	m_pages[m_currentOpenPage]->OpenPage();
	Bookmarksupdate();
}

void Grimoire::SkipToPage(int id)
{
	if (id >= m_pages.size() || id < 0)
		return;

	m_pages[m_currentOpenPage]->ClosePage();
	m_currentOpenPage = id;
	m_pages[m_currentOpenPage]->OpenPage();
	Bookmarksupdate();
}

void Grimoire::Bookmarksupdate()
{
	for (int i = 0; i < m_pages.size(); i++) {
		if (i < m_currentOpenPage) {
			m_pages[i]->m_pBookmark->GoLeft();
			m_pages[i]->m_pBookmark->SetLayer(0);
		}
		else if (i == m_currentOpenPage) {
			m_pages[i]->m_pBookmark->GoRight();
			m_pages[i]->m_pBookmark->SetLayer(3);
		}
		else if (i > m_currentOpenPage){
			m_pages[i]->m_pBookmark->GoRight();
			m_pages[i]->m_pBookmark->SetLayer(0);
		}
	}
}
