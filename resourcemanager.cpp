#include "resourcemanager.hpp"

sf::Texture& ResourceManager::loadTexture(std::string_view id)
{
	if (m_textures.find(id) != m_textures.end())
		return m_textures.at(id);

	m_textures.emplace(id, sf::Texture{});
	if (!m_textures.at(id).loadFromFile(id.data()))
		throw std::exception("Unable to load Texture");

	return m_textures.at(id);
}
