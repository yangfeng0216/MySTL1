仿函数，即函数对象 \
通过重载function call操作符（operator()）使得对象的行为类似于一个函数
```
    // traits 模板
    // 定义一元函数的参数型别和返回值型别
    template <typename Arg, typename Result>
    struct unary_function;
    
    // 定义二元函数的参数型别的返回值类型
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function；

    // 算术运算
    // 加法
    template <typename T>
    struct plus :public binary_function<T, T, T>;
    
     // 减法
    template <typename T>
    struct minus :public binary_function<T, T, T>;
    
    // 乘法
    template <typename T>
    struct multiplies :public binary_function<T, T, T>;
    
    // 除法
    template <typename T>
    struct divides :public binary_function<T, T, T>;
    
    // 取余
    template <typename T>
    struct modulus :public binary_function<T, T, T>;
    
    // 否定
    template <typename T>
    struct negate :public unary_function<T, T>
    
    // 加法证同
    template <typename T>
    T identity_element(plus<T>);
    
    // 乘法证同
    template <typename T>
    T identity_element(multiplies<T>);
    
    // 关系运算
    // 等于
    template <typename T>
    struct equal_to :public binary_function<T, T, bool>;
    
    // 不等于
    template <typename T>
    struct not_equal_to :public binary_function<T, T, bool>;
    
    // 大于
    template <typename T>
    struct greater :public binary_function<T, T, bool>  
    
    // 小于
    template <typename T>
    struct less :public binary_function<T, T, bool>;
    
    // 大于等于
    template <typename T>
    struct greater_equal :public binary_function<T, T, bool>;
    
    // 小于
    template <typename T>
    struct less_equal :public binary_function<T, T, bool>;
    
    // 逻辑运算
    // 逻辑与
    template <typename T>
    struct logical_and :public binary_function<T, T, bool>;
    
    // 逻辑或
    template <typename T>
    struct logical_or :public binary_function<T, T, bool>;
    
    // 逻辑非
    template <typename T>
    struct logical_not :public unary_function<T, bool>;
    
    // 正同、选择、投射
    // 证同函数：不会改变元素，返回本身
    template <typename T>
    struct identity :public unary_function<T, bool>;
    
    // 选择函数：接受一个pair，返回第一个元素
    template <typename Pair>
    struct selectfirst :public unary_function<Pair, typename Pair::first_type>;
    
    // 选择函数：接受一个pair，返回第二个元素
    template <typename Pair>
    struct selectsecond :public unary_function<Pair, typename Pair::second_type>;
    
    // 投射函数，返回第一参数
    template <typename Arg1, typename Arg2>
    struct projectfirst :public binary_function<Arg1, Arg2, Arg1>;
    
    // 投射函数，返回第二参数
    template <typename Arg1, typename Arg2>
    struct projectsecond :public binary_function<Arg1, Arg2, Arg2>;
    
    // 哈希函数
    // 函数对象用于计算元素的哈希值(在哈希表中的位置)，对一些内置型别和容器做了特化处理。
    // 对于大部分类型，hash function 什么都不做
    #define MYSTL_TRIVIAL_HASH_FCN(Type)                \
    template <>                                         \
    struct hash<Type> {                                 
        size_t operator()(Type val) const noexcept {    \
            return static_cast<size_t>(val);            \
        }                                               \
    };
    // 针对整数，返回原值，针对浮点数，逐位计算
```