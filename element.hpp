#pragma once
#include "helper.hpp"

class Element
{
protected:
	uuid m_id;
public:
	Element() : m_id(std::move(generateUnique())) {}
public:
	uuid getUUID() const { return m_id; }
	void setUUID(uuid id) { m_id = id; }
};
