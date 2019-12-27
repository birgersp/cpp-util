/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef MAP_HPP
#define MAP_HPP

#include "core.hpp"
#include <map>
#include <functional>

template <class K, class V>
class Map
{
public:

	void put(K key, V value)
	{
		map[key] = value;
	}

	V* get(const K& key)
	{
		auto iterator = map.find(key);
		if (iterator == map.end())
			return nullptr;
		return &iterator->second;
	}

	bool has(const K& key) const
	{
		auto iterator = map.find(key);
		return (iterator != map.end());
	}

	uint size() const
	{
		return map.size();
	}

	void foreach(std::function<void(K, V) > callback)
	{
		for (auto it = map.begin(); it != map.end(); ++it)
			callback(it->first, it->second);
	}

private:

	std::map<K, V> map;

};

#endif /* MAP_HPP */

