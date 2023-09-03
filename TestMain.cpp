#include<iostream>
//#include<list>
//#include"stl_alloc.h"
//#include"stl_vector.h"
//#include"stl_list.h"
//#include"stl_deque.h"
//#include"stl_stack.h"
//#include"stl_queue.h"
//#include<vector>
//#include<list>/
//#include"stl_heap.h"
#include"stl_queue.h"
#include"stl_slist.h"
#include"stl_tree.h"
#include<functional>
#include<string>
#include"stl_set.h"
#include"stl_multiset.h"
#include"stl_map.h"
#include"stl_multimap.h"
#include"stl_hashtable.h"
#include"stl_hash_set.h"
#include"stl_hash_map.h"
using namespace std;

#include<vector>
#include<numeric>
#include<algorithm>
#include<set>
#include<string>
#include<time.h>
#include<fstream>
#include<deque>


class Shape
{
public:
	virtual void display() = 0;
};
class Rect : public Shape
{
public:
	virtual void display()
	{
		cout << "Rect ";
	}
};
class Circle : public Shape
{
public:
	virtual void display()
	{
		cout << "Circle ";
	}
};
class Square : public Shape
{
public:
	virtual void display()
	{
		cout << "Square ";
	}
};

void main()
{
	std::vector<Shape*> v;

	v.push_back(new Rect);
	v.push_back(new Circle);
	v.push_back(new Square);
	v.push_back(new Circle);
	v.push_back(new Rect);

	for(int i=0; i<v.size(); ++i)
		v[i]->display();
	cout<<endl;

	for_each(v.begin(), v.end(), mem_fun(&Shape::display));
	cout<<endl;
}


/*
void print(int x)
{
	cout << x << " ";
}

void main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for_each(v.begin(), v.end(), print);
	cout << endl;
	
	for_each(v.begin(), v.end(), ptr_fun(print)); //转换为函数对象的手法
	cout << endl;
}
/*
void main()
{
	ostream_iterator<int> outite(cout, " ");
	std::vector<int> iv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::vector<int>::iterator it = iv.begin();
	while (it != iv.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	std::vector<int>::reverse_iterator rit = iv.rbegin();
	while (rit != iv.rend())
	{
		cout<<*rit<<" ";
		++rit;  //
	}
	cout<<endl;

	copy(iv.rbegin(), iv.rend(), outite);
	cout << endl;
}

/*
void main()
{
	ostream_iterator<int> outite(cout, " ");
	std::deque<int> id = { 0, 1, 2, 3, 4, 5 };

	copy(id.begin(), id.end(), outite);
	cout << endl;

	int ar[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

	//20 30
	copy(ar + 1, ar + 3, front_inserter(id)); //30, 20, 0, 1, 2, 3, 4, 5 
	copy(id.begin(), id.end(), outite);
	cout << endl;

	//50, 60
	copy(ar + 4, ar + 6, back_inserter(id));//30, 20, 0, 1, 2, 3, 4, 5 50 60
	copy(id.begin(), id.end(), outite);
	cout << endl;

	//10 20
	auto ite = find(id.begin(), id.end(), 3);
	copy(ar, ar + 2, inserter(id, ite)); //30, 20, 0, 1, 2, 10, 20, 3, 4, 5 50 60
	copy(id.begin(), id.end(), outite);
	cout << endl;
}

/*
void main()
{
	std::vector<int> iv = {1,2,3,4,5,6,7,8,9,10};
	for(int i=0; i<iv.size(); ++i)
		cout<<iv[i]<<" ";
	cout<<endl;

	//std::vector<int>::iterator it = iv.begin();
	auto it = iv.begin();
	while (it != iv.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	for(const int &e : iv)
		cout<<e<<" ";
	cout<<endl;

	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));

	ofstream ofile("MyTest.txt", ios::out);
	copy(iv.begin(), iv.end(), ostream_iterator<int>(ofile, " "));
	ofile.close();
}

/*
template<class _Ty>
struct Obj
{
	operator()()
	{}
};

void main()
{
	plus<int> pl;
	pl(10,20);
	std::vector<int> iv = { 8, 5, 4, 6, 7, 6, 2, 1, 6, 9, 3 };
	sort(iv.begin(), iv.end(),less<int>());

}

/*
//template<class _Ty = void>
//struct plus 
//{	
//	//重载小括号
//	result_type operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
//	{	
//		return (_Left + _Right);
//	}
//};


void main()
{
	//plus<int> pl;

	//pl(10,20) ==> pl.operator()(10,20)
	cout<<   plus<int>()(10, 20)   <<endl;  //仿函数  函数对象
}

/*
void main()
{
	//std::vector<int> iv = { 5, 10, 15, 20, 25, 27, 17, 27, 37, 47, 57 };
	std::vector<int> iv = { 8, 5, 4, 6, 7, 6, 2, 1, 6, 9, 3 };

	//[first, mid)   [mid, last)
	//               first       mid          last
	//inplace_merge(iv.begin(), iv.begin() + 6, iv.end());
	nth_element(iv.begin(), iv.begin()+6, iv.end()); 

	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}

/*
void main()
{
	std::vector<int> iv = { 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9 };
	auto res = equal_range(iv.begin(), iv.end(), 6);

	auto p = res.first;
	while (p != res.second)
	{
		cout << *p << " ";
		p++;
	}
	cout << endl;

}

/*
void main()
{
	std::vector<int> iv = { 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9 };
	pair<std::vector<int>::iterator, std::vector<int>::iterator> res = 
		equal_range(iv.begin(), iv.end(), 6);

	std::vector<int>::iterator p = res.first;
	while (p != res.second)
	{
		cout<<*p<<" ";
		p++;
	}
	cout<<endl;

	iv.erase(res.first, res.second);
}

/*
void main()
{
	std::vector<int> iv = { 8, 5, 4, 6, 7, 6, 2, 1, 6, 9, 3 };

	//sort(iv.begin(), iv.end());
	stable_sort(iv.begin(), iv.end());

	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}


/*
void main()
{
	std::vector<int> iv = { 8, 5, 4, 7, 6, 2, 1, 9, 3 };

	//partial_sort(iv.begin(), iv.begin()+4, iv.end(), greater<int>()); //堆排 topK
	std::vector<int> res(4);
	partial_sort_copy(iv.begin(), iv.end(), res.begin(), res.end());

	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}

/*
void main()
{
	std::vector<int> iv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	srand(time(0));

	//伪随机
	random_shuffle(iv.begin(), iv.end());
	
	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}

/*
void main()
{
	// 1   2   3   4   5   6
	//123 132 213 231 312 321
	std::vector<int> iv = { 3,1,2};
	do
	{
		for (int i = 0; i<iv.size(); ++i)
			cout << iv[i];
		cout << endl;
	} while (prev_permutation(iv.begin(), iv.end()));
}

/*
void main()
{
	// 1   2   3   4   5   6
	//123 132 213 231 312 321
	std::vector<int> iv = {1,2,3};
	do
	{
		for(int i=0; i<iv.size(); ++i)
			cout<<iv[i];
		cout<<endl;
	}while(next_permutation(iv.begin(), iv.end()));
}

/*
void main()
{
	std::vector<int> iv = { 1, 3, 5, 7, 9, 15, 20, 25, 30 };
	//cout<<*lower_bound(iv.begin(), iv.end(), 10)<<endl;  //> =
	//cout << *upper_bound(iv.begin(), iv.end(), 9) << endl;  //>
	cout<<binary_search(iv.begin(), iv.end(), 8)<<endl;
}

/*
void main()
{
	std::vector<int> iv1 = { 0, 1, 2, 7, 3, 4,6, 6, 6,6,5,     8 };
	auto pos = unique(iv1.begin(), iv1.end());
	iv1.erase(pos, iv1.end());
}

/*
struct even
{
	bool operator()(int &x)
	{
		return x % 2 == 1;
	}
};

void main()
{
	std::vector<int> iv1 = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 7, 8 };
	auto pos = partition(iv1.begin(), iv1.end(), even()); //返回值为分界点
	iv1.erase(pos, iv1.end());
}

/*
void main()
{
	std::vector<int> iv1 = { 0, 1, 2, 3, 4,  6,5, 6, 6, 6, 7, 8 };
	std::vector<int> iv2 = { 2, 8 };

	std::vector<int> iv3(iv1.size() + iv2.size());

	merge(iv1.begin(), iv1.end(), iv2.begin(), iv2.end(), iv3.begin());
	//cout << includes(iv1.begin(), iv1.end(), iv2.begin(), iv2.end()) << endl;
}

/*
void main()
{
	string str = "Hello Sgi STL";

	transform(str.begin(), str.end(), str.begin(), toupper);
	cout << str << endl;
}

/*
void main()
{
	string str = "Hello Sgi STL";

	string res;
	res.resize(str.size()+1);

	transform(str.begin(), str.end(), res.begin(), tolower);
	cout<<res<<endl;
}

/*
void main()
{
	int ar[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);
	std::vector<int> iv1(ar, ar + n);

	std::vector<int> iv2(iv1.size());
	//replace(iv1.begin(), iv1.end(), 6, 3);
	//replace_if(iv1.begin(), iv1.end(), bind2nd(less<int>(), 6), 9);
	//replace_copy(iv1.begin(), iv1.end(), iv2.begin(), 6, 3);
	replace_copy_if(iv1.begin(), iv1.end(), iv2.begin(), bind2nd(less<int>(), 6), 3);
}

/*
void main()
{
	int ar[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);
	std::vector<int> iv1(ar, ar + n);

	std::vector<int> iv2(8);

	//remove_copy(iv1.begin(), iv1.end(), iv2.begin(), 6); //移除不删除
	remove_copy_if(iv1.begin(), iv1.end(), iv2.begin(), bind2nd(less<int>(), 6)); //移除不删除
}

/*
void main()
{
	int ar[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);
	std::vector<int> iv1(ar, ar + n);

	//auto pos = remove(iv1.begin(), iv1.end(), 6);
	//iv1.erase(pos, iv1.end());
	remove_if(iv1.begin(), iv1.end(), bind2nd(less<int>(),6));
}

/*
class even_by_two
{
public:
	int operator()()const
	{
		return _x += 2;
	}
private:
	static int _x;
};
int even_by_two::_x = 0;

void main()
{

	std::vector<int> iv1(10);

	//generate(iv1.begin(), iv1.end(), even_by_two());  //

	generate_n(iv1.begin(), 5, even_by_two());

}

/*
struct display
{
	void operator()(int &x)
	{
		cout<<x<<" ";
	}
};

void main()
{
	int ar[] = { 0, 1, 4, 5, 6, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);

	for_each(ar, ar + n, display());
}

/*
void main()
{
	int ar[] = { 0, 1, 4, 5, 6, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);

	std::vector<int> iv1(ar, ar + n);

	std::vector<int> iv2 = { 4, 5, 6 };
	//找出最后一次出现的位置
	cout << *find_end(iv1.begin(), iv1.end(), iv2.begin(), iv2.end()) << endl;
	//找出第一次出现的位置
	cout << *find_first_of(iv1.begin(), iv1.end(), iv2.begin(), iv2.end()) << endl;
}

/*
void main()
{
	int ar[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(ar) / sizeof(ar[0]);

	cout<<*find(ar, ar+n, 5)<<endl;
	cout<<*find_if(ar, ar+n, bind2nd(greater<int>(), 5))<<endl;
}

/*
struct lessto5
{
	bool operator()(int &x)
	{
		return x < 5;
	}
};

void main()
{
	std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	//cout<<count(v.begin(), v.end(), 3)<<endl;
	//cout << count_if(v.begin(), v.end(), lessto5()) << endl;
	cout << count_if(v.begin(), v.end(), bind2nd(less<int>(), 6)) << endl;
}

/*
void main()
{
	std::vector<int> v = { 5, 8, 2, 4, 3, 1, 9, 7 };
	//std::make_heap(v.begin(), v.end(), greater<int>());
	std::make_heap(v.begin(), v.end());

	v.push_back(16);
	std::push_heap(v.begin(), v.end());

	std::pop_heap(v.begin(), v.end());
	v.pop_back();

	std::sort_heap(v.begin(), v.end());
}

/*
void main()
{
	std::multiset<int> v1 = { 1, 3, 5, 7, 9 };
	std::multiset<int> v2 = { 1, 3, 4, 6, 8 };
	set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}

/*
void main()
{
	std::multiset<int> v1 = { 1, 1, 1,3, 5, 7, 9 };
	std::multiset<int> v2 = { 1, 3, 4, 6, 8 };
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}

/*
void main()
{
	std::multiset<int> v1 = { 1, 1, 3, 5, 7, 9 };
	std::multiset<int> v2 = { 1, 1,1,1, 3, 4, 6, 8 };
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}

/*
void main()
{
	std::multiset<int> s1 = { 1, 1, 3, 5, 7, 9};
	std::multiset<int> s2 = { 1, 2, 4, 6, 8, 10 };

	std::vector<int> res(s1.size() + s2.size());
	//set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), res.begin());
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), ostream_iterator<int>(cout," "));
}

/*
void main()
{
	//要求序列有序
	std::vector<int> v1 = { 1, 3, 5, 7, 9 };
	std::vector<int> v2 = { 2, 4, 6, 8, 10 };

	std::vector<int> res(v1.size() + v2.size());

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin());
}


/*
void main()
{
	std::vector<int> iv1 = { 10, 20, 30, 40, 50 };

	std::vector<int> iv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	copy_backward(iv1.begin(), iv1.end(), iv2.end());
}
/*
void main()
{
	//cout<<power(10, 5)<<endl;
	cout << pow(10, 5) << endl;
}

/*
void main()
{
	std::vector<int> iv = { 1, 2, 3, 4, 5 };
	int res[5] = { 0 };

	partial_sum(iv.begin(), iv.end(), res);
}

/*
void main()
{
	std::vector<int> iv =  { 1, 2, 3, 4, 5 };

	std::vector<int> iv1 = { 2, 2, 5 };

	cout << inner_product(iv.begin(), iv.end(), iv1.begin(), 0) << endl;
}

/*
void main()
{
	std::vector<int> iv = { 1, 2, 30, 4, 5 };
	int res[5] = {0};
	adjacent_difference(iv.begin(), iv.end(), res); 
}

/*
void main()
{
	std::vector<int> iv = {1,2,3,4,5};
	cout << accumulate(iv.begin(), iv.end(), 100)<<endl;  //[  )
	cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;  //[  )
}

/*
void main()
{
	hash_multimap<int, int> hm;

	pair<const int, int> v[] = { { 1, 100 }, { 30, 300 }, { 2, 200 }, { 4, 400 },
								 { 1, 100 }, { 30, 300 }, { 2, 200 }, { 4, 400 } };
	int n = sizeof(v) / sizeof(v[0]);

	for (int i = 0; i<n; ++i)
		hm.insert(v[i]);

	hash_multimap<int, int>::iterator it = hm.begin();
	while (it != hm.end())
	{
		cout<<(*it).first<<" : "<<(*it).second<<endl;
		++it;
	}
}


/*
struct Test
{
	char a;
	double b;
	int c;

	bool operator==(const Test &t)
	{
		return c == t.c;
	}
};

struct MyGetKey
{
	int operator()(const Test &t)const
	{
		return t.c;
	}
};

void main()
{
	hashtable<Test, int, bss::hash<int>, MyGetKey, alloc> ht(7, bss::hash<int>());
	Test t = {'A', 12.34, 100};
	ht.insert_unique(t);
}

/*
void main()
{
	hash_map<int, int> hm;

	pair<const int, int> v[] = { { 1, 100 }, { 3, 300 }, { 2, 200 }, {4,400} };
	int n = sizeof(v) / sizeof(v[0]);

	for(int i=0; i<n; ++i)
		hm.insert(v[i]);

}

/*
void main()
{
	hash_multiset<int> hs;

	int ar[] = { 10, 7, 8, 15, 5, 6, 8, 9, 7, 13, 12, 10, 11, 13, 12 };
	int n = sizeof(ar) / sizeof(ar[0]);

	for(int i=0; i<n; ++i)
		hs.insert(ar[i]);

	hash_multiset<int>::iterator it = hs.begin();
	while (it != hs.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*

void main()
{
	hashtable<char*, char*, bss::hash<char*>, alloc> ht(7, bss::hash<char*>());

	char *s1 = "Hello";
	char *s2 = "STL";
	char *s3 = "SGI";

	ht.insert_unique(s1);
	ht.insert_unique(s2);
	ht.insert_unique(s3);
}

/*
void main()
{
	hashtable<int, int, bss::hash<int>, alloc> ht(7, bss::hash<int>());
	ht.insert_equal(1);
	ht.insert_equal(8);
	ht.insert_equal(4);
	ht.insert_equal(15);
	ht.insert_equal(22);
	ht.insert_equal(3);
	ht.insert_equal(8);

	hashtable<int, int, bss::hash<int>, alloc>::iterator it = ht.begin();
	while (it != ht.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	hashtable<int, int, bss::hash<int>, alloc> ht(7, bss::hash<int>());
	ht.insert_equal(1);
	ht.insert_equal(8);
	ht.insert_equal(4);
	ht.insert_equal(15);
	ht.insert_equal(22);
	ht.insert_equal(3);
	ht.insert_equal(8);

	//ht.insert_equal(10);

}

/*
void main()
{
	multimap<int, int> mp;
	pair<int, int> v[] = { { 1, 1000 }, { 5, 500 }, { 4, 400 }, { 2, 200 },
						   { 1, 1000 }, { 5, 500 }, { 4, 400 }, { 2, 200 } };
	int n = sizeof(v) / sizeof(v[0]);

	for (int i = 0; i<n; ++i)
		mp.insert(v[i]);

	map<int, int>::iterator it = mp.begin();
	while (it != mp.end())
	{
		//cout << it->first << " : " << it->second << endl;
		cout<<(*it).first<<" : "<<(*it).second<<endl;
		++it;
	}
}

/*
void main()
{
	map<int, int> mp;
	pair<int, int> v[] = { { 1, 1000 }, { 5, 500 }, { 4 , 400 }, {2, 200} };
	int n = sizeof(v) / sizeof(v[0]);

	for(int i=0; i<n; ++i)
		mp.insert(v[i]);

	map<int, int>::iterator it = mp.begin();
	while (it != mp.end())
	{
		cout<<it->first<<" : "<<it->second<<endl;	
		++it;
	}

	//mp[1] = 10;
	mp[3] = 300;  //插入操作
	it = mp.begin();
	while (it != mp.end())
	{
		cout << it->first << " : " << it->second << endl;
		++it;
	}

	//it = mp.begin();
	//it->first = 10;
	//it->second = 100;
}

/*
void main()
{
	int ar[] = { 10, 7, 8, 15, 5, 6, 8, 9, 7, 13, 12, 10, 11, 13, 12 };
	int n = sizeof(ar) / sizeof(ar[0]);
	multiset<int> st;

	for(int i=0; i<n; ++i)
		st.insert(ar[i]);

	set<int>::iterator it = st.begin();
	while (it != st.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	//int ar[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	int ar[] = { 10, 7, 8, 15, 5, 6, 8,9,7,13,12,10,11, 13, 12 };
	int n = sizeof(ar) / sizeof(ar[0]);

	rb_tree<int, int> rb;
	for(int i=0; i<n; ++i)
		//rb.insert_equal(ar[i]);
		rb.insert_unique(ar[i]);

	rb_tree<int,int>::iterator it = rb.begin();
	while (it != rb.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
namespace bss
{
	template<class _Ty1, class _Ty2>
	struct pair
	{	
		typedef pair<_Ty1, _Ty2> _Myt;
		typedef _Ty1 first_type;
		typedef _Ty2 second_type;

		pair()	: first(), second()
		{}
		pair(const _Ty1& _Val1, const _Ty2& _Val2) : first(_Val1), second(_Val2)
		{}
		_Myt& operator=(const _Myt& _Right)
		{	
			first = _Right.first;
			second = _Right.second;
			return (*this);
		}
		_Ty1 first;	  
		_Ty2 second;
	};
}
//值对结构
void main()
{
	pair<int, string> v1 = {1, "元旦节"};
	pair<int, string> v2 = {2, "劳动节"};

	//    键值               实质
	cout<<v1.first<<" : "<<v1.second<<endl;

	v1 = v2;
	cout << v1.first << " : " << v1.second << endl;
}

/*
void main()
{
	slist<int> slt(5, 3);

	slist<int>::iterator it = slt.begin();
	while (it != slt.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	int ar[10] = { 0, 1, 2, 3, 4, 8, 90, 3, 5 };
	int n = 9;

	//vector<int> iv(ar, ar+n);

	priority_queue<int> pq1(ar, ar+n);
	cout<<"size = "<<pq1.size()<<endl;
	cout<<"empty = "<<pq1.empty()<<endl;
	cout<<"top = "<<pq1.top()<<endl;
	pq1.push(7);
	
	pq1.pop();
}

/*
void main()
{
	int ar[10] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	//int ar[10] = {9,5,8,3,4,0,2,3,1};
	int n = 9;

	for (int i = 0; i < n; ++i)
		cout << ar[i] << " ";
	cout << endl;

	make_heap(ar, ar+n);

	for (int i = 0; i < n; ++i)
		cout << ar[i] << " ";
	cout << endl;
}

/*
void main()
{
	int ar[10] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	//int ar[10] = {9,5,8,3,4,0,2,3,1};
	int n = 9;

	//入堆
	ar[9] = 7;   //{9,5,8,3,4,0,2,3,1, 7};
	n++;

	for (int i = 0; i < n; ++i)
		cout << ar[i]<< " ";
	cout << endl;
	push_heap(ar, ar+n);
	for (int i = 0; i < n; ++i)
		cout << ar[i] << " ";
	cout << endl;

	//pop_heap(ar, ar+n);
	//n--;

	sort_heap(ar, ar+n);

	for (int i = 0; i < n; ++i)
		cout << ar[i] << " ";
	cout << endl;
}

/*
void main()
{
	int ar[] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	int n = sizeof(ar) / sizeof(ar[0]);
	vector<int> iv(ar, ar + n);

	for (int i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	make_heap(iv.begin(), iv.end(), greater<int>()); //默认大堆
	for (int i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	sort_heap(iv.begin(), iv.end(), greater<int>());
	for (int i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}

/*
void main()
{
	int ar[] = {0,1,2,3,4,8,9,3,5};
	int n = sizeof(ar) / sizeof(ar[0]);
	vector<int> iv(ar, ar+n);

	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	make_heap(iv.begin(), iv.end(), greater<int>()); //默认大堆

	for(int i=0; i<iv.size(); ++i)
		cout<<iv[i]<<" ";
	cout<<endl;

	iv.push_back(7);
	push_heap(iv.begin(), iv.end());

	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	/*pop_heap(iv.begin(), iv.end());
	iv.pop_back();
	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	sort_heap(iv.begin(), iv.end());
	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;
}

/*
void main()
{
	deque<int,alloc, 8> de;

	de.push_front(1);
	de.push_front(2);
	de.push_front(3);
	de.push_front(4);
	de.push_front(5);
	de.push_front(6);
	de.push_front(7);
	de.push_front(8);

	de.push_back(10);
	de.push_back(20);
	de.push_back(30);

	deque<int>::iterator it = de.begin();
	while (it != de.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	list<int> mylist;

	for(int i=1; i<=10; ++i)
		mylist.push_front(i);

	cout<<"front = "<<mylist.front()<<endl;
	cout<<"back = "<<mylist.back()<<endl;

	list<int>::iterator it = mylist.begin();
	while (it != mylist.end())
	{
		cout << *it << "-->";
		++it;
	}
	cout << "Over." << endl;


	//mylist.erase(mylist.begin());
	//mylist.pop_front();
	mylist.pop_back();

	it = mylist.begin();
	while (it != mylist.end())
	{
		cout << *it << "-->";
		++it;
	}
	cout << "Over." << endl;
}

/*
void main()
{
	list<int> mylist(5, 3);
	cout<<mylist.size()<<endl;

	list<int>::iterator it = mylist.begin();
	while (it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
int main()
{
	vector<int> iv;
	iv.push_back(1);
	iv.push_back(2);

	for(int i=0; i<iv.size(); ++i)
		cout<<iv[i]<<" ";
	cout<<endl;

	iv.pop_back();
	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	iv.resize(5, 0); // 1 2 0 0 0
	for (int i = 0; i<iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	cout<<"capacity = "<<iv.capacity()<<endl;

	iv.reserve(30);

	cout << "capacity = " << iv.capacity() << endl;
	return 0;
}


/*
struct my_input_iterator_tag {};
struct my_output_iterator_tag {};
struct my_forward_iterator_tag : public my_input_iterator_tag {};
struct my_bidirectional_iterator_tag : public my_forward_iterator_tag {};
struct my_random_access_iterator_tag : public my_bidirectional_iterator_tag {};

template <class Iterator>
struct my_iterator_traits
{
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
};

//对于原生指针类型，需要进行模板特化
template <class T>
struct my_iterator_traits<T*> {
	typedef my_input_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef ptrdiff_t                  difference_type;
	typedef T*                         pointer;
	typedef T&                         reference;
};

template <class InputIterator, class Distance>
inline void __my_advance(InputIterator& i, Distance n, my_input_iterator_tag)
{
	while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
void __my_advance(BidirectionalIterator& i, Distance n, my_bidirectional_iterator_tag)
{
	if (n >= 0)
	while (n--) ++i;
	else
	while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
void __my_advance(RandomAccessIterator& i, Distance n, my_random_access_iterator_tag)
{
	i += n;
}

template <class Iterator>
typename my_iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
	typedef typename my_iterator_traits<Iterator>::iterator_category category;
	return category();
}

template <class InputIterator, class Distance>
void my_advance(InputIterator& i, Distance n)
{
	__my_advance(i, n, iterator_category(i));

	//上述语句展开后相当于以下语句
	//__my_advance(i, n, my_iterator_traits<InputIterator>::iterator_category());
}

int main()
{
	int ar[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *ptr = ar;

	my_advance(ptr, 3);
	return 0;
}

/*
namespace bss
{
	template <class InputIterator, class Distance>
	inline void advance_II(InputIterator& i, Distance n)
	{
		while (n--) ++i;
	}

	template <class BidirectionalIterator, class Distance>
	void advance_BI(BidirectionalIterator& i, Distance n)
	{
		if (n >= 0)
		while (n--) ++i;
		else
		while (n++) --i;
	}

	template <class RandomAccessIterator, class Distance>
	void advance_RAI(RandomAccessIterator& i, Distance n)
	{
		i += n;
	}

	template<class InputIterator>
	bool is_random_access_iterator(InputIterator &i)
	{
		//return true;
		return false;
	}

	template<class InputIterator>
	bool is_bidirectional_iterator(InputIterator &i)
	{
		return true;
	}

	template<class InputIterator, class Distance>
	void advance(InputIterator &i, Distance n)
	{
		if (is_random_access_iterator(i))
			advance_RAI(i, n);
		else if (is_bidirectional_iterator(i))
			advance_BI(i, n);
		else
			advance_II(i, n);
	}
}
int main()
{
	int ar[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *ptr = ar;
	bss::advance(ptr, 3);
	return 0;
}

/*
int main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	vector<int> iv{ ar, ar + n };
	list<int> mylist{ar, ar+n};

	vector<int>::iterator it1 = find(iv.begin(), iv.end(), 5);
	list<int>::iterator it2   = find(mylist.begin(), mylist.end(), 5);
	
	return 0;
}

/*
#define N 10
class CIntArray
{
public:
	CIntArray()
	{
		for(int i=0; i<N; ++i)
			ar[i] = i+1; //1 2 3 4 5 6 7 8 9 10
	}
	int GetSum(int times)
	{
		int sum = 0;
		for(int i=0; i<N; ++i)
			sum += ar[i];
		return sum * times;
	}
private:
	int ar[N];
};

class CFloatArray
{
public:
	CFloatArray()
	{
		for (int i = 0; i<N; ++i)
			ar[i] = i + 1.11; 
	}
	float GetSum(float times)
	{
		float sum = 0;
		for (int i = 0; i<N; ++i)
			sum += ar[i];
		return sum * times;
	}
private:
	float ar[N];
};

//////////////////////////////////////////////////////
//类型萃取
template<class T>
struct type_traits
{};

template<>
struct type_traits<CIntArray>
{
	typedef  int return_type;
	typedef  int arg_type;
};

template<>
struct type_traits<CFloatArray>
{
	typedef  float return_type;
	typedef  float arg_type;
};

//////////////////////////////////////////////////////
template<class T>
class CApply
{
public:
	typename type_traits<T>::return_type GetSum(T &obj, typename type_traits<T>::arg_type times)  //顾此失彼
	{
		//cout << typeid(type_traits<T>::arg_type).name()<<endl;
		//cout << typeid(type_traits<T>::return_type).name() << endl;

		return obj.GetSum(times);
	}
};

int main()
{
	CIntArray cint;
	CFloatArray cfloat;

	//cout<<cint.GetSum(2)<<endl;
	//cout<<cfloat.GetSum(2.2)<<endl;

	CApply<CIntArray> c1;
	CApply<CFloatArray> c2;

	cout<<c1.GetSum(cint, 2)<<endl;
	cout<<c2.GetSum(cfloat, 2.2)<<endl;

	return 0;
}

/*
class String
{
public:
	String(const char *str = "")
	{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = new char[strlen(s.m_data)+1];
		strcpy(m_data, s.m_data);
	}
	~String()
	{
		delete []m_data;
	}
private:
	char *m_data;
};

class Test
{
public:
	Test(int d = 0) :m_data(d)
	{}
private:
	int m_data;
};

int main()
{
	vector<Test> iv(5);// 0 0 0 0 0
	return 0;
}

/*
int main()
{
	int n = 1;
	int *ptr = (int*)__default_alloc_template<0, 0>::allocate(sizeof(int));

	int *tmp = (int*)__default_alloc_template<0, 0>::reallocate(ptr, sizeof(int), sizeof(int)*100);

	__default_alloc_template<0, 0>::deallocate(ptr, sizeof(int));

	return 0;
}

/*
void out_of_memeory()
{
	//GC
	//free();
}

int main()
{
	//set_new_handler();

	int n = 1;
	int *ptr = (int*)__default_alloc_template<0,0>::allocate(sizeof(int));
	int *ptr1 = (int*)__default_alloc_template<0, 0>::allocate(sizeof(int));  //8

	int *ptr2 = (int*)__default_alloc_template<0, 0>::allocate(sizeof(int)*25); //100

	int *ptr3 = (int*)__default_alloc_template<0, 0>::allocate(sizeof(int)* 16); //64

	int *ptr4 = (int*)__default_alloc_template<0, 0>::allocate(sizeof(int)* 14);

	return 0;
}

/*
struct Student
{
	char name[10];
	int age;
};

union obj
{
	obj *free_list_link; 
	char client_data[1];
};

obj* CreateFreeList(int n)
{
	char *chunk = (char*)malloc(sizeof(Student) * n);
	
	obj *cur_obj, *next_obj;
	obj *list = next_obj = (obj*)chunk;

	for (int i = 0; i < n; ++i)
	{
		cur_obj = next_obj;
		next_obj = (obj*)((char*)next_obj + sizeof(Student));

		if(i+1 == n)
			cur_obj->free_list_link = 0;
		else
			cur_obj->free_list_link = next_obj;
	}

	return list;
}

void main()
{
	int n = 5;
	obj *free_list = CreateFreeList(n);

	Student *ps1 = (Student*)free_list;
	free_list = free_list->free_list_link;  //p = p->next;

	strcpy(ps1->name,"zhangsan");
	ps1->age = 20;

	//回收空间
	obj *free_obj = (obj*)ps1;
	free_obj->free_list_link = free_list;
	free_list = free_obj;
}

/*
#define __ALIGN 8

size_t ROUND_UP(size_t bytes) //最小整数倍
{
	return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);
}

size_t FREELIST_INDEX(size_t bytes)
{
	return (bytes + __ALIGN - 1) / __ALIGN - 1;
}

void main()
{
	int bytes = 5;
	int result = ROUND_UP(bytes);
	cout<<result<<endl;
}


/*
void Out_Of_Memory()
{
	cout << "Out Of Memory." << endl; //free 启动垃圾回收器
	exit(1);
}

int main()
{
	//set_new_handler();
	__malloc_alloc_template<0>::set_malloc_handler(Out_Of_Memory);

	int n = 536870912;
	//int n = 10;

	try
	{
		int *ptr = (int*)__malloc_alloc_template<0>::allocte(sizeof(int)* n);
	}
	catch (bad_alloc &e)
	{
		cout<<e.what()<<endl;
	}

	return 0;
}


/*
void Out_Of_Memory()
{
	cout<<"Out Of Memory."<<endl;
	exit(1);
}


int main()
{
	//预防
	set_new_handler(Out_Of_Memory);

	int n = 536870912;
	int *ptr = new int[n];  //

	delete []ptr;
	return  0;
}

/*
namespace by
{
	template<class T>
	T* _allocate(size_t size, T*)
	{
		set_new_handler(0);
		T *tmp = (T*)::operator new(size * sizeof(T));  //malloc
		if (tmp == 0)
		{
			cerr<<"out of memory."<<endl;
			exit(1);
		}
		return tmp;
	}
	template<class T>
	void _deallocate(T *buffer)  //free
	{
		::operator delete(buffer);
	}
	template<class T1, class T2>
	void _construct(T1 *p, const T2 &value)  //定位new placement new
	{
		new(p) T1(value);
	}
	template<class T>
	void _destroy(T *ptr)
	{
		ptr->~T();
	}

	template<class T>
	class allocator
	{
	public:
		typedef T        value_type;
		typedef T*       pointer;
		typedef const T* const_pointer;
		typedef T&       reference;
		typedef const T& const_reference;
		typedef size_t   size_type;
	public:
		pointer allocate(size_type n, const void *hint = 0)
		{
			return _allocate(n, (pointer)0);
		}
		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}
		void construct(pointer p, const T &value)
		{
			_construct(p, value);
		}
		void destroy(pointer p)
		{
			_destroy(p);
		}
	};
}

void main()
{
	list<int, by::allocator<int>> mylist;
}

/*
int main()
{
	plus<int> pl;  //函数对象 - 仿函数

	int res = pl(10, 20);   //pl.operator()(10, 20);
	cout<<"res = "<<res<<endl;
}
*/