
/* Generic SFML Loaders */
template <typename Resource, typename Identifier>
void ResourceManager<Resource,Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
	}
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::loadmem(Identifier id, const void* data, std::size_t size)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromMemory(data, size))
	{
		throw std::runtime_error("ResourceManager::load - Failed to load " + id);
	}
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource,Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource,Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
	
}

/* SFML Shader Loader */
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& p)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, p))
	{
		throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
	}

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}
