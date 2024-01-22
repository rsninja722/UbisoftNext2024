//-----------------------------------------------------------------------------
// Component.cpp
// template class to store components and manage creation/deletion
//-----------------------------------------------------------------------------

#ifndef NEXT2024_SRC_ENGINE_ECS_COMPONENT_H_
#define NEXT2024_SRC_ENGINE_ECS_COMPONENT_H_

#include "stdafx.h"

#include <vector>
#include <unordered_map>
#include "engine/pools/Pool.h"
#include "Entities.h"

template<typename T, unsigned int MAX_COMPONETS>
class ComponentManager {
public:
	std::unordered_map<entity, T*> m_registry;

	ComponentManager() : m_pool(std::make_unique<BasePool<T, MAX_COMPONETS>>())
	{
	}

	T* AddComponent(entity entityID, T& component) {
		T* allocated = (T*)m_pool->allocate();
		*allocated = component;
		m_registry[entityID] = allocated;
		return allocated;
	}

	T* GetComponent(entity entityID) {
		return m_registry[entityID];
	}

	void RemoveComponent(entity entityID) {
		m_pool->deallocate(m_registry[entityID]);
		m_registry.erase(entityID);
	}
private:
	std::unique_ptr<BasePool<T, MAX_COMPONETS>> m_pool;
};

#endif // NEXT2024_SRC_ENGINE_ECS_COMPONENT_H_