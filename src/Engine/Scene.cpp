#include "pch.h"
#include "Scene.h"

#include "GameManager.h"
#include "AssetManager.h"
#include "UIEntity.h"

#include "Text.h"
#include "Shape.h"

Scene::Scene() : m_entitiesSortByLayer(std::vector<std::list<Entity*>>(8)), m_maxLayer(8)
{
	m_pWindow = GameManager::Get()->GetWindow();
}

void Scene::DeleteScene()
{
	m_toDestroy = true;
}

Scene::~Scene()
{
	for (auto it : m_allEntities)
		delete it;
	m_allEntities.clear();

	for (int i = 0; i < m_entitiesSortByLayer.size(); i++)
		m_entitiesSortByLayer[i].clear();

	m_collidingEntities.clear();
}

int Scene::GetWindowWidth() const
{
	return m_pWindow->getSize().x;
}

int Scene::GetWindowHeight() const
{
	return m_pWindow->getSize().y;
}

Text* Scene::CreateText()
{
	Text* newText = new Text();

	newText->m_pScene = this;
	m_texts.push_back(newText);
	newText->m_pListIterator = &--m_texts.end();

	return newText;
}

UIText* Scene::CreateUIText()
{
	UIText* newText = new UIText();

	newText->m_pScene = this;
	m_UITexts.push_back(newText);
	newText->m_pListUIIterator = &--m_UITexts.end();

	return newText;
}

RectangleShape* Scene::CreateRectShape()
{
	RectangleShape* newShape = new RectangleShape();

	newShape->m_pScene = this;
	m_shapes.push_back(newShape);
	newShape->m_pListIterator = &--m_shapes.end();

	return newShape;
}

CircleShape* Scene::CreateCircleShape()
{
	CircleShape* newShape = new CircleShape();

	newShape->m_pScene = this;
	m_shapes.push_back(newShape);
	newShape->m_pListIterator = &--m_shapes.end();

	return newShape;
}

void Scene::DestroyShape(Shape* pShape)
{
	m_shapeToDelete.push_back(pShape);
}

void Scene::DeleteText(Text* pText)
{
	m_textToDelete.push_back(pText);
}

void Scene::SetBackGroundColor(sf::Color color)
{
	sf::Color m_backGroundColor = color;
}

float Scene::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

void Scene::SetMaxLayer(int maxLayer)
{
	m_maxLayer = maxLayer;

	if (m_entitiesSortByLayer.size() != maxLayer)
		m_entitiesSortByLayer.resize(maxLayer);
}

void Scene::Update()
{

	OnUpdate();
	//Update
	for (std::list<Entity*>::iterator it = m_allEntities.begin(); it != m_allEntities.end();)
	{
		Entity* pEntity = *it;

		if (pEntity->m_isActive)
			pEntity->Update();

		if (pEntity->ToDestroy() == false)
		{
			++it;
			continue;
		}

		m_entitiesToDestroy.push_back(pEntity);
		it = m_allEntities.erase(it);

	}


	for (auto it = m_entitiesToDestroy.begin(); it != m_entitiesToDestroy.end(); ++it)
	{
		Entity* EntityToDelete = *it;
		if (EntityToDelete->m_hasCollision)
			m_collidingEntities.erase(*EntityToDelete->m_pColliderIterator);
		if (EntityToDelete->m_isDrawable)
			m_entitiesSortByLayer[EntityToDelete->GetLayer()].erase(*EntityToDelete->m_pDrawIterator);
		if (EntityToDelete->m_isUI)
			m_uiCanva.RemoveUIElement(dynamic_cast<UIEntity*>(EntityToDelete));
		delete* it;
	}

	m_entitiesToDestroy.clear();

	for (auto it = m_textToDelete.begin(); it != m_textToDelete.end(); ++it)
	{
		Text* pTextToDelete = *it;
		if (pTextToDelete->m_isUI)
			m_UITexts.erase(*pTextToDelete->m_pListUIIterator);
		else
			m_texts.erase(*pTextToDelete->m_pListIterator);
		delete* it;
	}

	m_textToDelete.clear();

	for (auto it = m_shapeToDelete.begin(); it != m_shapeToDelete.end(); ++it)
	{
		Shape* pTextToDelete = *it;
		m_shapes.erase(*pTextToDelete->m_pListIterator);
		delete* it;
	}
	m_shapeToDelete.clear();

	 for (std::list<Entity*>::iterator it = m_entitiesToAdd.begin(); it != m_entitiesToAdd.end(); ++it)
	 {
	 	Entity* pEntity = *it;
	 	m_allEntities.push_back(*it);

		if (pEntity->m_isDrawable)
		{
	 		m_entitiesSortByLayer[pEntity->GetLayer()].push_back(*it);
			pEntity->m_pDrawIterator = &--m_entitiesSortByLayer[pEntity->GetLayer()].end();
		}
	 	if (pEntity->m_hasCollision)
		{
	 		m_collidingEntities.push_back(pEntity);
			pEntity->m_pColliderIterator = &--m_collidingEntities.end();
		}
		
		if (pEntity->m_isUI)
		{
			m_uiCanva.AddUIElement(pEntity);
		}
	 }

	m_entitiesToAdd.clear();
}

void Scene::FixedUpdate()
{
	OnFixedUpdate();

	for (auto it = m_allEntities.begin(); it != m_allEntities.end(); ++it )
	{
		Entity* pEntity = *it;

		if (pEntity->m_isActive)
			pEntity->FixedUpdate();
	}

	//Collision
	for (auto it1 = m_collidingEntities.begin(); it1 != m_collidingEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != m_collidingEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			 if (entity->AllowedCollision(otherEntity) == false)
			 	continue;
			
			 if (entity->IsColliding(otherEntity) == false)
			 	continue;
			
			 entity->OnCollision(otherEntity);
			 otherEntity->OnCollision(entity);
		}
	}
}

void Scene::HandleEvent(std::optional<sf::Event> pEvent)
{
	OnEvent(pEvent);
}

void Scene::Draw(sf::RenderWindow* pWindow)
{

	if (m_updateUI)
		UpdateUIElements();

	for (std::list<Entity*> entityLayer : m_entitiesSortByLayer)
	{
		for (Entity* pEntity : entityLayer)
		{
			if (pEntity->m_isDrawable)
				pWindow->draw(*(pEntity->GetSprite()));
		}
	}

	for (Text* pText : m_texts) {
		if (pText->m_isDrawable)
			pWindow->draw(*(pText->m_pText));
	}

	for (Shape* pShape : m_shapes) {
		if (pShape->m_isDrawable)
			pWindow->draw(*(pShape->GetShape()));
	}

	m_uiCanva.Draw();

	for (UIText* pText : m_UITexts) {
		if (pText->m_isDrawable)
			pWindow->draw(*(pText->m_pText));
	}
}

void Scene::UpdateUIElements()
{
	m_uiCanva.UpdateUIPos();

	for (UIText* pText : m_UITexts) {
	
		sf::Vector2f pos = pText->m_posOnCanva;
		pos.x += m_pWindow->getView().getCenter().x - (m_pWindow->getView().getSize().x * 0.5f);
		pos.y += m_pWindow->getView().getCenter().y - (m_pWindow->getView().getSize().y * 0.5f);
		pText->SetPosition(sf::Vector2f(pos.x, pos.y));
	}
}

void Scene::CallTickEvent()
{
	for (auto it = m_allEntities.begin(); it != m_allEntities.end(); ++it)
	{
		Entity* pEntity = *it;
		if (pEntity->m_hasTickEvent)
			pEntity->OnTick();
	}
}




void Scene::ChangeEntityLayer(Entity* pEntity, int newLayer)
{
	if (newLayer >= m_maxLayer) {
		std::cout << "Max Layer is" << m_maxLayer << std::endl;
		return;
	}

	m_entitiesSortByLayer[pEntity->GetLayer()].remove(pEntity);
	m_entitiesSortByLayer[newLayer].push_back(pEntity);
	pEntity->m_pDrawIterator = &--m_entitiesSortByLayer[newLayer].end();
}

void Scene::ChangeUIEntityLayer(UIEntity* pEntity, int newLayer)
{
	m_uiCanva.ChangeEntityLayer(pEntity, newLayer);
}
