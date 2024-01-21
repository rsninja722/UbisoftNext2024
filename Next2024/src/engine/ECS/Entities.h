#ifndef NEXT2024_SRC_ENGINE_ECS_ENTITIES_H_
#define NEXT2024_SRC_ENGINE_ECS_ENTITIES_H_

using entity = std::size_t;

class Entities {
public:
	static void Init();

	static entity Create();

	static unsigned int GetMaxEntities();
private:
	static entity m_maxEntities;
	static entity m_nextEntity;
};

#endif // NEXT2024_SRC_ENGINE_ECS_ENTITIES_H_