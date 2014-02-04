#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& p);


private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	
};

// (In-Line) Implementation of ResourceHolder class
#include "ResourceHolder.inl"

#endif
