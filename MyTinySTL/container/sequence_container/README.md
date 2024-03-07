包含常见的顺序容器  
    vector、list、deque  
```
vector:
    // 空间配置器：
        mystl::allocator<T>
        
    // 迭代器, 是普通指针：
    // 问题：算法是基于迭代器的，但vector的迭代器是普通指针，如何调用函数。
    // 答：因为针对指针进行了特化
       value_type*  
       
    // 使用三个迭代器标识容器的位置
    begin_、end_、cap_
    
    // 构造函数 
    vector();           // 默认构造函数，调用try_init()
    explicit vector(n); // 有参构造函数, 申请n个value_type()
    vector(n, value);   // 有参构造函数, 申请n个value
    
    vector(Iter first, Iter last);  // 迭代器初始化，但是T*算是input_iterator嘛?
    vector(const vector &rhs);      // 拷贝构造函数，调用range_init
    vector(vector &&rhs);           // 移动构造函数，冒号初始化
    vector(ilist);                  // 列表初始化，调用range_init
    
    operator=(const vector &rhs);   // 拷贝赋值运算符重载
    operator=(vector &&rhs);        // 移动赋值运算符重载
    operator=(ilist);               // 初始化列表赋值
    
    ~vector();                      // 析构函数
    
    // 迭代器相关操作，获取对应的迭代器
    
    // 容量相关操作，计算begin_、end_、cap_
  
    reserve(size_type n);    // 针对cap_, 小则忽略，大于则重新申请空间
    shrink_to_fit()；        // 使得end_ = cap_.
    
    // 访问元素, 返回引用而不是拷贝
    operator[]
    at()
    front()
    back()
    data()
    
    // 修改容器容量
    assign(n, value);         // 调用fill_assign, 填充n个value
    assign(Iter, Iter);       // 调用copy_assgn
    assign(il);               // 调用copy_assgn
    
    emplace(&&);              // 使用移动语义添加元素
    emplace_back(&&);         // 在末尾使用移动语义添加元素 
    push_back(&);             // 在末尾添加元素
    push_back(&&);            // 调用emplace_back
    pop_back();               // 弹出末尾元素
    
    insert(pos, val);         // 在pos处插入对象
    insert(pos, &&);          // 调用emplace
    insert(pos, n, val);      // 调用fill_insert()
    insert(pos, first, last); // 调用copy_insert()
    
    erase(pos);               // 删除 pos 位置上的元素          
    erase(first, last);       // 删除 first，last的元素
    clear();                  // 调用erase()
    
    resize();                 // 空间够则删除，不够则插入
    reverse();                // 翻转
    swap();                   // 添加swap函数，交换三个指针
    
    // 辅助函数
    try_init();               // 默认申请16个大小的元素，失败的话，所有迭代器赋为nullptr
    init_space(size, cap);    // 申请cap个大小的元素，失败的话，所有迭代器赋为nullptr
    fill_init(n, value);      // 申请空间，使用value初始化uninitialized_fill_n
    range_init(first, last);  // 计算迭代器范围，申请空间，调用uninitialized_copy
    destroy_and_recover();    // 销毁对象，释放空间
    
    get_new_cap();            // 内存不够则扩容

    fill_assign(n, value);    // 填充n个value
    copy_assign(IIter);       // 针对inputIter特例化
    copy_assign(FIter);       // 针对ForwardIter特例化
    
    reallocate_emplac();      // 重新分配空间并在 pos 处就地构造元素
    reallocate_insert();      // 重新分配空间并在 pos 处插入元素
    fill_insert();            // 插入元素，问题：为什么会使用move而不是copy
    copy_insert();            // 插入元素
    
    // 运算符、swap函数重载
```
list.h
``` 
    // 将节点分未base_node 和 data_node
    template <typename T> struct list_node_base;  // 指向前后节点
    template <typename T> struct list_node;       // 数据节点，继承了base_node
    
    // 迭代器、const 迭代器，继承双向迭代器
    struct list_iterator :public mystl::iterator<mystl::bidirectional_iterator_tag, T> 
    需要重载 *操作符和->操作符
    operator++() 返回引用
    operator++(int) 返回临时对象
    
    // list, 双向链表，前闭后开
    私有成员：node_, size_
    
    // 构造函数
    普通构造函数使用fill_init实现初始化
    迭代器初始化、花括号初始化、拷贝初始化使用copy_init实现初始虎啊
    移动构造函数：
    list(list &&rhs) noexcept :node_(rhs.node_), size_(rhs.size_);
    
    list &operator=(const list &rhs);
    list &operator=(list &&rhs);
    list &operator=(std::initializer_list<T> ilist);
    
    其余操作类似于vector, 但函数实现方式不同， 具体实现见源码
```
deque.h
``` 
    deque_buf_size:
    获取buf_size, sizeof(T)较大时默认为16，较小时为 4096 / sizeof(T)
    buf_size 用来表示每个缓存区的默认大小
    
    deque_iterator: random_access_iterator
    deque的迭代器比较复杂，由于duque实现的特殊性，每个迭代器包含四个指针:
        value_pointer   cur;    // 指向所在缓冲区的当前元素
        value_pointer   first;  // 指向所在缓冲区的头部
        value_pointer   last;   // 指向所在缓冲区的尾部
        map_pointer     node;   // 指向缓冲区所在节点，即中控区中某节点
    
    // 构造函数
    deque_iterator()
    deque_iterator(value_pointer v, map_pointer n)
    deque_iterator(const const_iterator &rhs)
    deque_iterator(iterator &&rhs)
    
    // 操作符重载
    self &operator=(const iterator &rhs)
    
    // 辅助函数
    void set_node(map_pointer new_node)
    参数为new_node, 修改了node、first、last属性，但是未修改cur
    
    // 操作符重载
    由于是random迭代器，需要实现所有对应的操作符
    
        reference operator*()   const { return *cur; }
        返回cur所指的值
        
        pointer   operator->()  const { return cur; }
        返回cur指针本身
        
        difference_type operator-
        迭代器距离需要考虑node之间的距离以及cur离firs的距离两部分
        
        self &operator++()
        self operator++(int)
        self &operator--()
        self &operator--(int)
        需要考虑到达了缓冲区边界的情况，如果到了缓冲区边界就要修改node指向
        
        self &operator+=(difference_type n)
        两种情况：
            仍在当前缓冲区，仅移动cur即可
            向前或向后缓冲区移动，需先调整node，再调整cur
            
        self operator+(difference_type n)
        self &operator-=(difference_type n)
        self operator-(difference_type n)
        
        reference operator[](difference_type n)
        重载[]操作符， 分别调用operator+, operator*，返回cur
        
        // 重载比较操作符
        
    
    deque:
    四个关键元素：
        iterator       begin_;     // 指向第一个节点
        iterator       end_;       // 指向最后一个结点
        map_pointer    map_;       // 指向一块 map，map 中的每个元素都是一个指针，指向一个缓冲区
        size_type      map_size_;  // map 内指针的数目
        
    // 构造函数
    deque()
    deque(size_type n)
    deque(size_type n, const value_type &value)
    deque(IIter first, IIter last)
    deque(std::initializer_list<value_type> ilist)
    deque(const deque &rhs)
    deque(deque &&rhs)
    
    // 赋值运算符重载
    deque& operator=(const deque &rhs);
    deque& operator=(deque &&rhs);  
    deque& operator=(std::initializer_list<value_type> ilist)
    
    ~deque()
    
    其余操作类似于vector, 但函数实现方式不同, 具体实现见源码
```