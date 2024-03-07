exceptdef.h  
    使用define定义封装几种常见的异常供容器调用  
memory.h  
```
    // 获取对象地址
    constexpr Tp *address_of(Tp &value) noexpect;
    
    // 获取临时缓冲区，返回地址指针及其大小
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len);
    
    // 模板类: temporary_buffer
    // 用于进行临时缓冲区的申请与释放
    template <typename ForwardIterator, typename T>
    class temporary_buffer;
    // 由于拷贝构造函数和拷贝赋值运算符被删除，因此不能使用拷贝初始化
  
    // auto_ptr已经被C++11淘汰
```

type_traits.h  
定义了m_bool_constant类用来代表true / false  
声明pair，is_pair用来判断是否为pair  
  
uninitialized.h  
```
    // uninitialized_copy
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result);
    
    // uninitialized_copy_n
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    ForwardIter uninitialized_copy_n(InputIter first, Size n, ForwardIter result);
    
    // uninitialized_fill
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    void uninitialized_fill(ForwardIter first, ForwardIter last, const T &value);
    
    // uninitialized_fill_n
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &value);
     
    // uninitialized_move
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result);
    
    // uninitialized_move
    // 针对未初始化区域进行构造，如果是POD类型，直接拷贝，否则逐个构造
    ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter result);
```
util.h  
定义了全局函数move、forward、swap 和 模板类pair



