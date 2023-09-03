# SGI_STL_annotated
剖析SGI STL源码
1.STL sgi版本的源码剖析，首先第一部先熟悉空间配置器allocator。
空间配置器就是负责内存空间申请。
空间配置器不光负责空间申请，为了能够达到通用，一共负责四件事：
(1)allocator：申请空间
(2)deallocate：释放空间
(3)construct：构造对象
(4)destroy：析构对象

• C++是通过::operato new()申请空间，::operato delete()释放空间，这两个全局函数相
当于C语言中的malloc()和free(),所以，SGI直接使 malloc和free完成内存的申请和释放。

• 考虑小额区块可能造成内存碎片问题，SGI将空间配置器实现成两级配置器，其中一级空
间配置器和二级空间配置器的分水岭为128字节
一级空间配置器是进行大块内存的分配，在一级空间配置启当中有set_new_handler机制，
set_new_handler机制是应对空间不足采取的机制，空间配置器的使命：尽可能的分配成功。
二级是进行小块内存分配，就是内存池机制。


2.萃取跟迭代器
在SGI当中大量的使用了萃取，通过萃取获取类型，传给对应的迭代器
跌代器提供一种方法，使之能够按照某种顺序遍历容器所含的元素，但又不需要暴露其内部
的实现方式
value_type:值类型，指迭代器所致对象的类型
difference_type:两个迭代器之间的距离
pointer:指针类型
reference:引⽤类型
iterator_category:迭代器类型

迭代器总共就五种类型:
Inputiterator:输人迭代器
Outputiterator:输出迭代器
Forwarditerator:前向迭代器
Bidirectionaliterator:双向迭代器
RandomAccessiterator:随机迭代器

3.容器：
#序列容器:
(1)vector容器:底层就是一个动态数组。
iterator start;
iterator finish;
iterator end_of_storage;
typedef simple_alloc<value_type, Alloc> data_allocator;
核心就是这3个指针，加上一个空间配置器。
(2)list容器:底层就是一个双向链表。
struct __list_node
{
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
	T data;
};
核心结构就是一个双向链表，再加上一个空间配置器。
(3)deque容器:底层是一个二维空间维持的双端队列，
deque是所有容器当中最复杂的,可以通过画图，展示比较清晰。
iterator start;
iterator finish;
map_pointer map;    
size_type   map_size;
map负责：负责保存每一个缓冲区的地址
start,finish负责：负责数据缓冲区的起始和结束位置的指向
map_size负责：负责记录中控器的节点个数。
deque是分段连续空间，维持连续假象的任务落在了迭代器身上
deque迭代器需要具备能够指出分段缓冲区在哪里
deque迭代器还需能够判断缓冲区的边沿，需要维持向前或者向后跳跃
deque迭代器为了完成上述任务，需要随时掌控中控器map
核心结构就是这4个外配一个空间配置器，


(4) stack、queue:相当于是适配器,底层是通过deque的机构进行适配，
当然你自己也可以利用vector等容器区适配。
(5)priority_queue：底层是一个大根堆结构。
主要通过make_heap建堆，push_heap入堆、pop_heap出堆、heap_sort堆排序来实现，heap底层使用动态数组vector实现。
#2.关联容器:
关联容器四兄弟：set、map、multiset、multimap底层实现的是一颗红黑树结构
1、每个节点不是红色就是黑
2、根节点必须是黑色
3、如果根节点为红色，其子节点必须是黑色
4、任意节点到NULL的任何路径，所含的黑色节点数必须相同（注：空指针则认为是黑色节点）
-------------------------------------------------------------------------
记住红黑树内功心法：【头脚皆为黑，黑同红不连】


红⿊树的平衡调整心法：
【插入看叔伯，删除看兄弟】

无论是插入节点还是删除节点，当不满足红黑树性质的时候，就发生了不平衡，此时必须要
通过旋转方式，旋转根AVL树旋转方式一样，四种旋转方式。
(2)非关联容器四兄弟:unordered_set、unordered_multiset、unordered_map、unordered_multimap
底层是一个链式hash_table.

hasher hash; //哈希函数
ExtractKey get_key;  //获取元素
vector<node*, Alloc> buckets;  //数组  桶节点
size_type num_elements; //元素个数
核心就是一个hashtable和空间配置器。
4.算法：
STL里边包罗很多算法，堆算法，快排、求topk问题算法。集合算法等
5.仿函数:
6.适配器:


