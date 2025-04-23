#pragma once

#include <string>
#include <list>

class Scene;

namespace sf
{
	class Text;
}

class UIText;

class Text
{
	std::list<Text*>::iterator* m_pListIterator = nullptr;

	bool m_toDestroy = false;

protected:
	
	bool m_isUI = false;

	sf::Text* m_pText = nullptr;
	bool m_isDrawable = false;

	Scene* m_pScene = nullptr;

	sf::Vector2f m_pos = { 0.0f,0.0f };

	std::list<UIText*>::iterator* m_pListUIIterator = nullptr;

public:
	Text();
	~Text();

	void SetText(std::string str);

	void Draw();
	void Hide();

	void SetPosition(sf::Vector2f pos);
	
	void SetFont(const char* fontName);

	void SetSize(int size);

	void SetColor(sf::Color color);
	void SetOutline(sf::Color color, int thickness = 1);

	void Destroy();

	friend Scene;
};

class UIText : public Text
{
	sf::Vector2f m_posOnCanva = { 0.0f,0.0f };

public:
	UIText();
	~UIText()= default;

	void SetPosOnCanva(sf::Vector2f posOnCanva);

	friend Scene;

};