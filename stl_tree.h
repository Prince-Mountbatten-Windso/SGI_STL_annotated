#pragma once

#include"stl_alloc.h"
#include "stl_iterator.h"
#include "stl_construct.h"


using namespace std;

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base
{
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;
};
template <class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
	typedef __rb_tree_node<Value>* link_type;
	Value value_field;
};


////////////////////////////////////////////////////////////////
//平衡调整
void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{
	__rb_tree_node_base* y = x->right;
	x->right = y->left;
	if (y->left != 0)
		y->left->parent = x;
	y->parent = x->parent;

	if (x == root)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{
	__rb_tree_node_base* y = x->left;
	x->left = y->right;
	if (y->right != 0)
		y->right->parent = x;
	y->parent = x->parent;

	if (x == root)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}


void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{
	x->color = __rb_tree_red;
	while (x != root && x->parent->color == __rb_tree_red)
	{
		if (x->parent == x->parent->parent->left) //左分支
		{
			__rb_tree_node_base* y = x->parent->parent->right; //叔伯节点
			if (y && y->color == __rb_tree_red) //状况三
			{
				x->parent->color = __rb_tree_black;
				y->color = __rb_tree_black;
				x->parent->parent->color = __rb_tree_red;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right) //状况二
				{
					x = x->parent;
					__rb_tree_rotate_left(x, root);
				}
				x->parent->color = __rb_tree_black;    //状况一
				x->parent->parent->color = __rb_tree_red;
				__rb_tree_rotate_right(x->parent->parent, root);
			}
		}
		else //右分支
		{
			__rb_tree_node_base* y = x->parent->parent->left;
			if (y && y->color == __rb_tree_red)
			{
				x->parent->color = __rb_tree_black;
				y->color = __rb_tree_black;
				x->parent->parent->color = __rb_tree_red;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					__rb_tree_rotate_right(x, root);
				}
				x->parent->color = __rb_tree_black;
				x->parent->parent->color = __rb_tree_red;
				__rb_tree_rotate_left(x->parent->parent, root);
			}
		}
	}
	root->color = __rb_tree_black;
}

////////////////////////////////////////////////////////////////
struct __rb_tree_base_iterator
{
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef bss::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	base_ptr node;

	void increment()
	{
		if (node->right != 0)
		{
			node = node->right;
			while (node->left != 0)
				node = node->left;
		}
		else
		{
			base_ptr y = node->parent;
			while (node == y->right)
			{
				node = y;
				y = y->parent;
			}
			if (node->right != y)
				node = y;
		}
	}

	void decrement()
	{
		if (node->color == __rb_tree_red &&
			node->parent->parent == node)
			node = node->right;
		else if (node->left != 0)
		{
			base_ptr y = node->left;
			while (y->right != 0)
				y = y->right;
			node = y;
		}
		else
		{
			base_ptr y = node->parent;
			while (node == y->left)
			{
				node = y;
				y = y->parent;
			}
			node = y;
		}
	}
};

template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
	typedef __rb_tree_node<Value>* link_type;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __rb_tree_iterator<Value, Ref, Ptr> self;

	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x)
	{
		node = x;
	}

	reference operator*()
	{
		return ((link_type)node)->value_field;
	}
	pointer operator->()
	{
		return &((link_type)node)->value_field;
	}
	self& operator++()
	{
		increment();
		return *this;
	}
	self& operator--()
	{
		decrement();
		return *this;
	}
};

bool operator==(const __rb_tree_base_iterator& x,
	const __rb_tree_base_iterator& y)
{
	return x.node == y.node;
}

bool operator!=(const __rb_tree_base_iterator& x,
	const __rb_tree_base_iterator& y)
{
	return x.node != y.node;
}

////////////////////////////////////////////////////////////////

template <class Key, class Value, class Alloc = alloc>
class rb_tree
{
protected:
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
	typedef __rb_tree_color_type color_type;
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef rb_tree_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
public:
	typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
	typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

public:
	rb_tree() : node_count(0)
	{
		init();
	}
public:
	iterator begin()
	{
		return leftmost();
	}
	iterator end()
	{
		return header;
	}
	const_iterator begin()const
	{
		return leftmost();
	}
	const_iterator end()const
	{
		return header;
	}
public:
	iterator insert_equal(const Value& v)
	{
		link_type y = header;
		link_type x = root();
		while (x != 0)
		{
			y = x;
			//x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
			x = (v < value(x) ? left(x) : right(x));
		}
		return __insert(x, y, v);
	}

	pair<typename rb_tree<Key, Value, Alloc>::iterator, bool> insert_unique(const Value& v)
	{
		link_type y = header;
		link_type x = root();
		bool comp = true;
		while (x != 0)
		{
			y = x;
			//comp = key_compare(KeyOfValue()(v), key(x));
			comp = v < value(x);
			x = comp ? left(x) : right(x);
		}
		iterator j = iterator(y);
		if (comp)  //小于
		{
			if (j == begin())
				return pair<iterator, bool>(__insert(x, y, v), true);
			else
				--j;
		}
		//if (key_compare(key(j.node), KeyOfValue()(v)))
		if (value(j.node) < v) //大于
			return pair<iterator, bool>(__insert(x, y, v), true);

		return pair<iterator, bool>(j, false); //相等
	}
protected:
	iterator __insert(base_ptr x_, base_ptr y_, const Value& v);
private:
	void init()
	{
		header = get_node();  //malloc
		color(header) = __rb_tree_red;   //header->color = __rb_tree_red;
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}
	link_type get_node()
	{
		return rb_tree_node_allocator::allocate();
	}
	link_type create_node(const value_type& x)
	{
		link_type tmp = get_node();
		construct(&tmp->value_field, x);
		return tmp;
	}
protected:
	link_type& root() const { return (link_type&)header->parent; }
	link_type& leftmost() const { return (link_type&)header->left; }
	link_type& rightmost() const { return (link_type&)header->right; }

	static link_type& left(link_type x) { return (link_type&)(x->left); }  //x->left
	static link_type& right(link_type x) { return (link_type&)(x->right); }
	static link_type& parent(link_type x) { return (link_type&)(x->parent); }
	static reference value(link_type x) { return x->value_field; }
	//static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
	static color_type& color(link_type x) { return (color_type&)(x->color); }

	static link_type& left(base_ptr x) { return (link_type&)(x->left); }
	static link_type& right(base_ptr x) { return (link_type&)(x->right); }
	static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
	static reference value(base_ptr x) { return ((link_type)x)->value_field; }
	//static const Key& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
	static color_type& color(base_ptr x) { return (color_type&)(link_type(x)->color); }
protected:
	size_type node_count;
	link_type header;  //头指针
};


template <class Key, class Value, class Alloc>
typename rb_tree<Key, Value, Alloc>::iterator
rb_tree<Key, Value, Alloc>::__insert(base_ptr x_, base_ptr y_, const Value& v)
{
	link_type x = (link_type)x_;
	link_type y = (link_type)y_;
	link_type z;

	//if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) 
	if (y == header || x != 0 || v < value(y))
	{
		z = create_node(v);
		left(y) = z;                // also makes leftmost() = z when y == header
		if (y == header)
		{
			root() = z;
			rightmost() = z;
		}
		else if (y == leftmost())
			leftmost() = z;           // maintain leftmost() pointing to min node
	}
	else
	{
		z = create_node(v);
		right(y) = z;
		if (y == rightmost())
			rightmost() = z;          // maintain rightmost() pointing to max node
	}
	parent(z) = y;
	left(z) = 0;
	right(z) = 0;
	__rb_tree_rebalance(z, header->parent);
	++node_count;

	return iterator(z); //暂时不返回
}