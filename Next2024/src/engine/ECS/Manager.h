//-----------------------------------------------------------------------------
// Manager.cpp
// template class to orginize a component and system manager into one class
//-----------------------------------------------------------------------------
#ifndef NEXT2024_SRC_ENGINE_ECS_MANAGER_H_
#define NEXT2024_SRC_ENGINE_ECS_MANAGER_H_

#include "stdafx.h"

#include <unordered_map>
#include "engine/ECS/Component.h"
#include "engine/ECS/System.h"

/*COMP must be a stuct
* SYS must be a struct in the following form
* struct NAME {
*	void Update(ComponentStruct* comp, float deltaTime);
*	void Render(ComponentStruct* comp);
*	...
* }
* MAX_COMPONENTS specifies how many components can be created before the program exits
*/
template <typename COMPONENT, typename SYSTEM, unsigned int MAX_COMPONENTS>
class Manager
{
public:
	Manager()
	{
	}

	Manager(SYSTEM* sys)
	{
		m_compManager = ComponentManager<COMPONENT, MAX_COMPONENTS>();
		m_sysManager = SystemManager<COMPONENT, SYSTEM>(sys);
	}

	COMPONENT* AddComponent(entity entityID, COMPONENT& component) {
		return m_compManager.AddComponent(entityID, component);
	}

	COMPONENT* GetComponent(entity entityID) {
		return m_compManager.GetComponent(entityID);
	}

	std::unordered_map<entity, COMPONENT*>* GetAllComponents()
	{
		return &m_compManager.m_registry;
	}

	void RemoveComponent(entity entityID) {
		m_compManager.RemoveComponent(entityID);
	}

	void UpdateAll(float deltaTime) {
		m_sysManager.UpdateAll(&m_compManager.m_registry, deltaTime);
	}

	void RenderAll() {
		m_sysManager.RenderAll(&m_compManager.m_registry);
	}
private:
	ComponentManager<COMPONENT, MAX_COMPONENTS> m_compManager;
	SystemManager<COMPONENT, SYSTEM> m_sysManager;
};

#endif // NEXT2024_SRC_ENGINE_ECS_MANAGER_H_