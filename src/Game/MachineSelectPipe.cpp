#include "pch.h"
#include "MachineSelectPipe.h"
#include "Machine.h"
#include "Text.h"


void MachineSelectPipe::Init(std::vector<std::vector<Tile*>> tiles, Machine* pMachine)
{
	if (m_pTextTitle == nullptr)
	{
		m_pTextTitle = m_pScene->CreateUIText();
		m_pTextTitle->SetText("Choose The Pipe pos and direction");
		m_pTextTitle->SetColor(sf::Color::White);
		m_pTextTitle->SetOutline(sf::Color(0, 0, 0), 2);
		SetPosOnCanva(0.5f * sf::Vector2f(GameManager::Get()->GetWindowSize()));
		SetSpriteTexture("Selector");
		SetLayer(2);
		m_pTextTitle->SetPosOnCanva({ m_posOnCanva.x - (GetWidth() * 0.25f) + 85.f , m_posOnCanva.y - (GetHeight() * 0.5f) + 0.0f});

		m_pClick = m_pScene->CreateUIText();
		m_pClick->SetSize(19);
		m_pClick->SetText("Choose The Tile with Left click");
		m_pClick->SetColor(sf::Color::White);
		m_pClick->SetOutline(sf::Color(0, 0, 0), 1);
		m_pClick->SetPosOnCanva({ m_posOnCanva.x - (GetWidth() * 0.25f) - 27.0f, m_posOnCanva.y + 110.f});
		
		m_pArrow = m_pScene->CreateUIText();
		m_pArrow->SetText("Choose The direction with arrows");
		m_pArrow->SetColor(sf::Color::White);
		m_pArrow->SetOutline(sf::Color(0, 0, 0), 1);
		m_pArrow->SetSize(19);
		m_pArrow->SetPosOnCanva({ m_posOnCanva.x - (GetWidth() * 0.25f)  - 10.5f, m_posOnCanva.y +130.0f });
		
		m_pEnter = m_pScene->CreateUIText();
		m_pEnter->SetText("Confirm with Enter");
		m_pEnter->SetColor(sf::Color::White);
		m_pEnter->SetOutline(sf::Color(0, 0, 0), 1);
		m_pEnter->SetSize(19);
		m_pEnter->SetPosOnCanva({ m_posOnCanva.x - (GetWidth() * 0.25f)  - 25.0f, m_posOnCanva.y +150.0f });
	}

	m_pTextTitle->Draw();
	m_pClick->Draw();
	m_pArrow->Draw();
	m_pEnter->Draw();
	m_tilesOfMachine = std::vector< std::vector<UIEntity*>>(tiles.size());
	m_pSelectedMachine = pMachine;
	for (int i = 0; i < tiles.size(); i++)
	{
		m_tilesOfMachine[i] = std::vector<UIEntity*>(tiles[i].size());
		for (int j = 0; j < tiles[i].size();j++)
		{
			m_tilesOfMachine[i][j] = CreateEntity<UIEntity>();
			m_tilesOfMachine[i][j]->Init();
			m_tilesOfMachine[i][j]->SetSpriteTexture("TilesSelector");
			m_tilesOfMachine[i][j]->SetPosOnCanva({ m_posOnCanva.x - tiles.size() * m_tilesOfMachine[i][j]->GetWidth() * 0.5f + i * (m_tilesOfMachine[i][j]->GetWidth() * 1.5f), m_posOnCanva.y - tiles[i].size() * m_tilesOfMachine[i][j]->GetHeight() * 0.5f + j * (m_tilesOfMachine[i][j]->GetHeight() * 1.5f)});
			m_tilesOfMachine[i][j]->SetLayer(3);
			m_tilesOfMachine[i][j]->SetUIVisible();
		}
	}
	m_isActive = true;
	m_uiIsDrawable = true;
}

void MachineSelectPipe::EndSelection()
{
	m_tileIsSelected = false;
	m_selectedTile = sf::Vector2i(-1, -1);
	m_tileSide = 0;
	m_pipeID = 0;

	m_pSelectedMachine = nullptr;

	for (int i = 0; i != m_tilesOfMachine.size(); i++)
	{
		for (int j = 0; j != m_tilesOfMachine[i].size(); j++)
		{
			m_tilesOfMachine[i][j]->Destroy();
		}
		m_tilesOfMachine[i].clear();
	}

	m_selectedTilesAndSide.clear();
	m_tilesOfMachine.clear();
	m_isActive = false;
	m_uiIsDrawable = false;
	m_pTextTitle->Hide();
	m_pClick->Hide();
	m_pArrow->Hide();
	m_pEnter->Hide();
}

MachineSelectPipe::MachineSelectPipe()
{
	m_isActive = false;
	m_uiIsDrawable = false;
}

void MachineSelectPipe::OnUpdate()
{

	sf::Vector2i mousePos = GameManager::Get()->GetMousePosCenter();

	for (int i = 0; i <m_tilesOfMachine.size(); i++)
	{
		for (int j = 0; j < m_tilesOfMachine[i].size(); j++)
		{
			if (m_tilesOfMachine[i][j] == nullptr)
				continue;

			if (m_tilesOfMachine[i][j]->IsInside(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (m_tileIsSelected)
					m_tilesOfMachine[m_selectedTile.x][m_selectedTile.y]->SetSpriteTexture("TilesSelector");
				
				m_tileIsSelected = true;
				m_selectedTile = sf::Vector2i(i, j);
				m_tilesOfMachine[i][j]->SetSpriteTexture("TilesIsSelected");
			}
		}
	}

	if (m_tileIsSelected)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			m_tileSide = PlaceableObject::IN_OUT_SIDE::LEFT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			m_tileSide = PlaceableObject::IN_OUT_SIDE::RIGHT;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			m_tileSide = PlaceableObject::IN_OUT_SIDE::UP;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			m_tileSide = PlaceableObject::IN_OUT_SIDE::DOWN;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			for (SelectedTiles tile : m_selectedTilesAndSide)
			{
				if (tile.tileCoord == m_selectedTile && m_tileSide == tile.side)
					return;
			}

			m_pSelectedMachine->SetPipe(m_pipeID, m_selectedTile, m_tileSide);
			m_selectedTilesAndSide.push_back({ m_selectedTile, m_tileSide });
			m_pipeID += 1;
		}
	}
	if (m_pSelectedMachine->AllPipeSelected())
		EndSelection();
}

