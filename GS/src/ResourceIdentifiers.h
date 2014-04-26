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
		RedClick,
		TestGuy,
		TestTileset,
		ManOveralls,
		AutoDoors,
		WomanTeen01,
		ManTeen01,
		WomanMidage01,
		WomanOld01,
		ManYoung01,
		Kitty,
		Hearts,
		AnimWash,
		AnimCut,
		AnimColor,
		StatusNotifiers,
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

#endif
