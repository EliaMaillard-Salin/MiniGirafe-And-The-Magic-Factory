#pragma once

#include <list>
#include <vector>
#include <optional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include "UICanva.h"

class GameManager;
class Entity;
class Text;
class UIText;
class Shape;
class RectangleShape;
class CircleShape;

namespace sf {
	class RenderWindow;
	class Text;
}

class Scene
{
private:
	sf::RenderWindow* m_pWindow = nullptr;

	int m_maxLayer = 7;

	bool m_toDestroy = false;

protected:
	std::list<Entity*> m_entitiesToDestroy = {};
	std::list<Entity*> m_entitiesToAdd = {};

	sf::Text* m_pText = nullptr;

	std::vector<std::list<Entity*>> m_entitiesSortByLayer = std::vector<std::list<Entity*>>(10);
	UICanva m_uiCanva = UICanva();
	std::list<Entity*> m_allEntities = {};
	std::list<Entity*> m_collidingEntities = {};

	int m_fps = 0;

	std::list<UIText*> m_UITexts = {};
	std::list<Text*> m_texts = {};

	std::list<Text*> m_textToDelete = {};

	std::list<Shape*> m_shapes = {};
	std::list<Shape*> m_shapeToDelete = {};

	bool m_updateUI = false;

	sf::Color m_backGroundColor = sf::Color::Black;

private:
	
	void Update();
	void FixedUpdate();
	void HandleEvent(std::optional<sf::Event> pEvent);
	void Draw(sf::RenderWindow* pWindow);

	void UpdateUIElements();

	void CallTickEvent();

protected:
	Scene();
	virtual ~Scene();

	virtual void OnEvent(std::optional<sf::Event> pEvent) {};
	virtual void LoadAssets() {};
	virtual void OnInitialize() {};
	virtual void OnUpdate() {};
	virtual void OnFixedUpdate() {};

	void DeleteScene();

public:
	template<typename T>
	T* CreateEntity();

	void ChangeEntityLayer(Entity* pEntity, int newLayer);
	void ChangeUIEntityLayer(UIEntity* pEntity, int newLayer);

	float GetDeltaTime() const;
	void SetMaxLayer(int maxLayer);

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	Text* CreateText();
	UIText* CreateUIText();

	RectangleShape* CreateRectShape();
	CircleShape* CreateCircleShape();

	void DestroyShape(Shape* pShape);

	void DeleteText(Text* pText);

	void SetBackGroundColor(sf::Color color);

	friend GameManager;
};

#include "Scene.inl"