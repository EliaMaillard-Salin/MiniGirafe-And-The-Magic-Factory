#pragma once

class Frames;

class Animation
{
public: 
	void PlayAnimation(sf::Sprite* sprite);
	bool Update(int* currentFrame,float* currentFrameTime, sf::Sprite* sprite);
	void SetLooping(bool loop) { m_isLooping = loop; }
	void SetSpeed(float speed) { m_displaySpeed = speed; }
	sf::Sprite* GetSprite();

protected:
	const char* m_spritesheetName;
	const char* m_animationName;
	float m_displaySpeed;
	std::vector<Frames*> m_animationsFrames;
	bool m_isLooping;

	sf::Sprite* m_pSprite = nullptr;

private: 
	Animation(const char* name, const char* spritesheetName);
	~Animation() {};

	friend class AnimationManager;
};

