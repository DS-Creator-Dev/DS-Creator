#pragma once

#include "DSCEngine/types/vector.hpp"
#include "DSCEngine/debug/assert.hpp"

namespace DSC
{
	/*!
	* \brief Generic hash map
	* \tparam K type of keys
	* \tparam V type of values
	* \tparam H hash function for keys
	* \tparam S hash container size (H(k) maps k to 0..S-1)
	 */
	template<typename K, typename V, int (*H)(const K&), int S> class HashMap
	{
	public:
		struct Entry { K key; V value;};
	private:
		Vector<Entry> container[S];
	public:
		/*! \brief checks if a key exists in the hash map
			\param key key to check
			\return true if key exists, false otherwise
		 */
		bool contains_key(const K& key) const;
		
		/*! \brief get left-value reference to the value held by a key
			\param key key to access
			\return value of the key
			
			\details if the key does not exist, it is created automatically
		 */
		V& operator[] (const K& key);
		
		/*! \brief get right-value reference to the value held by a key
			\param key key to access
			\return value of the key
			
			\details raises fatal error if key does not exist in the hash map
		 */
		const V& operator[] (const K& key) const;

		/*! \brief removes key from the hash map
			\param key key to remove
			
			\details if key doesn't exist, it is simply ignored
		 */
		void remove_key(const K& key);
	};	
}

template<typename K, typename V, int (*H)(const K&), int S>
bool DSC::HashMap<K,V,H,S>::contains_key(const K& key) const
{
	int h = H(key);
	nds_assert(0<=h && h<S);
	
	for(int i=0;i<container[h].size();i++)
		if(container[h][i].key==key)
			return true;
	return false;	
}
	
template<typename K, typename V, int (*H)(const K&), int S>	
V& DSC::HashMap<K,V,H,S>::operator[] (const K& key)
{
	int h = H(key);
	nds_assert(0<=h && h<S);
	
	for(int i=0;i<container[h].size();i++)
		if(container[h][i].key==key)
			return container[h][i].value;
		
	container[h].push_back({key, V()});
	return container[h][container[h].size()-1].value;
	
}

template<typename K, typename V, int (*H)(const K&), int S>
const V& DSC::HashMap<K,V,H,S>::operator[] (const K& key) const
{
	int h = H(key);
	nds_assert(0<=h && h<S);
	
	for(int i=0;i<container[h].size();i++)
		if(container[h][i].key==key)
			return container[h][i].value;
	__assert__(false, "Key not found");
}

template<typename K, typename V, int (*H)(const K&), int S>
void DSC::HashMap<K,V,H,S>::remove_key(const K& key)
{
	int h = H(key);
	nds_assert(0<=h && h<S);
	
	for(int i=0;i<container[h].size();i++)
		if(container[h][i].key==key)
		{
			container[h].remove_at(i);
			return;
		}			
}