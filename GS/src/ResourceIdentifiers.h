#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H
#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
		SalonTileset,
		TestTileset
	};

}

namespace Images
{
	enum ID
	{
		TestTileset,
		SalonTileset
	};
}

namespace Fonts
{
	enum ID
	{
		Default,
	};
}
template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::Image, Images::ID> ImageManager;

#endif
