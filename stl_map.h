#pragma once

#include"stl_alloc.h"

template <class Key, class T, class Alloc = alloc>
class map
{
public:
	typedef Key key_type;
	typedef T data_type;
	typedef pair<const Key, T> value_type;
private:
	typedef rb_tree<key_type, value_type, Alloc> rep_type;
public:
	typedef typename rep_type::iterator iterator;
public:
	map()
	{}
public:
	iterator begin()
	{
		return t.begin();
	}
	iterator end()
	{
		return t.end();
	}
public:
	pair<iterator, bool> insert(const value_type& x) 
	{
		return t.insert_unique(x);
	}
private:
	rep_type t;
};