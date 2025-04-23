#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"

template<typename T>
inline T* Scene::CreateEntity()
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->m_pScene = this;
	m_entitiesToAdd.push_back(newEntity);

	return newEntity;
}

