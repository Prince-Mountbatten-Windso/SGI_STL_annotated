#pragma once

#include"stl_construct.h"
#include"stl_iterator.h"

template<class T>
struct __list_node
{
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
	T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef __list_iterator<T, T&, T*>             iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef __list_iterator<T, Ref, Ptr>           self;

	typedef T   value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef bss::bidirectional_iterator_tag iterator_category;

	//�����ڵ�
	link_type node;

public:
	__list_iterator() : node(0)
	{}
	__list_iterator(link_type x) : node(x)
	{}
public:
	self& operator++()
	{
		node = (link_type)node->next;
		return *this;
	}
	self  operator++(int)
	{
		self tmp = *this;
		++*this;
		return tmp;
	}
	self& operator--()
	{
		node = (link_type)(node->prev);
		return *this;
	}
	self  operator--(int)
	{
		self tmp = *this;
		--*this;
		return tmp;
	}
	reference operator*()
	{
		return node->data;
	}
	pointer operator->()
	{
		return &(operator*());
	}
	bool operator==(const self &x)
	{
		return node == x.node;
	}
	bool operator!=(const self &x)
	{
		return node != x.node;
	}
};

//////////////////////////////////////////////////////////////

template <class T, class Ref, class Ptr>
bss::bidirectional_iterator_tag iterator_category(const __list_iterator<T, Ref, Ptr>&) 
{
	return bss::bidirectional_iterator_tag();
}


template<class T, class Alloc=alloc>
class list
{
protected:
	typedef __list_node<T> list_node;
	typedef size_t   size_type;
	typedef T&       reference;
public:
	typedef list_node* link_type;
	typedef typename __list_iterator<T, T&, T*>::iterator iterator;
public:
	list()
	{
		empty_initialize();
	}
	list(size_type n) 
	{
		fill_initialize(n, T());
	}
	list(size_type n, const T &x)
	{
		fill_initialize(n, x);
	}
	~list()
	{
		clear();
		put_node(node);
	}
public:
	iterator begin()
	{
		//return node->next;
		return (link_type)((*node).next);
	}
	iterator end()
	{
		return (link_type)(node);
	}
	bool empty() const
	{
		return node->next == node;
	}
	size_type size()
	{
		size_type result = 0;
		bss::distance(begin(), end(), result);
		return result;
	}
	reference front()
	{
		return *begin();   //operator *
	}
	reference back()
	{
		return *(--end());
	}

public:
	void push_front(const T& x)
	{
		insert(begin(), x);
	}
	void push_back(const T& x)
	{
		insert(end(), x);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}
	void swap(list<T, Alloc>& x)
	{
		std::swap(node, x.node);
	}
	void clear()
	{
		link_type cur = (link_type)node->next;
		while (cur != node)
		{
			link_type tmp = cur;
			cur = (link_type)cur->next;
			destroy_node(tmp);
		}
		node->next = node;
		node->prev = node;
	}
public:
	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
	void insert(iterator position, int n, const T& x)
	{
		for (; n > 0; --n)
			insert(position, x);
	}
	iterator erase(iterator position)
	{
		link_type next_node = link_type(position.node->next);
		link_type prev_node = link_type(position.node->prev);
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}
protected:
	link_type get_node() 
	{ 
		return list_node_allocator::allocate(); 
	}
	link_type create_node(const T& x) 
	{
		link_type p = get_node();
		construct(&p->data, x);
		return p;
	}
	void put_node(link_type p) 
	{
		list_node_allocator::deallocate(p); 
	}
	void destroy_node(link_type p) 
	{
		destroy(&p->data);
		put_node(p);
	}

	void empty_initialize() 
	{
		node = get_node();
		node->next = node;
		node->prev = node;
	}
	void fill_initialize(size_type n, const T& value) 
	{
		empty_initialize(); //����ͷ�ڵ�
		insert(begin(), n, value);
	}
protected:
	link_type node;  //head
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
};