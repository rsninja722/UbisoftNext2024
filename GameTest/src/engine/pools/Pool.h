//-----------------------------------------------------------------------------
// Pool.h
// Class to manage the memory usage for a pool of entities
//-----------------------------------------------------------------------------

#ifndef NEXT2024_SRC_ENGINE_POOL_POOL_H
#define NEXT2024_SRC_ENGINE_POOL_POOL_H

#include "engine/Log.h"

template <typename T, unsigned int SIZE>
class BasePool {
public:
	BasePool()
	{
		Init();
	}

	~BasePool()
	{
		for (unsigned int i = 0; i < SIZE; ++i) {
			if (m_used[i]) {
				((T*)m_data)[i].~T();
			}
		}
	}

	void Init() {
		for (unsigned int i = 0; i < SIZE; ++i) {
			m_used[i] = false;
		}
	}

	void* allocate() {
		for (unsigned int i = 0; i < SIZE; ++i) {
			if (!m_used[i]) {
				m_used[i] = true;
				return &m_data[i * sizeof(T)];
			}
		}
		return nullptr;
	}

	void deallocate(void* ptr) {
		for (unsigned int i = 0; i < SIZE; ++i) {
			if (&m_data[i * sizeof(T)] == ptr) {
				m_used[i] = false;
				((T*)m_data)[i].~T();
				return;
			}
		}
	}

private:
	uint8_t m_data[SIZE * sizeof(T)];
	bool m_used[SIZE];
};

#endif // NEXT2024_SRC_ENGINE_POOL_POOL_H
