#ifndef CASHREGISTER_H
#define CASHREGISTER_H

#pragma once

#include <vector>
#include "Glob.h"


class CashRegister
{
public:
	CashRegister();
	std::vector<TilePosition> getTilePositions();

private:

};

#endif
