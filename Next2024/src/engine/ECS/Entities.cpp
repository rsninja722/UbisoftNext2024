//-----------------------------------------------------------------------------
// Entities.cpp
// Class to manage the creation, destruction, and updating of entities
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Entities.h"

void Entities::Init()
{
	m_maxEntities = 0;
	m_nextEntity = 0;
}

entity Entities::Create()
{
	++m_nextEntity;
	m_maxEntities = m_nextEntity;
	return m_nextEntity;
}

unsigned int Entities::GetMaxEntities()
{
	return m_maxEntities;
}

entity Entities::m_maxEntities = 0;
entity Entities::m_nextEntity = 0;
