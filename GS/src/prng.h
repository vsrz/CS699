#ifndef PRNG_H
#define PRNG_H

#include <random>

static std::random_device gen;

int getRand(int lo, int hi)
{
	std::uniform_int_distribution<int> dist(lo, hi);
	return dist(gen);
}

#endif