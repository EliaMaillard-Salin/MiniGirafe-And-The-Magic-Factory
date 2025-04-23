#include "pch.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "AssetManager.h"

AnimationManager* AnimationManager::Get()
{
	static AnimationManager mInstance;

	return &mInstance;
}

Animation* AnimationManager::CreateAnimation(const char* animationName, const char* spritesheetName, int firstframe, int frameNumber)
{

	AnimationManager* pInstance = AnimationManager::Get();

	if (pInstance->m_animationList.find(animationName) != pInstance->m_animationList.end())
	{
		std::cout << "Animation already exists" << std::endl;
		return nullptr;
	}
	SpriteSheet* spritesheet = AssetManager::Get()->GetSpriteSheet(spritesheetName);
	if (spritesheet == nullptr) {
		std::cout << "SpriteSheet Unknow" << std::endl;
		return nullptr;
	}
	Animation* newAnimation = new Animation(animationName,spritesheetName);
	newAnimation->m_pSprite = spritesheet->m_spritesheetSprite;

	for (int i = firstframe; i < firstframe + frameNumber; i++)
	{
		newAnimation->m_animationsFrames.push_back(spritesheet->m_frames[i]);
	}

	pInstance->m_animationList.insert(std::pair<const char*, Animation*>(animationName, newAnimation) );
	return newAnimation;
}

bool AnimationManager::PlayAnimation(const char* animationName, sf::Sprite* pSprite)
{
	AnimationManager* pInstance = AnimationManager::Get();

	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
	{
		std::cout << "Animation not created" << std::endl;
		return false;
	}

	pInstance->m_animationList[animationName]->PlayAnimation(pSprite);
	return true;
}

Animation* AnimationManager::GetAnimation(const char* animationName)
{
	AnimationManager* pInstance = AnimationManager::Get();
	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
	{
		std::cout << "Animation Not Found";
		return nullptr;
	}
	return pInstance->m_animationList[animationName];
}

//bool AnimationManager::StopAnimation(const char* animationName)
//{
//	AnimationManager* pInstance = AnimationManager::Get();
//
//	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
//	{
//		std::cout << "Animation not created" << std::endl;
//		return false;
//	}
//
//	pInstance->m_animationList[animationName]->StopAnimation();
//	return true;
//}
