```
包含三个文件：
    alloc.h: 使用二级配置器实现内存分配
    allocator.h: 仅使用一级配置器实现内存分配
    construct.h: 对象的构造和销毁
```

```
了解的知识:
    new operator 分为两部分:
        operator new：分配足够的内存以便容纳所需类型的对象
        placement new：调用构造函数初始化内存中的对象
    delete operator 分为两部分:  
        placement delete：执行对象的析构函数
        operator delete：里面执行 free 函数
```

```
allocator.h
    // allocate
    调用operator new分配内存, 不构造对象
    
    // deallocate
    调用operator delete释放内存, 不析构对象
    
    // construct / destroy
    调用全局的construct / destroy

construct.h:
    //定义了全局构造、销毁函数
    
    // 在指定的内存空间，调用Ty的默认构造函数，构造对象
    template <typename T>
    void construct(Ty *ptr);
    
    // 在指定的内存空间，调用Ty1::Ty1(value)，构造对象
    template <typename Ty1, typename Ty2>
    void construct(Ty1 *ptr, const Ty2& value);
    
    // 在指定的内存空间，使用可变长参数列表
    template <typename Ty, typename ... Args>
    void construct(Ty *ptr, Args&& ...args);
    
    // destroy调用析构函数并且有两个版本
    
    // 传入指针, 判断类型Ty是否为 “容易销毁的(trivially destructible)”
    // 如果是，则什么也不做， 如果不是，调用对应的析构函数
    template <typename Ty>
    void destroy(Ty *pointer);
    
    // 传入迭代器范围[first, last), 至少是ForwardIter
    // 判断同上
    template <typename ForwardIter>
    void destroy(ForwardIter first, ForwardIter last)
    
alloc.h
    采取二级配置器
    1. 当申请内存大于阈值时，直接采用malloc、free管理内存
    2. 当申请内存小于阈值时，使用内存池管理内存
    
    // 根据申请空间大小选择调用的分配方式
    static void *allocate(size_t n);
    
    // 根据申请空间大小选择释放内存的方式
    static void *deallocate(size_t n);
    
    // 重新分配空间
    // 调用deallocate释放原空间，调用allocate重新分配新空间
    inline void *alloc::reallocate(void *p, size_t old_size, size_t new_size)
    
    // 根据区块大小，选择第n个free lists
    inline size_t M_freelist_index(size_t bytes);
    
    // 将申请的内存大小上调至内存池中所对应的大小
    inline size_t alloc::M_align(size_t bytes);
    
    // 重新填充 free list
    void *alloc::M_refill(size_t n)
    
    // 从内存池中分配空间给freelist，条件不允许时，会调整nobj，内存不足时，调用其余处理
    char *alloc::M_chunk_alloc(size_t size, size_t &nobj)
```
