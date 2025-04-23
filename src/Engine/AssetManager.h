#pragma once

#include <map>
#include <string>

#include "pch.h"

class GameManager;
class Sprite;

struct Frames
{
	int m_idInSpriteSheet;
	float m_width, m_height;
	float m_startX, m_startY;
	sf::Vector2f uvsPos[4];
	std::string m_name;
};

struct SpriteSheet
{
	const char* m_fileName;
	float m_width, m_height;
	int m_rows, m_columns, m_frameNumber;

	std::vector<Frames*> m_frames;

	sf::Sprite* m_spritesheetSprite = nullptr;
};


struct Atlas
{
	int m_textureCount;
	float m_width, m_height;

	sf::Texture* m_pTexture;

	std::map<std::string, Frames*> m_assests;
};



class AssetManager
{
public:


	static AssetManager* Get();

	static Atlas* LoadAtlas(const char* filename);
	static Atlas* GetAtlas(const char* filename);
	static Frames* GetAtlasAsset(const char* atlasName, const char* assetName);

	static sf::Font* LoadFont(const char* filename);
	static sf::Font* GetFont(const char* filename);

	static sf::Texture* LoadTexture(const char* filename);
	static sf::Texture* GetTexture(const char* filename);

	static SpriteSheet* LoadSpriteSheet(const char* fileName, int frameNumber, float SpriteSheetWidth, float SpriteSheetHeight, int rows, int columns);
	static SpriteSheet* GetSpriteSheet(const char* fileName);

protected:
	enum AssetType
	{
		SFML, GCRENDER
	};
	static void CutSpriteSheet(SpriteSheet* spritesheet);

	static void SetType(AssetType type) { AssetManager::Get()->m_assetType = type; }
	static AssetType GetType() { return AssetManager::Get()->m_assetType; }

protected:
	AssetType m_assetType;
	std::map<const char*, sf::Font> m_fonts;
	
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, SpriteSheet> m_spritesheet;
	std::map<std::string, Atlas> m_atlas;

	friend GameManager;
};

