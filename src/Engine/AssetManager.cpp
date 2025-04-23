#include "pch.h"
#include "AssetManager.h"
#include "GameManager.h"


#include <fstream>
#include "json.hpp"

using json = nlohmann::json;


AssetManager* AssetManager::Get()
{
	static AssetManager mInstance;

	return &mInstance;
}

Atlas* AssetManager::LoadAtlas(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();
	
	 if (pInstance->LoadTexture(filename) == nullptr)
	 {
	 	std::cerr << "Texture Atlas Not Found" << std::endl;
	 	return nullptr;
	 }

	std::string jsonFilepath = "../../res/Texture/";
	jsonFilepath += filename;
	jsonFilepath += ".json";
	std::ifstream jsonFile(jsonFilepath);
	json atlasData = json::parse(jsonFile);

	Atlas newAtlas = Atlas();
	newAtlas.m_textureCount = atlasData["TexturesCount"];
	newAtlas.m_width = atlasData["width"];
	newAtlas.m_height = atlasData["height"];

	for (auto it = atlasData["Textures"].begin(); it != atlasData["Textures"].end(); it++)
	{
		Frames* pAsset = new Frames();
		pAsset->m_startX = it.value()["x"];
		pAsset->m_startY = it.value()["y"];
		pAsset->m_width = it.value()["w"];
		pAsset->m_height = it.value()["h"];
		pAsset->m_name = it.value()["name"];
		pAsset->uvsPos[0] = sf::Vector2f(pAsset->m_startX, pAsset->m_startY + pAsset->m_height);//Bottom-Left
		pAsset->uvsPos[1] = sf::Vector2f(pAsset->m_startX, pAsset->m_startY);//Top-Left
		pAsset->uvsPos[2] = sf::Vector2f(pAsset->m_startX + pAsset->m_width, pAsset->m_startY);//Top-Right
		pAsset->uvsPos[3] = sf::Vector2f(pAsset->m_startX + pAsset->m_width, pAsset->m_startY + pAsset->m_height);//Bottom-Right

		newAtlas.m_assests.insert(std::pair<std::string, Frames*>(pAsset->m_name, pAsset));
	}

	pInstance->m_atlas.insert(std::pair<const char*, Atlas>(filename, newAtlas));

	return &newAtlas;
}

Atlas* AssetManager::GetAtlas(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();

	if (pInstance->m_fonts.find(filename) == pInstance->m_fonts.end())
	{
		return AssetManager::LoadAtlas(filename);
	}
	return &pInstance->m_atlas[filename];
}

Frames* AssetManager::GetAtlasAsset(const char* atlasName, const char* assetName)
{
	AssetManager* pInstance = AssetManager::Get();
	Atlas* pAtlas = nullptr;
	if (pInstance->m_atlas.find(atlasName) == pInstance->m_atlas.end())
	{
		std::cout << "Atlas not Found";
		return nullptr;
	}
	pAtlas = &pInstance->m_atlas[atlasName];

	if (pAtlas->m_assests.find(assetName) == pAtlas->m_assests.end())
	{
		std::cout << "Asset not Found";
		return nullptr;
	}
	return pAtlas->m_assests[assetName];
}


sf::Font* AssetManager::LoadFont(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();

	if (pInstance->m_fonts.find(filename) != pInstance->m_fonts.end())
	{
		std::cout << "Font already loaded";
		return nullptr;
	}
	std::string filepath = "../../res/Fonts/";
	filepath += filename;

	sf::Font newFont = sf::Font();


	if (newFont.openFromFile(filepath) == false)
	{
		std::cout << "Unable To Load Font" << std::endl;
		return nullptr;
	}

	pInstance->m_fonts.insert(std::pair<const char*,sf::Font>(filename, newFont));
	return &pInstance->m_fonts[filename];
}


sf::Font* AssetManager::GetFont(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();
	if (pInstance->m_fonts.find(filename) == pInstance->m_fonts.end())
	{
		return AssetManager::LoadFont(filename);
	}
	return  &pInstance->m_fonts[filename];
}


 sf::Texture* AssetManager::LoadTexture(const char* filename)
 {
 	AssetManager* pInstance = AssetManager::Get();

 	if (pInstance->m_textures.find(filename) != pInstance->m_textures.end())
 	{
 		std::cout << "Texture already loaded" << std::endl;
 		return nullptr;
 	}
 	std::string filepath = "../../res/Textures/";
 	filepath += filename;

 	sf::Texture newTexture = sf::Texture();
 	
 	filepath += ".png";
	if (newTexture.loadFromFile(filepath) == false)
	{
		std::cout << "Unable to load Texture" << std::endl;
		return nullptr;
	}

 	pInstance->m_textures.insert(std::pair<const char*, sf::Texture>(filename, newTexture));
 	return &pInstance->m_textures[filename];
 }

 sf::Texture* AssetManager::GetTexture(const char* filename)
 {
 	AssetManager* pInstance = AssetManager::Get();

 	if (pInstance->m_textures.find(filename) == pInstance->m_textures.end())
 	{
		return AssetManager::LoadTexture(filename);
 	}
 	return &pInstance->m_textures[filename];
 }

 SpriteSheet* AssetManager::LoadSpriteSheet(const char* fileName, int frameNumber, float SpriteSheetWidth, float SpriteSheetHeight, int rows, int columns)
 {

 	AssetManager* pInstance = AssetManager::Get();

 	if (pInstance->m_spritesheet.find(fileName) != pInstance->m_spritesheet.end())
 	{
 		std::cout << "SpriteSheet already loaded";
 		return nullptr;
 	}

 	std::string filepath = "../../res/Textures/";
 	filepath += fileName;

	sf::Texture* pTexture = AssetManager::LoadTexture(fileName);
	if (pTexture == nullptr)
	{
		std::cout << "Could Not Find SpriteSheet Texture" << std::endl;
		return nullptr;
	}

	SpriteSheet newSprite = SpriteSheet();
 	newSprite.m_fileName = fileName;
 	newSprite.m_frameNumber = frameNumber;
 	newSprite.m_width = SpriteSheetWidth;
 	newSprite.m_height = SpriteSheetHeight;
 	newSprite.m_rows = rows;
 	newSprite.m_columns = columns;
 	pInstance->CutSpriteSheet(&newSprite);


 	newSprite.m_spritesheetSprite = new sf::Sprite(*pTexture);


 	pInstance->m_spritesheet.insert(std::pair<const char*, SpriteSheet>(fileName, newSprite));
 	return &newSprite;
 }

SpriteSheet* AssetManager::GetSpriteSheet(const char* fileName)
{
	AssetManager* pInstance = AssetManager::Get();
	if (pInstance->m_spritesheet.find(fileName) == pInstance->m_spritesheet.end())
	{
		std::cout << "SpriteSheet " << fileName << " is not loaded" << std::endl;
		return nullptr;
	}
	return &pInstance->m_spritesheet[fileName];
}

void AssetManager::CutSpriteSheet(SpriteSheet* spritesheet)
{
	int spritesID = 0;
	float spritesWidth = spritesheet->m_width / spritesheet->m_columns;
	float spritesHeight = spritesheet->m_height/ spritesheet->m_rows;

	float X, Y = 0;

	for (int i = 0; i < spritesheet->m_rows; i++ )
	{
		X = 0;
		for (int i = 0; i < spritesheet->m_columns; i++)
		{
			Frames* sprite = new Frames(); 
			sprite->m_width = spritesWidth;
			sprite->m_height = spritesHeight;
			sprite->m_idInSpriteSheet = spritesID++;
			sprite->m_startX = X;
			sprite->m_startY = Y;
			sprite->uvsPos[0] = sf::Vector2f(X, Y + spritesHeight);//Bottom-Left
			sprite->uvsPos[1] = sf::Vector2f(X, Y );//Top-Left
			sprite->uvsPos[2] = sf::Vector2f(X + spritesWidth, Y );//Top-Right
			sprite->uvsPos[3] = sf::Vector2f(X + spritesWidth, Y + spritesHeight);//Bottom-Right
			X += spritesWidth;
			spritesheet->m_frames.push_back(sprite);
		}
		Y += spritesHeight;
	};
}