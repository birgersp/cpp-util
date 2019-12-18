#ifndef MAP_HPP
#define MAP_HPP

#include <map>

namespace cpputil
{

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

private:

	std::map<K, V> map;

};

}

#endif /* MAP_HPP */

