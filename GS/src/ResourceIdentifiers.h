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
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
