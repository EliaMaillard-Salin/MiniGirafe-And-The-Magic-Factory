#include "pch.h"
#include "Shape.h"
#include "Scene.h"


Shape::~Shape()
{
	m_pListIterator = nullptr;
}

void Shape::Draw()
{
	m_isDrawable = true;
}

void Shape::Hide()
{
	m_isDrawable = false;
}

void Shape::Destroy()
{
	m_pScene->DestroyShape(this);
}

RectangleShape::RectangleShape()
{
	m_pShape = new sf::RectangleShape();
}

RectangleShape::~RectangleShape()
{
	delete m_pShape;
}

void RectangleShape::SetPosition(sf::Vector2f pos)
{
	m_pShape->setPosition(pos);
}

void RectangleShape::SetSize(float width, float height)
{
	m_pShape->setSize({ width,height });
}

void RectangleShape::SetColor(sf::Color color)
{
	m_pShape->setFillColor(color);
}

sf::Drawable* RectangleShape::GetShape()
{
	return m_pShape;
}


CircleShape::CircleShape()
{
	m_pShape = new sf::CircleShape();
}

CircleShape::~CircleShape()
{
	delete m_pShape;
}

void CircleShape::SetPosition(sf::Vector2f pos)
{
	m_pShape->setPosition(pos);
}

void CircleShape::SetRadius(float radius)
{
	m_pShape->setRadius(radius);
}

void CircleShape::SetColor(sf::Color color)
{
	m_pShape->setFillColor(color);
}

sf::Drawable* CircleShape::GetShape()
{
	return m_pShape;
}
