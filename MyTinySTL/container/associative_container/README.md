hashtable:  
哈希表是一种抽象数据结构，实现了关联数组或字典的功能, 将键映射到值  
哈希表使用一个哈希函数来计算一个索引，也称为哈希码，指向一个数组的桶或槽，从中可以找到或存储所需的值   
在查找时，键被哈希，生成的哈希值指示存储相应值的位置，同时要考虑哈希冲突， 哈希表的优点是插入和搜索操作非常快速  
哈希表的基本思想是，对于每个要存储的元素，计算一个唯一的地址，并将值放在数组中该索引处

常用Hash函数  
直接寻址法：取关键字或关键字的某个线性函数值为散列地址。即H(key)=key或H(key) = a·key + b，其中a和b为常数（这种散列函数叫做自身函数)  
数字分析法：分析一组数据，找出数字的规律，尽可能利用这些数据来构造冲突几率较低的散列地址  
平方取中法：取关键字平方后的中间几位作为散列地址  
折叠法：将关键字分割成位数相同的几部分，最后一部分位数可以不同，然后取这几部分的叠加和（去除进位）作为散列地址  
随机数法：选择一随机函数，取关键字作为随机函数的种子生成随机值作为散列地址，通常用于关键字长度不同的场合  
除留余数法：取关键字被某个不大于散列表表长m的数p除后所得的余数为散列地址。即 H(key) = key MOD p,p<=m  

冲突处理:  
    开放寻址法  
    再散列法  
    链地址法(拉链法)  
    建立一个公共溢出区  
``` 
    hashtable_node
        包含一个next指针和节点值
        
    value traits:
        分为两种，set 和 map
        template <typename T, bool>
        struct ht_value_traits_imp：
            对应set，key_value == mapped_value == value_type
        
        template <typename T>
        struct ht_value_traits_imp<T, true>
            对应map 的 key-value，key_value = key 即pair.first, mapped_value = value 即pair.seond, 
            value_type = key-value 即pair
        
        ht_value_traits：
            先通过判断是不是pair来判断是map还是set
            实现get_key, get_value方法
        
    ht_iterator: 单向迭代器
        ht_iterator_base：
            node_ptr node;   // 迭代器当前所指节点
            contain_ptr ht;  // 保持与容器的连结
        
        ht_iterator：
            继承ht_iterator_base，实现构造函数  
            实现操作符*, ->, ++, --重载
        
        ht_local_iterator：
            仅针对当前链上的元素
            
    hashtable: 采用拉链法解决冲突
        使用vector作为桶，元素为结点指针
        
        // 构造函数
        explicit hashtable(size_type bucket_count,
                   const Hash &hash = Hash(),
                   const KeyEqual &equal = KeyEqual()) 
                   
        template <class Iter, typename std::enable_if<
        mystl::is_input_iterator<Iter>::value, int>::type = 0>
        hashtable(Iter first, Iter last,
                  size_type bucket_count,
                  const Hash &hash = Hash(),
                  const KeyEqual &equal = KeyEqual())      
                  
        hashtable(const hashtable &rhs)
        hashtable(hashtable &&rhs)
        
        // 比较关键的几个私有函数
        is_equal()
        const_iterator M_cit(node_ptr node)()
        iterator M_begin()
        
        // 操作分为两种，键值可重复的与不可重复的，分别针对set、multiset 和 map、multimap
        iterator emplace_multi(Args&& ...args);
        pair<iterator, bool> emplace_unique(Args&& ...args);
        
        iterator insert_multi
        pair<iterator, bool> insert_unique
        
        // 针对bucket实现了一系列接口    
```
unorder_set:
    unordered_set: 键值不允许重复
    unordered_mulitset: 键值允许重复

unorder_mapt:
    unordered_map: 键值不允许重复
    unordered_mulitmap: 键值允许重复