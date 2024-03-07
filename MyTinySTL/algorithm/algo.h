#ifndef TINYSTL_ALGO_H
#define TINYSTL_ALGO_H

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

// 包含查找、排序等算法
#include <cstddef>
#include <ctime>

#include "algobase.h"
#include "memory.h"
#include "heap_algo.h"
#include "functional.h"
#include "reverse_iterator.h"

namespace mystl {
    /*****************************************************************************************/
    // all_of
    // 检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    /*****************************************************************************************/
    template <typename InputIter, typename UnaryPredicate>
    bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (!unary_pred(*first)) {
                return false;
            }
        }
        return true;
    }

    /*****************************************************************************************/
    // any_of
    // 检查[first, last)内是否存在某个元素满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    /*****************************************************************************************/
    template <typename InputIter, typename UnaryPredicate>
    bool any_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (unary_pred(*first)) {
                return true;
            }
        }
        return false;
    }

    /*****************************************************************************************/
    // none_of
    // 检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    /*****************************************************************************************/
    template <typename InputIter, typename UnaryPredicate>
    bool none_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (unary_pred(*first)) {
                return false;
            }
        }
        return true;
    }

    /*****************************************************************************************/
    // count
    // 对[first, last)区间内的元素与给定值进行比较，缺省使用 operator==，返回元素相等的个数
    /*****************************************************************************************/
    template <typename InputIter, typename T>
    typename mystl::iterator_traits<InputIter>::difference_type
    count(InputIter first, InputIter last, const T &value) {
        typename mystl::iterator_traits<InputIter>::difference_type n = 0;
        for (; first != last; ++first) {
            if (*first == value) {  // 相同就累加
                ++n;
            }
        }

        return n;
    }

    /*****************************************************************************************/
    // count_if
    // 对[first, last)区间内的每个元素都进行一元 unary_pred 操作，返回结果为 true 的个数
    /*****************************************************************************************/
    template <typename InputIter, typename UnaryPredicate>
    typename mystl::iterator_traits<InputIter>::difference_type
    count_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        typename mystl::iterator_traits<InputIter>::difference_type n = 0;
        for (; first != last; ++first) {
            if (unary_pred(*first)) {  // 返回为true就累加
                ++n;
            }
        }
        return n;
    }

    /*****************************************************************************************/
    // find
    // 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
    /*****************************************************************************************/
    template <typename InputIter, typename T>
    InputIter find(InputIter first, InputIter last, const T &value) {
        while (first != last && *first != value) {
            ++first;
        }
        return first;  // 指向该元素或first == last
    }

    /*****************************************************************************************/
    // find_if
    // 在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
    /*****************************************************************************************/
    template <typename InputIter, typename UnaryPredicate>
    InputIter find_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        while (first != last && !unary_pred(*first)) {
            ++first;
        }
        return first;  // 指向该元素或first == last
    }

    /*****************************************************************************************/
    // find_if_not
    // 在[first, last)区间内找到第一个令一元操作 unary_pred 为 false 的元素并返回指向该元素的迭代器
    /*****************************************************************************************/\
    template <typename InputIter, typename UnaryPredicate>
    InputIter find_if_not(InputIter first, InputIter last, UnaryPredicate unary_pred) {
        while (first != last && unary_pred(*first)) {
            ++first;
        }
        return first;  // 指向该元素或first == last
    }

    /*****************************************************************************************/
    // search
    // 在[first1, last1)中查找[first2, last2)的首次出现点
    // 暴力匹配
    /*****************************************************************************************/
    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2) {
        auto d1 = mystl::distance(first1, last1);
        auto d2 = mystl::distance(first2, last2);
        if (d1 < d2) {
            return last1;
        }
        auto current1 = first1;
        auto current2 = first2;
        while (current2 != last2) {
            if (*current1 == *current2) {
                ++current1;
                ++current2;
            }else {
                if (d1 == d2) {
                    return last1;
                }else {
                    current1 = ++first1;  // 移动起始位置
                    current2 = first2;
                    --d1;
                }
            }
        }

        return first1;
    }

    template <typename ForwardIter1, typename ForwardIter2, typename Compared>
    ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2, Compared comp) {
        auto d1 = mystl::distance(first1, last1);
        auto d2 = mystl::distance(first2, last2);
        if (d1 < d2) {
            return last1;
        }
        auto current1 = first1;
        auto current2 = first2;
        while (current2 != last2) {
            if (comp(*current1, *current2)) {
                ++current1;
                ++current2;
            }else {
                if (d1 == d2) {
                    return last1;
                }else {
                    current1 = ++first1;
                    current2 = first2;
                    --d1;
                }
            }
        }

        return first1;
    }

    /*****************************************************************************************/
    // search_n
    // 在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
    /*****************************************************************************************/
    template <typename ForwardIter, typename Size, typename T>
    ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T &value) {
        if (n <= 0) {
            return first;
        }
        first = mystl::find(first, last, value);
        while (first != last) {
            auto m = n - 1;
            auto i = first;
            ++i;
            while (i != last && m != 0 && *i == value) {
                ++i;
                --m;
            }
            if (m == 0) {
                return first;  // 找到符合结果的索引，返回
            }else {
                first = mystl::find(i, last, value);  // 重新查找下一处
            }
        }

        return last;
    }

    template <typename ForwardIter, typename Size, typename T, typename Compared>
    ForwardIter search_n(ForwardIter first, ForwardIter last,
                         Size n, const T &value, Compared comp) {
        if (n <= 0) {
            return first;
        }
        while (first != last) {  // 查找第一个符合的起点
            if (comp(*first, value)) {
                break;
            }
            ++first;
        }

        while (first != last) {
            auto m = n - 1;
            auto i = first;
            ++i;
            while (i != last && m != 0 && comp(*i, value)) {
                ++i;
                --m;
            }
            if (m == 0) {
                return first;  // 找到符合结果的索引，返回
            }else {
                while (i != last) {
                    if (comp(*i, value)) {
                        break;
                    }
                    ++i;
                }
                first = i;  // 重新查找下一处
            }
        }

        return last;
    }

    /*****************************************************************************************/
    // find_end
    // 在[first1, last1)区间中查找[first2, last2)最后一次出现的地方，若不存在返回 last1
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                                   ForwardIter1 first2, ForwardIter2 last2,
                                   forward_iterator_tag, forward_iterator_tag) {
        if (first2 == last2) {  // 查找目标为空，返回last1，表示“空子序列”的最后出现点
            return last1;
        }
        auto result = last1;
        while (true) {
            // 利用search查找某个子序列的首次出现点。找不到则返回last1
            auto new_result = mystl::search(first1, last1, first2, last2);
            if (new_result == last1) {  // 没找到
                return result;
            }else {  // 记录当前位置，查找下一处
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }

    // TODO: 这里对于反向迭代器的使用需要进一步理解
    // bidirectional_iterator_tag，可以逆向查找
    template <typename  BidirectionalIter1, typename  BidirectionalIter2>
    BidirectionalIter1 find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                                         BidirectionalIter2 first2, BidirectionalIter2 last2,
                                         bidirectional_iterator_tag, bidirectional_iterator_tag) {
        // 反向查找，即查找反向出现的第一次
        typedef reverse_iterator<BidirectionalIter1> reviter1;
        typedef reverse_iterator<BidirectionalIter2> reviter2;
        reviter1 rlast1(first1);
        reviter2 rlast2(first2);
        // 查找时将序列一和序列二统统逆转方向
        reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
        if (rresult == rlast1) {  // 没找到
            return last1;
        }
        auto result = rresult.base();  // 转回正向迭代器
        mystl::advance(result, -mystl::distance(first2, last2));  // 调整回子序列的起头处
        return result;
    }

    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1,
                          ForwardIter1 first2, ForwardIter2 last2) {
        typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
        typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
        return mystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
    }

    // forward_iterator_tag
    template <typename ForwardIter1, typename ForwardIter2, typename Compared>
    ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                                   ForwardIter1 first2, ForwardIter2 last2,
                                   forward_iterator_tag, forward_iterator_tag,
                                   Compared comp) {
        if (first2 == last2) {  // 查找目标为空，返回last1，表示“空子序列”的最后出现点
            return last1;
        }
        auto result = last1;
        while (true) {
            // 利用search查找某个子序列的首次出现点。找不到则返回last1
            auto new_result = mystl::search(first1, last1, first2, last2, comp);
            if (new_result == last1) {  // 没找到
                return result;
            }else {  // 记录当前位置，查找下一处
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }

    // bidirectional_iterator_tag，可以逆向查找
    template <typename  BidirectionalIter1, typename  BidirectionalIter2, typename Compared>
    BidirectionalIter1 find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                                         BidirectionalIter2 first2, BidirectionalIter2 last2,
                                         bidirectional_iterator_tag, bidirectional_iterator_tag,
                                         Compared comp) {
        // 反向查找，即查找反向出现的第一次
        typedef reverse_iterator<BidirectionalIter1> reviter1;
        typedef reverse_iterator<BidirectionalIter2> reviter2;
        reviter1 rlast1(first1);
        reviter2 rlast2(first2);
        // 查找时将序列一和序列二统统逆转方向
        reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, comp);
        if (rresult == rlast1) {  // 没找到
            return last1;
        }
        auto result = rresult.base();  // 转回正向迭代器
        mystl::advance(result, -mystl::distance(first2, last2));  // 调整回子序列的起头处
        return result;
    }

    template <typename ForwardIter1, typename ForwardIter2, typename Compared>
    ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1,
                          ForwardIter1 first2, ForwardIter2 last2,
                          Compared comp) {
        typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
        typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
        return mystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2(), comp);
    }
    /*****************************************************************************************/
    // find_first_of
    // 在[first1, last1)中查找[first2, last2)中的某些元素，返回指向第一次出现的元素的迭代器
    /*****************************************************************************************/
    template <typename InputIter, typename ForwardIter>
    InputIter find_first_of(InputIter first1, InputIter last1,
                            ForwardIter first2, ForwardIter last2) {
        for (; first1 != last1; ++first1) {  // 遍历序列一
            for (auto iter = first2; iter != last2; ++iter) {  // 遍历序列二
                if (*first1 == *iter) {
                    return first1;
                }
            }
        }
        return last1;
    }

    template <typename InputIter, typename ForwardIter, typename Compard>
    InputIter find_first_of(InputIter first1, InputIter last1,
                            ForwardIter first2, ForwardIter last2,
                            Compard comp) {
        for (; first1 != last1; ++first1) {
            for (auto iter = first2; iter != last2; ++iter) {
                if (comp(*first1, *iter)) {
                    return first1;
                }
            }
        }
        return last1;
    }

    /*****************************************************************************************/
    // for_each
    // 使用一个函数对象 f 对[first, last)区间内的每个元素执行一个 operator() 操作，但不能改变元素内容
    // f() 可返回一个值，但该值会被忽略
    // 将仿函数施行于区间的每一个元素上，f不可改变元素内容，first和last都是inputiterators，不保证接受赋值行为
    /*****************************************************************************************/
    template <typename InputIter, typename Function>
    Function for_each(InputIter first, InputIter last, Function f) {
        for (; first != last; ++first) {
            f(*first);
        }
        return f;
    }

    /*****************************************************************************************/
    // adjacent_find
    // 找出第一对匹配的相邻元素，缺省使用 operator== 比较，如果找到返回一个迭代器，指向这对元素的第一个元素
    /*****************************************************************************************/
    template <typename ForwardIter>
    ForwardIter adjacent_find(ForwardIter first, ForwardIter last) {
        if (first == last)  return last;
        auto next = first;
        while (++next != last) {
            if (*first == *next)  return first;  // 找到相同的相邻元素就返回
            first = next;
        }
        return last;
    }

    template <typename ForwardIter, typename Compared>
    ForwardIter adjacent_find(ForwardIter first, ForwardIter last, Compared comp) {
        if (first == last)  return last;
        auto next = first;
        while (++next != last) {
            if (comp(*first, *next))  return first;
            first = next;
        }
        return last;
    }

    /*****************************************************************************************/
    // lower_bound
    // 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
    // 应用于有序区间，二分查找的一种版本
    // 在不破坏排序状态的原则下，可插入value的第一个位置
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter, typename T>
    ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last,
                                const T &value, forward_iterator_tag) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0) {  // 二分查找
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (*middle < value) {
                first = middle;
                ++first;
                len = len - half - 1;
            }else {
                len = half;
            }
        }

        return first;
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T>
    RandomIter lbound_dispatch(RandomIter first, RandomIter last,
                               const T &value, random_access_iterator_tag) {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (*middle < value) {
                first = middle + 1;
                len = len - half - 1;
            }else {
                len = half;
            }
        }

        return first;
    }

    template <typename ForwardIter, typename T>
    ForwardIter
    lower_bound(ForwardIter first, ForwardIter last, const T &value) {
        return mystl::lbound_dispatch(first, last, value, iterator_category(first));
    }

    // forward_iterator_tag
    template <typename ForwardIter, typename T, typename Compared>
    ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last,
                                const T &value, forward_iterator_tag,
                                Compared comp) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0) {  // 二分查找
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (comp(*middle, value)) {
                first = middle;
                ++first;
                len = len - half - 1;
            }else {
                len = half;
            }
        }

        return first;
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T, typename Compared>
    RandomIter lbound_dispatch(RandomIter first, RandomIter last,
                               const T &value, random_access_iterator_tag,
                               Compared comp) {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (comp(*middle, value)) {
                first = middle + 1;
                len = len - half - 1;
            }else {
                len = half;
            }
        }

        return first;
    }

    template <typename ForwardIter, typename T, typename Compared>
    ForwardIter
    lower_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
        return mystl::lbound_dispatch(first, last, value, iterator_category(first), comp);
    }

    /*****************************************************************************************/
    // upper_bound
    // 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
    // 应用于有序空间，二分查找的一个版本
    // 在不破坏排序状态的原则下，可插入value的最后一个位置
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter, typename T>
    ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last,
                                const T &value, forward_iterator_tag) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0) {  // 二分查找
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (value < *middle) {
                len = half;

            }else {
                first = middle;
                ++first;  // 不能像random一样，直接令first = middle + 1
                len = len - half - 1;
            }
        }

        return first;
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T>
    RandomIter ubound_dispatch(RandomIter first, RandomIter last,
                               const T &value, random_access_iterator_tag) {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (value < *middle) {
                len = half;
            }else {
                first = middle + 1;
                len = len - half - 1;
            }
        }

        return first;
    }

    template <typename ForwardIter, typename T>
    ForwardIter
    upper_bound(ForwardIter first, ForwardIter last, const T& value) {
        return mystl::ubound_dispatch(first, last, value, iterator_category(first));
    }

    // forward_iterator_tag
    template <typename ForwardIter, typename T, typename Compared>
    ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last,
                                const T &value, forward_iterator_tag,
                                Compared comp) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0) {  // 二分查找
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (comp(value, *middle)) {
                len = half;

            }else {
                first = middle;
                ++first;  // 不能像random一样，直接令first = middle + 1
                len = len - half - 1;
            }
        }

        return first;
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T, typename Compared>
    RandomIter ubound_dispatch(RandomIter first, RandomIter last,
                               const T &value, random_access_iterator_tag,
                               Compared comp) {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (comp(value, *middle)) {
                len = half;
            }else {
                first = middle + 1;
                len = len - half - 1;
            }
        }

        return first;
    }

    template <typename ForwardIter, typename T, typename Compared>
    ForwardIter
    upper_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
        return mystl::ubound_dispatch(first, last, value, iterator_category(first), comp);
    }

    /*****************************************************************************************/
    // binary_search
    // 二分查找，如果在[first, last)内有等同于 value 的元素，返回 true，否则返回 false
    // 应用于有序空间
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    bool binary_search(ForwardIter first, ForwardIter last, const T &value) {
        auto i = mystl::lower_bound(first, last, value);
        return i != last && !(value < *i);
    }

    template <typename ForwardIter, typename T, typename Compared>
    bool binary_search(ForwardIter first, ForwardIter last,
                       const T &value, Compared comp) {
        auto i = mystl::lower_bound(first, last, value);
        return i != last && !comp(value, *i);
    }

    /*****************************************************************************************/
    // equal_range
    // 查找[first,last)区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首尾
    // 第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter, typename T>
    mystl::pair<ForwardIter, ForwardIter>
    erange_dispatch(ForwardIter first, ForwardIter last,
                    const T &value, forward_iterator_tag) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle, left, right;
        while (len > 0) {  // 整个区间尚未遍历完毕
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (*middle < value) {
                first = middle;  // 将运作区间缩小至后半段，提高效率
                ++first;
                len = len - half - 1;
            }else if (value < *middle) {
                len = half;  // 将运作区间缩小至前半段，提高效率
            }else {
                left = mystl::lower_bound(first, middle, value);  // 前半段查找left
                mystl::advance(first, len);
                right = mystl::upper_bound(++middle, first, value);  // 后半段查找right
                return mystl::pair<ForwardIter, ForwardIter>(left, right);
            }
        }
        return mystl::pair<ForwardIter, ForwardIter>(last, last);
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T>
    mystl::pair<RandomIter, RandomIter>
    erange_dispatch(RandomIter first, RandomIter last,
                    const T &value, random_access_iterator_tag) {
        auto len = last - first;
        auto half = len;
        RandomIter middle, left, right;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (*middle < value) {
                first = middle + 1;
                len = len - half - 1;
            }else if (value < *middle) {
                len = half;
            }else {
                left = mystl::lower_bound(first, middle, value);
                right = mystl::upper_bound(++middle, first + len, value);
                return mystl::pair<RandomIter, RandomIter>(left, right);
            }
        }
        return mystl::pair<RandomIter, RandomIter>(last, last);
    }

    template <typename ForwardIter, typename T>
    mystl::pair<ForwardIter, ForwardIter>
    equal_range(ForwardIter first, ForwardIter last, const T &value) {
        return mystl::erange_dispatch(first, last, value, iterator_category(first));
    }

    template <typename ForwardIter, typename T, typename Compared>
    mystl::pair<ForwardIter, ForwardIter>
    erange_dispatch(ForwardIter first, ForwardIter last,
                    const T &value, forward_iterator_tag,
                    Compared comp) {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle, left, right;
        while (len > 0) {  // 整个区间尚未遍历完毕
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (comp(*middle, value)) {
                first = middle;  // 将运作区间缩小至后半段，提高效率
                ++first;
                len = len - half - 1;
            }else if (comp(value, *middle)) {
                len = half;  // 将运作区间缩小至前半段，提高效率
            }else {
                left = mystl::lower_bound(first, middle, value);  // 前半段查找left
                mystl::advance(first, len);
                right = mystl::upper_bound(++middle, first, value);  // 后半段查找right
                return mystl::pair<ForwardIter, ForwardIter>(left, right);
            }
        }
        return mystl::pair<ForwardIter, ForwardIter>(last, last);
    }

    // random_access_iterator_tag
    template <typename RandomIter, typename T, typename Compared>
    mystl::pair<RandomIter, RandomIter>
    erange_dispatch(RandomIter first, RandomIter last,
                    const T &value, random_access_iterator_tag,
                    Compared comp) {
        auto len = last - first;
        auto half = len;
        RandomIter middle, left, right;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (comp(*middle, value)) {
                first = middle + 1;
                len = len - half - 1;
            }else if (comp(value, *middle)) {
                len = half;
            }else {
                left = mystl::lower_bound(first, middle, value);
                right = mystl::upper_bound(++middle, first + len, value);
                return mystl::pair<RandomIter, RandomIter>(left, right);
            }
        }
        return mystl::pair<RandomIter, RandomIter>(last, last);
    }

    template <typename ForwardIter, typename T, typename Compared>
    mystl::pair<ForwardIter, ForwardIter>
    equal_range(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
        return mystl::erange_dispatch(first, last, value, iterator_category(first), comp);
    }

    /*****************************************************************************************/
    // generate
    // 将函数对象 gen 的运算结果对[first, last)内的每个元素赋值
    /*****************************************************************************************/
    template <typename ForwardIter, typename Generator>
    void generate(ForwardIter first, ForwardIter last, Generator gen) {
        for (; first != last; ++first) {
            *first = gen();
        }
    }

    /*****************************************************************************************/
    // generate_n
    // 用函数对象 gen 连续对 n 个元素赋值
    /*****************************************************************************************/
    template <typename ForwardIter, typename Size, typename Generator>
    void generate_n(ForwardIter first, Size n, Generator gen) {
        for (; n > 0; --n, ++first) {
            *first = gen();
        }
    }

    /*****************************************************************************************/
    // includes
    // 判断序列一S1 是否包含序列二S2
    // 应用于有序区间
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    bool includes(InputIter1 first1, InputIter1 last1,
                  InputIter2 first2, InputIter2 last2) {
        while (first1 != last1 && first2 != last2) {  // 两个区间都尚未走完
            if (*first2 < *first1) {  // 序列二的元素小于序列一的元素
                return false;
            }else if (*first1 < *first2) {
                ++first1;
            }else {  // *first1 == *first2
                ++first1;
                ++first2;
            }
        }

        return first2 == last2;
    }

    template <typename InputIter1, typename InputIter2, typename Compared>
    bool includes(InputIter1 first1, InputIter1 last1,
                  InputIter2 first2, InputIter2 last2,
                  Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first2, *first1)) {
                return false;
            }else if (comp(*first1, *first2)) {
                ++first1;
            }else {
                ++first1;
                ++first2;
            }
        }

        return first2 == last2;
    }

    /*****************************************************************************************/
    // is_heap
    // 检查[first, last)内的元素是否为一个堆，如果是，则返回 true
    /*****************************************************************************************/
    template <typename RandomIter>
    bool is_heap(RandomIter first, RandomIter last) {
        auto n = mystl::distance(first, last);  // 这里可以用 last - first
        auto parent = 0;
        for (auto child = 1; child < n; ++child) {
            if (first[parent] < first[child]) {
                return false;
            }
            if ((child & 1) == 0) {  // 偶数
                ++parent;
            }
        }
        return true;
    }

    template <typename RandomIter, typename Compared>
    bool is_heap(RandomIter first, RandomIter last, Compared comp) {
        auto n = mystl::distance(first, last);  // 这里可以用 last - first
        auto parent = 0;
        for (auto child = 1; child < n; ++child) {
            if (comp(first[parent], first[child])) {
                return false;
            }
            if ((child & 1) == 0) {  // 偶数
                ++parent;
            }
        }
        return true;
    }
    /*****************************************************************************************/
    // is_sorted
    // 检查[first, last)内的元素是否升序，如果是升序，则返回 true
    /*****************************************************************************************/
    template <typename ForwardIter>
    bool is_sorted(ForwardIter first, ForwardIter last) {
        if (first == last) { return true; }
        auto next = first;
        ++next;
        for (; next != last; first = next, ++next) {
            if (*next < *first) {
                return false;
            }
        }
        return true;
    }

    template <typename ForwardIter, typename Compared>
    bool is_sorted(ForwardIter first, ForwardIter last) {
        if (first == last) { return true; }
        auto next = first;
        ++next;
        for (; next != last; first = next, ++next) {
            if (comp(*next, *first)) {
                return false;
            }
        }
        return true;
    }

    /*****************************************************************************************/
    // median
    // 找出三个值的中间值
    /*****************************************************************************************/
    template <typename T>
    const T &median(const T &left, const T &mid, const T &right) {
        if (left < mid)
            if (mid < right)        // left < mid < right
                return mid;
            else if (left < right)  // left < right <= mid
                return right;
            else                    // right <= left < mid
                return left;
        else if (left < right)      // mid <= left < right
            return left;
        else if (mid < right)       // mid < right <= left
            return right;
        else                        // right <= mid <= left
            return mid;
    }

    template <typename T, typename Compared>
    const T &median(const T &left, const T &mid, const T &right, Compared comp) {
        if (comp(left, mid))
            if (comp(mid, right))
                return mid;
            else if (comp(left, right))
                return right;
            else
                return left;
        else if (comp(left, right))
            return left;
        else if (comp(mid, right))
            return right;
        else
            return mid;
    }

    /*****************************************************************************************/
    // max_element
    // 返回一个迭代器，指向序列中最大的元素
    /*****************************************************************************************/
    template <typename ForwardIter>
    ForwardIter max_element(ForwardIter first, ForwardIter last) {
        if (first == last)
            return first;
        auto result = first;
        while (++first != last) {
            if (*result < *first) {
                result = first;
            }
        }
        return result;
    }

    template <typename ForwardIter, typename Compared>
    ForwardIter max_element(ForwardIter first, ForwardIter last, Compared comp) {
        if (first == last)
            return first;
        auto result = first;
        while (++first != last) {
            if (comp(*result, *first)) {
                result = first;
            }
        }
        return result;
    }

    /*****************************************************************************************/
    // min_element
    // 返回一个迭代器，指向序列中最小的元素
    /*****************************************************************************************/
    template <typename ForwardIter>
    ForwardIter min_element(ForwardIter first, ForwardIter last) {
        if (first == last) {
            return first;
        }
        auto result = first;
        while (++first != last) {
            if (*first < *result) {
                result = first;
            }
        }
        return result;
    }

    template <typename ForwardIter, typename Compared>
    ForwardIter min_element(ForwardIter first, ForwardIter last, Compared comp) {
        if (first == last) {
            return first;
        }
        auto result = first;
        while (++first != last) {
            if (comp(*first, *result)) {
                result = first;
            }
        }
        return result;
    }

    /*****************************************************************************************/
    // swap_ranges
    // 将[first1, last1)从 first2 开始，交换相同个数元素
    // 交换的区间长度必须相同，两个序列不能互相重叠，返回一个迭代器指向序列二最后一个被交换元素的下一位置
    /*****************************************************************************************/
    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1,
                             ForwardIter2 first2) {
        for (; first1 != last1; ++first1, ++first2) {
            mystl::iter_swap(first1, first2);
        }
        return first2;
    }

    /*****************************************************************************************/
    // transform
    // 第一个版本以函数对象 unary_op 作用于[first, last)中的每个元素并将结果保存至 result 中
    // 第二个版本以函数对象 binary_op 作用于两个序列[first1, last1)、[first2, last2)的相同位置
    // 如果第二个序列长度小于第一个，则执行结果不可预测
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename UnaryOperation>
    OutputIter transform(InputIter first, InputIter last,
                         OutputIter result, UnaryOperation unary_op) {
       for (; first != last; ++first, ++result) {
           *result = unary_op(*first);
       }
       return result;
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename BinaryOperation>
    OutputIter transform(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, OutputIter result,
                         BinaryOperation binary_op) {
        for (; first1 != last1; ++first1, ++first2, ++result) {
            *result = binary_op(*first1, *first2);
        }
        return result;
    }

    /*****************************************************************************************/
    // remove_copy
    // 移除区间内与指定 value 相等的元素，并将结果复制到以 result 标示起始位置的容器上
    // 并不真正删除元素, 原容器不会有任何改变，除非result也指向原容器
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename T>
    OutputIter remove_copy(InputIter first, InputIter last,
                           OutputIter result, const T& value) {
        for (; first != last; ++first) {
            if (*first != value) {
                *result++ = *first;
            }
        }
        return result;
    }

    /*****************************************************************************************/
    // remove
    // 移除所有与指定 value 相等的元素
    // [0, 1, 0, 2, 0, 3, 0, 4], 移除0 -> [1, 2, 3, 4, 0, 3, 0, 4]
    // 并不从容器中删除这些元素，所以 remove 和 remove_if 不适用于 array
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    ForwardIter remove(ForwardIter first, ForwardIter last, const T &value) {
        first = mystl::find(first, last, value);  // 利用循序查找法找出第一个相等元素
        auto next = first;  // 用next标识
        // 利用remove_copy()允许新旧容器重叠的性质，进行移除操作
        return first == last ? first : mystl::remove_copy(++next, last, first, value);
    }

    /*****************************************************************************************/
    // remove_copy_if
    // 移除区间内所有令一元操作 unary_pred 为 true 的元素，并将结果复制到以 result 为起始位置的容器上
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename UnaryPredicate>
    OutputIter remove_copy_if(InputIter first, InputIter last,
                              OutputIter result, UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (!unary_pred(*first)) {
                *result = *first;
                ++result;
            }
        }
        return result;
    }

    /*****************************************************************************************/
    // remove_if
    // 移除区间内所有令一元操作 unary_pred 为 true 的元素
    /*****************************************************************************************/
    template <typename ForwardIter, typename UnaryPredicate>
    ForwardIter remove_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred) {
        first = mystl::find_if(first, last, unary_pred);  // 利用 find_if 找出第一个匹配的地方
        auto next = first;
        return first == last ? first : mystl::remove_copy_if(++next, last, first, unary_pred);
    }

    /*****************************************************************************************/
    // replace
    // 将区间内所有的 old_value 都以 new_value 替代
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    void replace(ForwardIter first, ForwardIter last,
                 const T &old_value, const T &new_value) {
        for (; first != last; ++first) {
            if (*first == old_value) {
                *first = new_value;
            }
        }
    }

    /*****************************************************************************************/
    // replace_copy
    // 行为与 replace 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename T>
    OutputIter replace_copy(InputIter first, InputIter last,
                 OutputIter result, const T& old_value, const T& new_value) {
        for (; first != last; ++first, ++result)
        {
            *result = *first == old_value ? new_value : *first;
        }
        return result;
    }

    /*****************************************************************************************/
    // replace_if
    // 将区间内所有令一元操作 unary_pred 为 true 的元素都用 new_value 替代
    /*****************************************************************************************/
    template <typename ForwardIter, typename UnaryPredicate, typename T>
    void replace_if(ForwardIter first, ForwardIter last,
                    UnaryPredicate unary_pred, const T& new_value) {
        for (; first != last; ++first) {
            if (unary_pred(*first)) {
                *first = new_value;
            }
        }
    }

    /*****************************************************************************************/
    // replace_copy_if
    // 行为与 replace_if 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter,
            typename UnaryPredicate, typename T>
    OutputIter replace_copy_if(InputIter first, InputIter last,
                               OutputIter result, UnaryPredicate unary_pred,
                               const T& new_value) {
        for (; first != last; ++first, ++result) {
            *result = unary_pred(*first) ? new_value : *first;
        }

        return result;
    }

    /*****************************************************************************************/
    // reverse
    // 将[first, last)区间内的元素反转
    /*****************************************************************************************/
    // bidirectional_iterator_tag
    template <typename BidirectionalIter>
    void reverse_dispatch(BidirectionalIter first, BidirectionalIter last,
                          bidirectional_iterator_tag) {
        while (true) {
            if (first == last || first == --last) {
                return ;
            }
            mystl::iter_swap(first++, last);
        }
    }
    // random_access_iterator_tag
    template <typename RandomIter>
    void reverse_dispatch(RandomIter first, RandomIter last,
                          random_access_iterator_tag) {
        while (first < last) {  // 只有randomiter 才能做到判断 <
            mystl::iter_swap(first++, --last);
        }
    }

    template <typename BidirectionalIter>
    void reverse(BidirectionalIter first, BidirectionalIter last) {
        mystl::reverse_dispatch(first, last, iterator_category(first));
    }

    /*****************************************************************************************/
    // reverse_copy
    // 行为与 reverse 类似，不同的是将结果复制到 result 所指容器中
    /*****************************************************************************************/
    template <typename BidirectionalIter, typename OutputIter>
    OutputIter reverse_copy(BidirectionalIter first, BidirectionalIter last,
                            OutputIter result) {
        while (first != last) {
            --last;
            *result = *last;
            ++result;
        }
        return result;
    }

    /*****************************************************************************************/
    // random_shuffle
    // 将[first, last)内的元素次序随机重排
    // 重载版本使用一个产生随机数的函数对象 rand
    /*****************************************************************************************/
    template <typename RandomIter>
    void random_shuffle(RandomIter first, RandomIter last) {
        if (first == last) {
            return ;
        }
        srand((unsigned) time(0));
        for (auto i = first + 1; i != last; ++i) {
            mystl::iter_swap(i, first + (rand() % (i - first + 1)));
        }
    }

    template <typename RandomIter, typename RandomNumberGenerator>
    void random_shuffle(RandomIter first, RandomIter last,
                        RandomNumberGenerator &rand) {
        if (first == last) {
            return ;
        }

        auto len = mystl::distance(first, last);
        for (auto i = first + 1; i != last; ++i) {
            mystl::iter_swap(i, first + (rand(i - first + 1) % len));
        }
    }

    /*****************************************************************************************/
    // rotate
    // 将[first, middle)内的元素和 [middle, last)内的元素互换，可以交换两个长度不同的区间
    // 返回first所指元素移动后的位置
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter>
    ForwardIter rotate_dispatch(ForwardIter first, ForwardIter middle,
                                ForwardIter last, forward_iterator_tag) {
        auto first2 = middle;
        do {
            mystl::swap(*first++, *first2++);
            if (first == middle) {
                middle = first2;
            }
        }while (first2 != last);  // 后半段移到前面

        auto new_middle = first;  // 迭代器返回的位置
        first2 = middle;
        while (first2 != last) {  // 调整剩余元素
            mystl::swap(*first++, *first2++);
            if (first == middle) {
                middle = first2;
            }else if (first2 == last) {
                first2 = middle;
            }
        }
        return new_middle;
    }
    // 另一种实现方式：以短端为依据，对应元素逐一对调
    // template <typename ForwardIter>
    // ForwardIter rotate_dispatch(ForwardIter first, ForwardIter middle,
    //                             ForwardIter last, forward_iterator_tag) {
    //     for (auto i = middle; ;) {
    //         mystl::iter_swap(first, i);  //前段、后段元素一一交换
    //         ++first;  // 双双前进1
    //         ++i;
    //         // 以下判断是前段先结束还是后段先结束
    //         if (first == middle) {  // 前段先结束
    //             if (i == last) return ;  // 如果后段也结束, 完成退出
    //             middle = i;  // 调整，对新的前后段再做交换
    //         }else if (i == last) {  // 后段先结束
    //             i = middle;  // 调整，对新的前后段再做交换
    //         }
    //     }
    // }

    // bidirectional_iterator_tag
    template <typename BidirectionalIter>
    BidirectionalIter rotate_dispatch(BidirectionalIter first, BidirectionalIter middle,
                                      BidirectionalIter last, bidirectional_iterator_tag) {
        mystl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
        mystl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
        // 为什么不直接调用reverse_dispatch(first, last, bidirectional_iterator_tag());
        while (first != middle && middle != last) {
            mystl::swap(*first++, *--last);
        }

        if (first == middle) {
            mystl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
            return last;
        }else {
            mystl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
            return first;
        }

    }

    // 求最大公因子，辗转相除法
    template <typename EuclideanRingElement>
    EuclideanRingElement rgcd(EuclideanRingElement m, EuclideanRingElement n) {
        while (n != 0) {
            auto t = m % n;
            m = n;
            n = t;
        }
        return m;
    }

    // random_access_iterator_tag
    template <typename RandomIter>
    RandomIter rotate_dispatch(RandomIter first, RandomIter middle,
                               RandomIter last, random_access_iterator_tag) {
        // 因为是 random access iterator，我们可以确定每个元素的位置
        auto n = last - first, l = middle - first, r = n - l;
        auto result = first + (last - middle);
        if (l == r) {  // 前后两端交换长度相同
            mystl::swap_ranges(first, middle, middle);
            return result;
        }
        auto cycle_times = rgcd(n, l);  // 求n和l的最大公因数
        // TODO: 不太理解
        // https://blog.csdn.net/fiempty/article/details/46347985?locationNum=9&fps=1
        for (auto i = 0; i < cycle_times; ++i) {
            auto tmp = *first;
            auto p = first;
            if (l < r) {
                for (auto j = 0; j < r / cycle_times; ++j) {
                    if (p > first + r) {
                        *p = *(p - r);
                        p -= r;
                    }
                    *p = *(p + l);
                    p += l;
                }
            }else {
                for (auto j = 0; j < l / cycle_times - 1; ++j) {
                    if (p < last - l) {
                        *p = *(p + l);
                        p += l;
                    }
                    *p = *(p - r);
                    p -= r;
                }
            }
            *p = tmp;
            ++first;
        }
        return result;
    }

    template <typename ForwardIter>
    ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last) {
        if (first == middle) {
            return last;
        }

        if (middle == last) {
            return first;
        }

        return mystl::rotate_dispatch(first, middle, last, iterator_category(first));
    }

    /*****************************************************************************************/
    // rotate_copy
    // 行为与 rotate 类似，不同的是将结果复制到 result 所指的容器中
    /*****************************************************************************************/
    template <typename ForwardIter, typename OutputIter>
    ForwardIter rotate_copy(ForwardIter first, ForwardIter middle,
                            ForwardIter last, OutputIter result) {
        // 先复制后半段，再复制前半段即可
        return mystl::copy(first, middle, mystl::copy(middle, last, result));
    }

    /*****************************************************************************************/
    // is_permutation
    // 判断[first1,last1)是否为[first2, last2)的排列组合
    /*****************************************************************************************/
    // 单纯的记录每个元素出现的个数进行比较
    template <typename ForwardIter1, typename ForwardIter2, typename BinaryPred>
    bool is_permytation_aux(ForwardIter1 first1, ForwardIter1 last1,
                            ForwardIter2 first2, ForwardIter2 last2,
                            BinaryPred pred) {
        constexpr bool is_ra_it = mystl::is_random_access_iterator<ForwardIter1>::value
                && mystl::is_random_access_iterator<ForwardIter2>::value;

        // if (is_ra_it) {  // 是random_access_iterator, 计算长度，不相等则返回
        //     auto len1 = last1 - first1;
        //     auto len2 = last2 - first2;
        //     if (len1 != len2) {
        //         return false;
        //     }
        // }

        // 先找出相同的前缀段
        for (; first1 != last1 && first2 != last2; ++first1, (void) ++first2) {
            if (!pred(*first1, *first2)) {
                break;
            }
        }

        if (is_ra_it) {
            if (first1 == last1) return true;
        }else {
            // 其余类型的迭代，只能单独计算距离
            auto len1 = mystl::distance(first1, last1);
            auto len2 = mystl::distance(first2, last2);
            if (len1 == 0 && len2 == 0) return true;
            if (len1 != len2) return false;
        }

        // 判断剩余部分
        for (auto i = first1; i != last1; ++i) {
            bool is_repeated = false;
            // 相同的元素, 令is_repeated = true， 跳过该次循环
            for (auto j = first1; j != i; ++j) {
                if (pred(*j, *i)) {
                    is_repeated = true;
                    break;
                }
            }
            if (!is_repeated) {
                // 计算 *i 在 [first2, last2) 的数目
                auto c2 = 0;
                for (auto j = first2; j != last2; ++j) {
                    if (pred(*i, *j)) ++c2;
                }
                if (c2 == 0) return false;

                // 计算 *i 在 [first1, last1) 的数目
                auto c1 = 1;
                auto j = i;
                for (++j; j != last1; ++j) {
                    if (pred(*i, *j)) ++c1;
                }

                if (c1 != c2) {
                    return false;
                }
            }
        }
        return true;
    }


    // 指定比较操作
    template <typename ForwardIter1, typename ForwardIter2, typename BinaryPred>
    bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2,
                        BinaryPred pred) {
        return is_permutation_aux(first1, last1, first2, last2, pred);
    }

    // 未指定比较操作，默认数据类型相同，使用仿函数，equal_to
    template <typename ForwardIter1, typename ForwardIter2>
    bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2) {
        typedef typename mystl::iterator_traits<ForwardIter1>::value_type v1;
        typedef typename mystl::iterator_traits<ForwardIter2>::value_type v2;
        static_assert(std::is_same<v1, v2>::value,
                "the type should be same in mystl::is_permutation");
        return is_permytation_aux(first1, last1, first2, last2, mystl::equal_to<v1>());
    }

    /*****************************************************************************************/
    // next_permutation
    // 取得[first, last)所标示序列的下一个排列组合，如果没有下一个排序组合，返回 false，否则返回 true
    // 首先，从最尾端开始往前寻找两个相邻元素，令第一元素为*i,第二元素为*ii,且满足*i<*ii.找到这样一组相邻元素后，
    // 再从最尾端开始往前检验，找出第一个大于*i的元素， 令为*j，将i，j元素对调，再将ii之后的所有元素颠倒排列。
    /*****************************************************************************************/
    template <typename BidirectionalIter>
    bool next_permutation(BidirectionalIter first, BidirectionalIter last) {
        auto i = last;
        if (first == last || first == --i) {  // 为空或只有一个元素
            return false;
        }
        for (;;) {
            auto ii = i;
            if (*--i < *ii) {   // 找到第一对小于关系的元素
                auto j = last;
                while (!(*i < *--j)) {}  // 找到第一个大于*i的元素
                mystl::iter_swap(i, j);       // 交换 i，j 所指元素
                mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转，包括ii
                return true;
            }

            if (i == first) {  // 数组逆序排列
                mystl::reverse(first, last);
                return false;
            }
        }
    }

    template <typename BidirectionalIter, typename Compared>
    bool next_permutation(BidirectionalIter first, BidirectionalIter last,
                          Compared comp) {
        auto i = last;
        if (first == last || first == --i) {  // 为空或只有一个元素
            return false;
        }
        for (;;) {
            auto ii = i;
            if (comp(*--i, *ii)) {   // 找到第一对小于关系的元素
                auto j = last;
                while (!(comp(*i, *--j))) {}  // 找到第一个大于*i的元素
                mystl::iter_swap(i, j);       // 交换 i，j 所指元素
                mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转，包括ii
                return true;
            }

            if (i == first) {  // 数组逆序排列
                mystl::reverse(first, last);
                return false;
            }
        }
    }

    /*****************************************************************************************/
    // prev_permutation
    // 取得[first, last)所标示序列的上一个排列组合，如果没有上一个排序组合，返回 false，否则返回 true
    // 首先，从最尾端开始往前寻找两个相邻元素，令第一元素为*i,第二元素为*ii,且满足*i > *ii.找到这样一组相邻元素后，
    // 再从最尾端开始往前检验，找出第一个小于*i的元素， 令为*j，将i，j元素对调，再将ii之后的所有元素颠倒排列。
    /*****************************************************************************************/
    template <typename BidirectionalIter>
    bool prev_permutation(BidirectionalIter first, BidirectionalIter last) {
        auto i = last;
        if (first == last || first == --i) {
            return false;
        }

        for (;;) {
            auto ii = i;
            if (*ii < *--i) {  // 找到第一对大于关系的相邻元素
                auto j = last;
                while (!(*--j < *i)) {}
                mystl::iter_swap(i, j);  // 交换i，j
                mystl::reverse(ii, last);  // 将 ii(包括ii)之后的所有元素反转
                return true;
            }

            if (i == first) {
                mystl::reverse(first, last);
                return false;
            }
        }
    }

    template <typename BidirectionalIter, typename Compared>
    bool prev_permutation(BidirectionalIter first, BidirectionalIter last,
                          Compared comp) {
        auto i = last;
        if (first == last || first == --i) {
            return false;
        }

        for (;;) {
            auto ii = i;
            if (comp(*ii, *--i)) {  // 找到第一对大于关系的相邻元素
                auto j = last;
                while (!(comp(*--j, *i))) {}
                mystl::iter_swap(i, j);  // 交换i，j
                mystl::reverse(ii, last);  // 将 ii(包括ii)之后的所有元素反转
                return true;
            }

            if (i == first) {
                mystl::reverse(first, last);
                return false;
            }
        }
    }

    /*****************************************************************************************/
    // merge
    // 将两个经过排序的集合 S1 和 S2 合并起来置于另一段空间，返回一个迭代器指向最后一个元素的下一位置
    // 应用于有序空间
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter merge(InputIter1 first1, InputIter1 last1,
                     InputIter2 first2, InputIter2 last2,
                     OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first2 < *first1) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
            }
            ++result;
        }
        // copy剩余元素
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    template <typename InputIter1, typename InputIter2, typename OutputIter,
            typename Compared>
    OutputIter merge(InputIter1 first1, InputIter1 last1,
                     InputIter2 first2, InputIter2 last2,
                     OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
            }
            ++result;
        }
        // copy剩余元素
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    /*****************************************************************************************/
    // inplace_merge
    // 把连接在一起的两个有序序列结合成单一序列并保持有序
    /*****************************************************************************************/
    // 没有缓冲区的情况下合并
    template <typename BidirectionalIter, typename Distance>
    void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                              BidirectionalIter last, Distance len1, Distance len2) {
        // 边界条件
        if (len1 == 0 || len2 == 0) {
            return ;
        }
        if (len1 + len2 == 2) {
            if (*middle < *first) {
                mystl::iter_swap(first, middle);
            }
            return ;
        }
        auto first_cut = first;
        auto second_cut = middle;
        Distance len11 = 0;
        Distance len22 = 0;
        if (len1 > len2) {  // 序列一较长，找到序列一的中点
            len11 = len1 >> 1;
            mystl::advance(first_cut, len11);
            second_cut = mystl::lower_bound(middle, last, *first_cut);
            len22 = mystl::distance(middle, second_cut);
        }else {  // 序列二较长，找到序列二的中点
            len22 = len2 >> 1;
            mystl::advance(second_cut, len22);
            first_cut = mystl::upper_bound(first, middle, *second_cut);
            len11 = mystl::distance(first, first_cut);
        }
        auto new_middle = mystl::rotate(first_cut, middle, second_cut);
        mystl::merge_without_buffer(first, first_cut, new_middle, len11, len22);
        mystl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22);
    }

    // 有缓冲区的条件下合并
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter1 merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
                                      BidirectionalIter2 first2, BidirectionalIter2 last2,
                                      BidirectionalIter1 result) {
        if (first1 == last1) {
            return mystl::copy_backward(first2, last2, result);
        }
        if (first2 == last2) {
            return mystl::copy_backward(first1, last1, result);
        }
        --last1;
        --last2;
        while (true) {
            if (*last2 < *last1) {
                *--result = *last1;
                if (first1 == last1)
                    return mystl::copy_backward(first2, ++last2, result);
                --last1;
            }else {
                *--result = *last2;
                if (first2 == last2)
                    return mystl::copy_backward(first1, ++last1, result);
                --last2;
            }
        }
    }

    // 利用缓存区进行旋转，如果缓冲区不足，还是调用通用的rotate函数
    template <typename BidirectionalIter1, typename BidirectionalIter2, typename Distance>
    BidirectionalIter1 rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle,
                                       BidirectionalIter1 last, Distance len1, Distance len2,
                                       BidirectionalIter2 buffer, Distance buffer_size) {
        BidirectionalIter2 buffer_end;
        if (len1 > len2 && len2 <= buffer_size) {
            buffer_end = mystl::copy(middle, last, buffer);
            mystl::copy_backward(first, middle, last);
            return mystl::copy(buffer, buffer_end, first);
        }else if (len1 <= buffer_size) {
            buffer_end = mystl::copy(first, middle, buffer);
            mystl::copy(middle, last, first);
            return mystl::copy_backward(buffer, buffer_end, last);
        }else {
            return mystl::rotate(first, middle, last);
        }

    }

    template <typename BidirectionalIter, typename Distance, typename Pointer>
    void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                        BidirectionalIter last, Distance len1, Distance len2,
                        Pointer buffer, Distance buffer_size) {
        // 区间长度足够放进缓冲区
        if (len1 <= len2 && len1 <= buffer_size) {
            Pointer buffer_end = mystl::copy(first, middle, buffer);
            mystl::merge(buffer, buffer_end, middle, last, first);
        }else if (len2 <= buffer_size) {
            Pointer buffer_end = mystl::copy(middle, last, buffer);
            mystl::merge_backward(first, middle, buffer, buffer_end, last);
        }else {
            // 区间长度太长，分割递归处理
            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;
            if (len1 > len2) {
                len11 = len1 >> 1;
                mystl::advance(first_cut, len11);
                second_cut = mystl::lower_bound(middle, last, *first_cut);
                len22 = mystl::distance(middle, second_cut);
            }else {
                len22 = len2 >> 1;
                mystl::advance(second_cut, len22);
                first_cut = mystl::upper_bound(first, middle, *second_cut);
                len11 = mystl::distance(first, first_cut);
            }
            // 通过旋转之后，整个数组就分为前后两部分，后面一部分全都大于第一部分，因此就可以分开处理
            auto new_middle = mystl::rotate_adaptive(first_cut, middle, second_cut,
                                                     len1 - len11, len22, buffer, buffer_size);
            mystl::merge_adaptive(first, first_cut, new_middle, len11, len22,
                                  buffer, buffer_size);
            mystl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                                  len2 - len22, buffer, buffer_size);
        }
    }

    template <typename BidirectionalIter, typename T>
    void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                           BidirectionalIter last, T*) {
        auto len1 = mystl::distance(first, middle);
        auto len2 = mystl::distance(middle, last);
        temporary_buffer<BidirectionalIter, T> buf(first, last);
        if (!buf.begin()) {
            mystl::merge_without_buffer(first, middle, last, len1, len2);
        }else {
            mystl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size());
        }
    }

    template <typename BidirectionalIter>
    void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                       BidirectionalIter last) {
        if (first == middle || middle == last) {
            return ;
        }
        mystl::inplace_merge_aux(first, middle, last, value_type(first));
    }

    // 没有缓冲区的情况下合并
    template <typename BidirectionalIter, typename Distance, typename Compared>
    void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                              BidirectionalIter last, Distance len1, Distance len2,
                              Compared comp) {
        // 边界条件
        if (len1 == 0 || len2 == 0) {
            return ;
        }
        if (len1 + len2 == 2) {
            if (comp(*middle, *first)) {
                mystl::iter_swap(first, middle);
            }
            return ;
        }
        auto first_cut = first;
        auto second_cut = middle;
        Distance len11 = 0;
        Distance len22 = 0;
        if (len1 > len2) {  // 序列一较长，找到序列一的中点
            len11 = len1 >> 1;
            mystl::advance(first_cut, len11);
            second_cut = mystl::lower_bound(middle, last, *first_cut);
            len22 = mystl::distance(middle, second_cut);
        }else {  // 序列二较长，找到序列二的中点
            len22 = len2 >> 1;
            mystl::advance(second_cut, len22);
            first_cut = mystl::upper_bound(first, middle, *second_cut);
            len11 = mystl::distance(first, first_cut);
        }
        auto new_middle = mystl::rotate(first_cut, middle, second_cut);
        mystl::merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
        mystl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
    }

    // 有缓冲区的条件下合并
    template <typename BidirectionalIter1, typename BidirectionalIter2, typename Compared>
    BidirectionalIter1 merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
                                      BidirectionalIter2 first2, BidirectionalIter2 last2,
                                      BidirectionalIter1 result, Compared comp) {
        if (first1 == last1) {
            return mystl::copy_backward(first2, last2, result);
        }
        if (first2 == last2) {
            return mystl::copy_backward(first1, last1, result);
        }
        --last1;
        --last2;
        while (true) {
            if (comp(*last2, *last1)) {
                *--result = *last1;
                if (first1 == last1)
                    return mystl::copy_backward(first2, ++last2, result);
                --last1;
            }else {
                *--result = *last2;
                if (first2 == last2)
                    return mystl::copy_backward(first1, ++last1, result);
                --last2;
            }
        }
    }

    template <typename BidirectionalIter, typename Distance,
            typename Pointer, typename Compared>
    void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                        BidirectionalIter last, Distance len1, Distance len2,
                        Pointer buffer, Distance buffer_size, Compared comp) {
        // 区间长度足够放进缓冲区
        if (len1 <= len2 && len1 <= buffer_size) {
            Pointer buffer_end = mystl::copy(first, middle, buffer);
            mystl::merge(buffer, buffer_end, middle, last, first, comp);
        }else if (len2 <= buffer_size) {
            Pointer buffer_end = mystl::copy(middle, last, buffer);
            mystl::merge_backward(first, middle, buffer, buffer_end, last, comp);
        }else {
            // 区间长度太长，分割递归处理
            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;
            if (len1 > len2) {
                len11 = len1 >> 1;
                mystl::advance(first_cut, len11);
                second_cut = mystl::lower_bound(middle, last, *first_cut, comp);
                len22 = mystl::distance(middle, second_cut);
            }else {
                len22 = len2 >> 1;
                mystl::advance(second_cut, len22);
                first_cut = mystl::upper_bound(first, middle, *second_cut, comp);
                len11 = mystl::distance(first, first_cut);
            }
            // 通过旋转之后，整个数组就分为前后两部分，后面一部分全都大于第一部分，因此就可以分开处理
            auto new_middle = mystl::rotate_adaptive(first_cut, middle, second_cut,
                                                     len1 - len11, len22, buffer, buffer_size);
            mystl::merge_adaptive(first, first_cut, new_middle, len11, len22,
                                  buffer, buffer_size, comp);
            mystl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                                  len2 - len22, buffer, buffer_size, comp);
        }
    }

    template <typename BidirectionalIter, typename T, typename Compared>
    void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                           BidirectionalIter last, T*, Compared comp) {
        auto len1 = mystl::distance(first, middle);
        auto len2 = mystl::distance(middle, last);
        temporary_buffer<BidirectionalIter, T> buf(first, last);
        if (!buf.begin()) {
            mystl::merge_without_buffer(first, middle, last, len1, len2,comp);
        }else {
            mystl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size(), comp);
        }
    }

    template <typename BidirectionalIter, typename Compared>
    void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                       BidirectionalIter last, Compared comp) {
        if (first == middle || middle == last) {
            return ;
        }
        mystl::inplace_merge_aux(first, middle, last, value_type(first), comp);
    }

    /*****************************************************************************************/
    // partial_sort
    // 对整个序列做部分排序，保证较小的 N 个元素以递增顺序置于[first, first + N)中
    /*****************************************************************************************/
    template <typename RandomIter>
    void partial_sort(RandomIter first, RandomIter middle, RandomIter last) {
        mystl::make_heap(first, middle);
        for (auto i = middle; i < last; ++i) {
            if (*i < *first) {
                mystl::pop_heap_aux(first, middle, i, *i, distance_type(first));
            }
        }
        mystl::sort_heap(first, middle);
    }

    template <typename RandomIter, typename Compared>
    void partial_sort(RandomIter first, RandomIter middle,
                      RandomIter last, Compared comp) {
        mystl::make_heap(first, middle, comp);
        for (auto i = middle; i < last; ++i) {
            if (comp(*i, *first)) {
                mystl::pop_heap_aux(first, middle, i, *i, distance_type(first), comp);
            }
        }
        mystl::sort_heap(first, middle, comp);
    }

    /*****************************************************************************************/
    // partial_sort_copy
    // 行为与 partial_sort 类似，不同的是把排序结果复制到 result 容器中
    /*****************************************************************************************/
    template <typename InputIter, typename RandomIter, typename Distance>
    RandomIter psort_copy_aux(InputIter first, InputIter last,
                              RandomIter result_first, RandomIter result_last,
                              Distance*) {
        if (result_first == result_last) { return result_last; }
        auto result_iter = result_first;
        // 单纯的复制过去
        while (first != last && result_iter != result_last) {
            *result_iter = *first;
            ++result_iter;
            ++first;
        }
        mystl::make_heap(result_first, result_iter);
        while (first != last) {
            if (*first < *result_first) {
                mystl::adjust_heap(result_first, static_cast<Distance>(0),
                                   result_iter - result_first, *first);
            }
            ++first;
        }
        mystl::sort_heap(result_first, result_iter);
        return result_iter;
    }

    template <typename InputIter, typename RandomIter>
    RandomIter partial_sort_copy(InputIter first, InputIter last,
                      RandomIter result_first, RandomIter result_last) {
        return mystl::psort_copy_aux(first, last, result_first, result_last,
                                     distance_type(result_first));
    }

    template <typename InputIter, typename RandomIter,
            typename Distance, typename Compared>
    RandomIter psort_copy_aux(InputIter first, InputIter last,
                              RandomIter result_first, RandomIter result_last,
                              Distance*, Compared comp) {
        if (result_first == result_last) { return result_last; }
        auto result_iter = result_first;
        // 单纯的复制过去
        while (first != last && result_iter != result_last) {
            *result_iter = *first;
            ++result_iter;
            ++first;
        }
        mystl::make_heap(result_first, result_iter, comp);
        while (first != last) {
            if (comp(*first, *result_first)) {
                mystl::adjust_heap(result_first, static_cast<Distance>(0),
                                   result_iter - result_first, *first, comp);
            }
            ++first;
        }
        mystl::sort_heap(result_first, result_iter, comp);
        return result_iter;
    }

    template <typename InputIter, typename RandomIter, typename Compared>
    RandomIter partial_sort_copy(InputIter first, InputIter last,
                                 RandomIter result_first, RandomIter result_last,
                                 Compared comp) {
        return mystl::psort_copy_aux(first, last, result_first, result_last,
                                     distance_type(result_first), comp);
    }

    /*****************************************************************************************/
    // partition
    // 对区间内的元素重排，被一元条件运算判定为 true 的元素会放到区间的前段
    // 该函数不保证元素的原始相对位置
    /*****************************************************************************************/
    template <typename BidirectionalIter, typename UnaryPredicate>
    BidirectionalIter partition(BidirectionalIter first, BidirectionalIter last,
                                UnaryPredicate unary_pred) {
        while (true) {
            while (first != last && unary_pred(*first)) {
                ++first;  // 符合条件，移动first
            }
            if (first == last) {
                break;  // 调整结束，跳出
            }
            --last;
            while (first != last ** !unary_pred(*last)) {
                --last;  // 不符合条件，移动last
            }
            if (first == last) {
                break;  // 调整结束，跳出
            }

            mystl::iter_swap(first, last);  // 对调头尾指针所指元素
            ++first;
        }
        return first;
    }

    /*****************************************************************************************/
    // partition_copy
    // 行为与 partition 类似，不同的是，将被一元操作符判定为 true 的放到 result_true 的输出区间
    // 其余放到 result_false 的输出区间，并返回一个 mystl::pair 指向这两个区间的尾部
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter1,
            typename OutputIter2, typename UnaryPredicate>
    mystl::pair<OutputIter1, OutputIter2>
    partition_copy(InputIter first, InputIter last,
                   OutputIter1 result_true, OutputIter2 result_false,
                   UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (unary_pred(*first)) {
                *result_true++ = *first;
            }else {
                *result_false++ = *first;
            }
        }
        return mystl::pair<OutputIter1, OutputIter2>(result_true, result_false);
    }

    /*****************************************************************************************/
    // sort
    // 将[first, last)内的元素以递增的方式排序
    // 所有的关系型容器都拥有自动排序的功能，stack，queue，priority-queue不允许用户自定义排序
    // 剩下的vector、deque和list，前两者适用sort算法，list的迭代器为bidirectionalIterators,不适用sort
    /*****************************************************************************************/
    constexpr static size_t kSmallSectionSize = 128;  // 小型区间的大小，在这个大小内采用插入排序

    // 用来控制分支恶化的情况
    // 找出 2 ^ k <= n 的最大K值
    template <typename Size>
    Size slg2(Size n) {
        Size k = 0;
        for (; n > 1; n >>= 1)
            ++k;
        return k;
    }

    // 分割函数 unchecked_partition
    template <typename RandomIter, typename T>
    RandomIter unchecked_partition(RandomIter first, RandomIter last, const T& pivot) {
        while (true) {
            while (*first < pivot) {
                ++first;
            }
            --last;
            while (pivot < last) {
                --last;
            }
            if (!(first < last)) {
                return first;
            }
            mystl::iter_swap(first, last);
            ++first;
        }
    }

    // 内省式排序，先进行 quick sort，当分割行为有恶化倾向时，改用 heap sort
    // intro_sort: 最坏情况下为 O(NlogN)
    template <typename RandomIter, typename Size>
    void intro_sort(RandomIter first, RandomIter last, Size depth_limit) {
        while (static_cast<size_t>(last - first) > kSmallSectionSize) {
            if (depth_limit == 0) {  // 到达最大分割深度限制
                mystl::partial_sort(first, last, last);  // 改用 heap_sort
                return;
            }
            --depth_limit;
            // 三点中值
            auto mid = mystl::median(*(first), *(first + (last - first) / 2), *(last - 1));
            auto cut = mystl::unchecked_partition(first, last, mid);
            mystl::intro_sort(cut, last, depth_limit);  // 对右半段进行递归调用
            last = cut;  // 接着对左半段进行处理
        }
    }

    // 插入排序辅助函数 unchecked_linear_insert
    // 省下了一个判断操作
    template <typename RandomIter, typename T>
    void unchecked_linear_insert(RandomIter last, const T& value) {
        auto next = last;
        --next;
        while (value < *next) {  // 存在逆转对
            *last = *next;  // 调整
            last = next;  // 左移，继续判断
            --next;
        }
        *last = value;

    }

    // 插入排序函数 unchecked_insertion_sort
    template <typename RandomIter>
    void unchecked_insertion_sort(RandomIter first, RandomIter last) {
        for (auto i = first; i != last; ++i) {
            mystl::unchecked_linear_insert(i, *i);
        }
    }

    // 插入排序 insertion_sort: O(N²)
    template <typename RandomIter>
    void insertion_sort(RandomIter first, RandomIter last) {
        if (first == last) { return; }
        for (auto i = first + 1; i != last; ++i) {
            auto value = *i;
            if (value < *first) {  // 尾部元素比头部元素还小（头部必为最小元素）
                mystl::copy_backward(first, i, i + 1);  // 将整个区间向右移一个位置
                *first = value;  // 令头元素等于原先的尾元素值
            }else {  // 尾部元素不比头部元素还小
                mystl::unchecked_linear_insert(i, value);
            }
        }
    }

    // 最终插入排序函数 final_insertion_sort
    template <typename RandomIter>
    void final_insertion_sort(RandomIter first, RandomIter last) {
        if (static_cast<size_t>(last - first) > kSmallSectionSize) {
            mystl::insertion_sort(first, first + kSmallSectionSize);
            mystl::unchecked_insertion_sort(first + kSmallSectionSize, last);
        }else {
            mystl::insertion_sort(first, last);
        }
    }

    template <typename RandomIter>
    void sort(RandomIter first, RandomIter last) {
        if (first != last) {
            // 内省式排序，将区间分为一个个小区间，然后对整体进行插入排序
            mystl::intro_sort(first, last, slg2(last - first) * 2);
            mystl::final_insertion_sort(first, last);
        }
    }

    // 分割函数 unchecked_partition
    template <typename RandomIter, typename T, typename Compared>
    RandomIter unchecked_partition(RandomIter first, RandomIter last,
                                   const T& pivot, Compared comp) {
        while (true) {
            while (comp(*first, pivot)) {
                ++first;
            }
            --last;
            while (comp(pivot, *last)) {
                --last;
            }
            if (!(first < last)) {
                return first;
            }
            mystl::iter_swap(first, last);
            ++first;
        }
    }

    // 内省式排序，先进行 quick sort，当分割行为有恶化倾向时，改用 heap sort
    template <typename RandomIter, typename Size, typename Compared>
    void intro_sort(RandomIter first, RandomIter last,
                    Size depth_limit, Compared comp) {
        while (static_cast<size_t>(last - first) > kSmallSectionSize) {
            if (depth_limit == 0) {
                mystl::partial_sort(first, last, last, comp);  // 改用 heap_sort
                return;
            }
            --depth_limit;
            auto mid = mystl::median(*(first), *(first + (last - first) / 2), *(last - 1));
            auto cut = mystl::unchecked_partition(first, last, mid, comp);
            mystl::intro_sort(cut, last, depth_limit, comp);
            last = cut;
        }
    }

    // 插入排序辅助函数 unchecked_linear_insert
    template <typename RandomIter, typename T, typename Compared>
    void unchecked_linear_insert(RandomIter last, const T& value, Compared comp) {
        auto next = last;
        --next;
        while (comp(value, *next)) {  // 从尾部开始寻找第一个可插入位置
            *last = *next;
            last = next;
            --next;
        }
        *last = value;
    }

    // 插入排序函数 unchecked_insertion_sort
    template <typename RandomIter, typename Compared>
    void unchecked_insertion_sort(RandomIter first, RandomIter last,
                                  Compared comp) {
        for (auto i = first; i != last; ++i) {
            mystl::unchecked_linear_insert(i, *i, comp);
        }
    }

    // 插入排序函数 insertion_sort
    template <typename RandomIter, typename Compared>
    void insertion_sort(RandomIter first, RandomIter last, Compared comp) {
        if (first == last) {
            return ;
        }
        for (auto i = first + 1; i != last; ++i) {
            auto value = *i;
            if (comp(value, *first)) {
                mystl::copy_backward(first, i, i + 1);
                *first = value;
            }else {
                mystl::unchecked_linear_insert(i, value, comp);
            }
        }
    }

    // 最终插入排序函数 final_insertion_sort
    template <typename RandomIter, typename Compared>
    void final_insertion_sort(RandomIter first, RandomIter last, Compared comp) {
        if (static_cast<size_t>(last - first) > kSmallSectionSize) {
            mystl::insertion_sort(first, first + kSmallSectionSize, comp);
            mystl::unchecked_insertion_sort(first + kSmallSectionSize, last, comp);
        }else {
            mystl::insertion_sort(first, last, comp);
        }
    }

    template <typename RandomIter, typename Compared>
    void sort(RandomIter first, RandomIter last, Compared comp) {
        if (first != last) {
            // 内省式排序，将区间分为一个个小区间，然后对整体进行插入排序
            mystl::intro_sort(first, last, slg2(last - first) * 2, comp);
            mystl::final_insertion_sort(first, last, comp);
        }
    }


    /*****************************************************************************************/
    // nth_element
    // 对序列重排，使得所有小于第 n 个元素的元素出现在它的前面，大于它的出现在它的后面
    /*****************************************************************************************/
    template <typename RandomIter>
    void nth_element(RandomIter first, RandomIter nth, RandomIter last) {
        if (nth == last) { return; }
        while (last - first > 3) {
            auto cut = mystl::unchecked_partition(first, last,
                            mystl::median(*first, *(first + (last - first) / 2), *(last - 1)));
            if (cut < nth) { // 如果 nth 位于右段
                first = cut;
            }else {
                last = cut;
            }
        }
        mystl::insertion_sort(first, last);
    }

    template <typename RandomIter, typename Compared>
    void nth_element(RandomIter first, RandomIter nth,
                     RandomIter last, Compared comp) {
        if (nth == last) { return; }
        while (last - first > 3) {
            auto cut = mystl::unchecked_partition(first, last,
                                                  mystl::median(*first, *(first + (last - first) / 2), *(last - 1)),
                                                  comp);
            if (cut < nth) { // 如果 nth 位于右段
                first = cut;
            }else {
                last = cut;
            }
        }
        mystl::insertion_sort(first, last, comp);
    }

    /*****************************************************************************************/
    // unique_copy
    // 从[first, last)中将元素复制到 result 上，序列必须有序，如果有重复的元素，只会复制一次
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename InputIter, typename ForwardIter>
    ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                     ForwardIter result, forward_iterator_tag) {
        *result = *first;
        while (++first != last) {
            if (*result != *first) {
                *++result = *first;
            }
        }
        return ++result;
    }
    // output_iterator_tag
    // 由于 output iterator 只能进行只写操作，所以不能有 *result != *first 这样的判断
    template <typename InputIter, typename OutputIter>
    OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                    OutputIter result, output_iterator_tag) {
        auto value = *first;
        *result = value;
        while (++first != last) {
            if (value != *first) {
                value = *first;
                *++result = value;
            }
        }
        return ++result;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter unique_copy(InputIter first, InputIter last, OutputIter result) {
        if (first == last) {
            return result;
        }
        return mystl::unique_copy_dispatch(first, last, result, iterator_category(result));
    }

    // forward_iterator_tag
    template <typename InputIter, typename ForwardIter, typename Compared>
    ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                     ForwardIter result, forward_iterator_tag,
                                     Compared comp) {
        *result = *first;
        while (++first != last) {
            if (!comp(*result, *first)) {
                *++result = *first;
            }
        }
        return ++result;
    }
    // output_iterator_tag
    // 由于 output iterator 只能进行只写操作，所以不能有 *result != *first 这样的判断
    template <typename InputIter, typename OutputIter, typename Compared>
    OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                    OutputIter result, output_iterator_tag,
                                    Compared comp) {
        auto value = *first;
        *result = value;
        while (++first != last) {
            if (!comp(value, *first)) {
                value = *first;
                *++result = value;
            }
        }
        return ++result;
    }

    template <typename InputIter, typename OutputIter, typename Compared>
    OutputIter unique_copy(InputIter first, InputIter last, OutputIter result, Compared comp) {
        if (first == last) {
            return result;
        }
        return mystl::unique_copy_dispatch(first, last, result, iterator_category(result), comp);
    }

    /*****************************************************************************************/
    // unique
    // 移除[first, last)内重复的元素，序列必须有序，和 remove 类似，它也不能真正的删除重复元素
    /*****************************************************************************************/
    template <typename ForwardIter>
    ForwardIter unique(ForwardIter first, ForwardIter last) {
        first = mystl::adjacent_find(first, last);
        return mystl::unique_copy(first, last, first);
    }

    template <typename ForwardIter, typename Compared>
    ForwardIter unique(ForwardIter first, ForwardIter last, Compared comp) {
        first = mystl::adjacent_find(first, last, comp);
        return mystl::unique_copy(first, last, first, comp);
    }

} // namespace mystl;

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif //TINYSTL_ALGO_H
