#pragma once
#include "Animation.h"
#include "AssetManager.h"

class AnimationManager
{
public :

	static AnimationManager* Get();

	static Animation* CreateAnimation(const char* animationName, const char* spritesheetName, int firstframe, int frameNumber);
	static Animation* GetAnimation(const char* animationName);
	static bool PlayAnimation(const char* animationName, sf::Sprite* pSprite);
	//static bool StopAnimation(const char* animationName);

protected:

	std::map<const char*,Animation*> m_animationList;
};

