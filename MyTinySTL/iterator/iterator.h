#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

// 迭代器设计：
#include <cstddef>
#include "type_traits.h"
#include <iostream>
namespace mystl {
    // 五种迭代器类型
    // 以 class 来定义选代器的各种分类标签，不仅可以促成重载机制的成功运作使编译器得以正确执行重载决议
    // 通过继承，可以消除单纯传递调用的函数。
    struct input_iterator_tag {};  // 只读
    struct output_iterator_tag {};  // 只写
    struct forward_iterator_tag :public input_iterator_tag {};  // 允许读写，但只能做前向移动
    struct bidirectional_iterator_tag :public forward_iterator_tag {};  // 允许读写，可以做双向移动
    struct random_access_iterator_tag :public bidirectional_iterator_tag {};  // 允许读写，可以任意移动

    // iterator 模板
    // eg: template <XXX_iterator_tag, int>
    template <typename Category, typename T, typename Distance = ptrdiff_t,
            typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Category        iterator_category;  // 以上迭代器的一种
        typedef T               value_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
        typedef Distance        difference_type;
    };

    // iterator traits
    template<typename T>
    struct has_iterator_cat {  // 判断是否有迭代器类别 iterator_category
    private:
        struct two {  // 代表两个字符大小
            char a;
            char b;
        };

        // 通过传入的模板类型有无typename U::iterator_category来返回two 还是char
        template<typename U>
        static two test(...);  // 接收任意参数，泛化版本

        template<typename U>
        static char test(typename U::iterator_category* = 0);


    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);  // 匹配test函数，返回true/false.
    };

    template<typename T>
    template<typename U>
    typename has_iterator_cat<T>::two has_iterator_cat<T>::test(...) {
        return has_iterator_cat::two();
    }

    template<typename T>
    template<typename U>
    char has_iterator_cat<T>::test(typename U::iterator_category*) {
        return char(0);
    }

    // 不能隐式转换为XXX_iterator_tag
    template <typename Iterator, bool>  // ==template <typename Iter, false>
    struct iterator_traits_impl {};

    // 能隐式转换为XXX_iterator_tag
    template <typename Iterator>
    struct iterator_traits_impl<Iterator, true> {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::difference_type   difference_type;
    };

    // 没有迭代器类型，has_iterator_cat 返回为false
    template <typename Iterator, bool>
    struct iterator_traits_helper {};

    // 有迭代器，判断是否能隐式转换为input_iterator_tag或output_iterator_tag
    template <typename Iterator>
    struct iterator_traits_helper<Iterator, true>
        :public iterator_traits_impl<Iterator,
        std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value> {};

    // 萃取迭代器的特性，这里value对应false和true
    template <typename Iterator>
    struct iterator_traits
    :public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

    // 针对原生指针的偏特化版本
    template <typename T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    template <typename T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    // 判断是否是迭代器类型，且类型是U
    template <typename T, typename U,
            bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
    :public m_bool_constant<std::is_convertible<
        typename iterator_traits<T>::iterator_category, U>::value> {};

    template <typename T, typename U>
    struct has_iterator_cat_of<T, U, false> :public m_false_type {};

    // 对每一种迭代器类型，调用has_iterator_cat_of
    template <typename Iter>
    struct is_input_iterator :public has_iterator_cat_of<Iter, input_iterator_tag> {};

    template <typename Iter>
    struct is_output_iterator :public has_iterator_cat_of<Iter, output_iterator_tag> {};

    template <typename Iter>
    struct is_forward_iterator :public has_iterator_cat_of<Iter, forward_iterator_tag> {};

    template <typename Iter>
    struct is_bidirectional_iterator :public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

    template <typename Iter>
    struct is_random_access_iterator :public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

    // 迭代器可以分为原生指针、input、output三种，这里判断是否是input或output
    template <typename Iterator>
    struct is_iterator
    :public m_bool_constant<is_input_iterator<Iterator>::value || is_output_iterator<Iterator>::value> {};

    // 萃取某个迭代器的 category，若传入的不是迭代器，会报错
    template <typename Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&) {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    // 萃取某个迭代器的 distance_type
    template <typename Iterator>
    typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    // 萃取某个迭代器的 value_type
    template <typename Iterator>
    typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    // 以下函数用于计算迭代器之间的距离
    // input_iterator_tag、forward_iterator_tag、bidirectional_iterator_tag
    template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag) {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }
    // 针对random_access_iterator_tag的特化版本
    template <typename RandomIter>
    typename iterator_traits<RandomIter>::difference_type
    distance_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag) {
        return last - first;
    }

    // 封装 distance
    template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last) {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // 以下函数用于让迭代器前进 n 个距离
    // advance 的 input_iterator_tag 的版本
    template <class InputIterator, class Distance>
    void advance_dispatch(InputIterator &i, Distance n, input_iterator_tag) {
        while (n--) { ++i; }
    }

    // advance 的 bidirectional_iterator_tag 的版本
    template <class BidirectionalIterator, class Distance>
    void advance_dispatch(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
        if (n >= 0)
            while (n--)  { ++i; }
        else
            while (n++)  { --i; }
    }

    // advance 的 random_access_iterator_tag 的版本
    template <class RandomIter, class Distance>
    void advance_dispatch(RandomIter &i, Distance n, random_access_iterator_tag) {
        i += n;
    }

    // 封装 advance
    template <class InputIterator, class Distance>
    void advance(InputIterator &i, Distance n) {
        advance_dispatch(i, n, iterator_category(i));
    }
} // namespace mystl
#endif //TINYSTL_ITERATOR_H
