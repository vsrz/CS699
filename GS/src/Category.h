#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Divide the objects into different cateogies
namespace Category
{
	/**
	 * Use of bit operators allows us to send commands
	 * to multiple entities
	 **/
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 4,
	};
}

#endif

