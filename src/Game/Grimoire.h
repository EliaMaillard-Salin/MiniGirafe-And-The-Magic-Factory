#pragma once
#include "UIEntity.h"

class GrimoirePages;

class Grimoire : public UIEntity
{

	std::vector<GrimoirePages*> m_pages = {};

	int m_currentOpenPage = 0;

public:
	Grimoire();
	~Grimoire();

	void Init();

	void Opengrimoire();
	void CloseGrimoire();

	void Nextpage();
	void PreviousPage();

	void SkipToPage(int id);

	void Bookmarksupdate();
};

