五种迭代器：
1. 所有的迭代器均支持：iter++, ++iter;
2. InputIter:    
   *inputIter: 复引用迭代器，作为右值  
   inputIter = inputIter1: 将一个迭代器赋给另一个迭代器  
   inputIter == inputIter1: 比较迭代器的相等性  
   inputIter != inputIter1: 比较迭代器的不等性
   
3. OutputIter:  
   *outputIter: 复引用迭代器，作为左值  
   outputIter = outputIter1: 将一个迭代器赋给另一个迭代器  
4. ForwardIter:  
    提供输入、输出迭代器的所有功能
5. BidirectionalIter:  
   包括前向迭代器的所有功能  
   --bidirectionalIter: 前置自减迭代器  
   bidirectionalIter--: 后置自减迭代器  
6. RandomAccessIter:
   包括双向迭代器的所有功能  
   randomAccessIter += i:       将迭代器递增i位  
   randomAccessIter -= i:       将迭代器递减i位  
   randomAccessIter +  i:       获取向后移动i位的迭代器  
   randomAccessIter -  i:       获取向前移动i位的迭代器  
   randomAccessIter[i]:         获取向前移动i位的迭代器  
   randomAccessIter <  randomAccessIter1:       迭代器Iter的位置在Iter1前，返回true，否则返回false    
   randomAccessIter <= randomAccessIter1:       迭代器Iter的位置在Iter1前面或同一位置时，返回true，否则返回false  
   randomAccessIter >  randomAccessIter1:       迭代器Iter的位置在Iter1后，返回true，否则返回false  
   randomAccessIter >= randomAccessIter1:       迭代器Iter的位置在Iter1前面或同一位置时，返回true，否则返回false
   
继承关系：  
   struct input_iterator_tag {};
   struct output_iterator_tag {};  
   struct forward_iterator_tag : public input_iterator_tag {};  
   struct bidirectional_iterator_tag : public forward_iterator_tag {};  
   struct random_access_iterator_tag : public bidirectional_iterator_tag {};
```
   // 迭代器模板
   template <typename Category, typename T, typename Distance = ptrdiff_t,
      typename Pointer = T*, typename Reference = T&>
   struct iterator;
     
   // 判断是否是迭代器
   template<typename T>
   struct has_iterator_cat；
   
   // 判断是否能隐式转换为XXX_iterator_tag，能则萃取特性
   template <typename Iterator>
   struct iterator_traits_impl<Iterator, bool>;
    
   // 结合has_iterator_cat、iterator_traits_impl
   // 判断是否是迭代器，再进一步判断是否是input \ output迭代器
   template <typename Iterator, bool>
   struct iterator_traits_helper {};
   
   // 进一步封装
   template <typename Iterator>
   struct iterator_traits
   :public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};
   
   // 针对原生指针特化, 原生指针不满足迭代器特性，但是属于迭代器
   template <typename T>
   struct iterator_traits<T*>;
   
   // 利用继承m_bool_constant，判断类型T是否是迭代器类型U
   template <typename T, typename U, 
         bool = has_iterator_cat<iterator_traits<T>>::value>
   struct has_iterator_cat_of
   :public m_bool_constant<std::is_convertible<
      typename iterator_traits<T>::iterator_category, U>::value> {};
      
   // 萃取迭代器的特性，包括category、difference_type、value_type、
   template <typename Iterator>
   typename iterator_traits<Iterator>::iterator_category
   iterator_category(const Iterator&);
   
   // 针对不同迭代器类型，实现对应的 
   distance、advance函数
```

    