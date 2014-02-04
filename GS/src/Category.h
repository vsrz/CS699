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
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
	};
}

#endif

