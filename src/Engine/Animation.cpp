#include "pch.h"
#include "Animation.h"
#include "AssetManager.h"
#include "AnimationManager.h"
#include "GameManager.h"

Animation::Animation(const char* name, const char* spritesheetName): m_animationName(name), m_spritesheetName(spritesheetName), m_isLooping(true), m_displaySpeed(0.05f)
{}

void Animation::PlayAnimation(sf::Sprite* sprite)
{
	sf::IntRect newSpriteRect = sf::IntRect(sf::Vector2i(m_animationsFrames[0]->m_startX, m_animationsFrames[0]->m_startY), sf::Vector2i(m_animationsFrames[0]->m_width, m_animationsFrames[0]->m_height));
	sprite->setTextureRect(newSpriteRect);
}

bool Animation::Update(int* currentFrame, float* currentFrameTime, sf::Sprite* sprite)
{
	*currentFrameTime += GameManager::Get()->GetDeltaTime();


	if (*currentFrameTime >= m_displaySpeed) {
		*currentFrameTime -= m_displaySpeed; 
		*currentFrame += 1; 
		if (*currentFrame == m_animationsFrames.size())
		{
			if (m_isLooping == false)
				return false;

			*currentFrame = 0;
		}
		sf::IntRect newSpriteRect = sf::IntRect(sf::Vector2i(m_animationsFrames[*currentFrame]->m_startX, m_animationsFrames[*currentFrame]->m_startY), sf::Vector2i(m_animationsFrames[*currentFrame]->m_width, m_animationsFrames[*currentFrame]->m_height));
		sprite->setTextureRect(newSpriteRect);
	}
	return true; 
}

sf::Sprite* Animation::GetSprite()
{
	sf::Sprite* pSprite = new sf::Sprite(m_pSprite->getTexture());
	pSprite->setTextureRect(m_pSprite->getTextureRect());
	pSprite->setOrigin(m_pSprite->getOrigin());
	return pSprite;
}


