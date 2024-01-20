//-----------------------------------------------------------------------------
// System.cpp
// template class to manage using systems to update and render components
// 
//-----------------------------------------------------------------------------

#ifndef NEXT2024_SRC_ENGINE_ECS_SYSTEM_H_
#define NEXT2024_SRC_ENGINE_ECS_SYSTEM_H_

#include "stdafx.h"

#include <utility>
#include <unordered_map>

#include "Entities.h"

/*COMP must be a stuct
* SYS must be a struct in the following form
* struct NAME {
*	void Update(ComponentStruct* comp, float deltaTime);
*	void Render(ComponentStruct* comp);
*	...
* }
*/
template<typename COMP, typename SYS>
class SystemManager {
public:
	SystemManager() : m_system(nullptr)
	{
	}

	SystemManager(SYS* system) : m_system(system)
	{
	}

	void UpdateAll(std::unordered_map<entity, COMP*>* components, float deltaTime) {
		for (std::pair<entity, COMP*> i : *components) {
			m_system->Update(i.second, deltaTime);
		}
	}

	void RenderAll(std::unordered_map<entity, COMP*>* components) {
		for (std::pair<entity, COMP*> i : *components) {
			m_system->Render(i.second);
		}
	}
private:
	SYS* m_system;
};

#endif // NEXT2024_SRC_ENGINE_ECS_SYSTEM_H_
