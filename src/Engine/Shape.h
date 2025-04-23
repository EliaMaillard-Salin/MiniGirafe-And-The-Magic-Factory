#pragma once

#include <list>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene;
namespace sf
{
	class RectangleShape;
	class CircleShape;
	class Drawable;
}

class Shape 
{
	std::list<Shape*>::iterator* m_pListIterator = nullptr;
	bool m_toDestroy = false;
	bool m_isDrawable = false;

	Scene* m_pScene = nullptr;

public:
	Shape() = default;
	virtual ~Shape();

	void Draw();
	void Hide();

	void Destroy();

	virtual sf::Drawable* GetShape() = 0;

	friend Scene;
};

class RectangleShape : public Shape
{
	sf::RectangleShape* m_pShape = nullptr;

public:
	RectangleShape();
	~RectangleShape();

	void SetPosition(sf::Vector2f pos);

	void SetSize(float width, float height);

	void SetColor(sf::Color color);

	sf::Drawable* GetShape() override;

};


class CircleShape : public Shape
{
	sf::CircleShape* m_pShape = nullptr;

public:
	CircleShape();
	~CircleShape();

	void SetPosition(sf::Vector2f pos);

	void SetRadius(float radius);

	void SetColor(sf::Color color);

	sf::Drawable* GetShape() override;

};

