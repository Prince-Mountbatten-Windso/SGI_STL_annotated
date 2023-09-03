#pragma once

#include"stl_tree.h"

template <class Key, class Alloc = alloc>
class set
{
public:
	typedef Key key_type;
	typedef Key value_type;
private:
	typedef rb_tree<key_type, value_type, Alloc> rep_type;
public:
	typedef typename rep_type::const_iterator iterator;
public:
	set()
	{}
public:
	iterator begin()const
	{
		return t.begin();
	}
	iterator end()const
	{
		return t.end();
	}
public:
	void insert(const value_type &x)
	{
		t.insert_unique(x);
	}
private:
	rep_type t;
};