#pragma once
#include <unordered_map>
#include <string_view>
#include <SFML/Graphics/Texture.hpp>

class ResourceManager
{
private:
	std::unordered_map<
		std::string_view,
		sf::Texture> m_textures;
public:
	sf::Texture& loadTexture(std::string_view id);
};