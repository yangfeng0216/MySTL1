#ifndef TINYSTL_ALGOBASE_H
#define TINYSTL_ALGOBASE_H
//  最大最小值，比较，内存拷贝，移动等算法
#include <cstring>

#include "iterator.h"
#include "util.h"

namespace mystl {

#ifdef max
    #pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
    #pragma message("#undefing marco min")
#undef min
#endif // min

    /*****************************************************************************************/
    // max
    // 取二者中的较大值，语义相等时保证返回第一个参数
    /*****************************************************************************************/
    template <typename T>
    const T& max(const T& lhs, const T& rhs) {
        return lhs < rhs ? rhs : lhs;
    }

    // 重载版本使用函数对象comp代替比较操作
    template <typename T, typename Compare>
    const T& max(const T& lhs, const T& rhs, Compare comp) {
        return comp(lhs, rhs) ? rhs : lhs;
    }

    /*****************************************************************************************/
    // min
    // 取二者中的较小值，语义相等时保证返回第一个参数
    /*****************************************************************************************/
    template <typename T>
    const T& min(const T& lhs, const T& rhs) {
        return lhs > rhs ? rhs : lhs;
    }

    template <typename T, typename Compare>
    const T& min(const T& lhs, const T& rhs, Compare comp) {
        return comp(rhs, lhs) ? rhs : lhs;
    }

    /*****************************************************************************************/
    // iter_swap
    // 将两个迭代器所指对象对调
    /*****************************************************************************************/
    template <typename FIter1, typename FIter2>
    void iter_swap(FIter1 lhs, FIter2 rhs) {
        mystl::swap(*lhs, *rhs);
    }

    /*****************************************************************************************/
    // copy
    // 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
    // 针对输入区间和输出区间可能出现重叠的情况，可能会导致错误
    // copy仅能做能改变现有迭代器所指元素，无法对空容器进行插入
    // 若想实现插入，应该搭配insert_iterator
    /*****************************************************************************************/
    // input_iterator_tag
    template <typename InputIter, typename OutputIter>
    OutputIter uncheckd_copy_cat(InputIter first, InputIter last, OutputIter result,
                                mystl::input_iterator_tag) {
        // 以迭代器的等同与否决定循环的执行次数，速度较慢
        for (; first != last; ++first, ++result) {
            *result = *first;
        }
        return result;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter uncheckd_copy_cat(InputIter first, InputIter last, OutputIter result,
                                 mystl::random_access_iterator_tag) {
        // 以n决定循环的执行次数，速度较快
        for (auto n = last - first; n > 0; --n, ++first, ++result) {
            *result = *first;
        }
        return result;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter uncheckd_copy(InputIter first, InputIter last, OutputIter result) {
        return uncheckd_copy_cat(first, last, result, iterator_category(first));
    }

    // 特化版本,判断迭代器指向类型有没有定义拷贝赋值运算符
    // 如果没有定义且类型一致直接通过memmove拷贝效率最高，否则就调用unchecked_copy_cat
    template <typename Tp, typename Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_copy_assignable<Up>::value, Up*>::type
    unchecked_copy(Tp *first, Tp *last, Up *result) {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0) {
            std::memmove(result, first, n * sizeof(Up));
        }
        return result + n;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter copy(InputIter first, InputIter last, OutputIter result) {
        return uncheckd_copy(first, last, result);
    }

    /*****************************************************************************************/
    // copy_backward
    // 将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内
    /*****************************************************************************************/
    // bidirectional_iterator_tag, 最低要求是双向迭代器
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward_cat(
            BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result, mystl::bidirectional_iterator_tag) {
        for (; first != last; --last, --result) {
            *result = *last;
        }
        return result;
    }

    // random_access_iterator_tag
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward_cat(
            BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result, mystl::random_access_iterator_tag) {
        for (auto n = last - first; n > 0; --n) {
            *--result = *--last;
        }
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                               BidirectionalIter2 result) {
        return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
    }

    // 特化版本
    template <typename Tp, typename Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_copy_assignable<Up>::value, Up*>::type
    unchecked_copy_backward(Tp *first, Tp *last, Up *result) {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0) {
            result -= n;
            std::memmove(result, first, n * sizeof(Up));
        }
        return result;
    }

    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                     BidirectionalIter2 result){
        return unchecked_copy_backward(first, last, result);
    }

    /*****************************************************************************************/
    // copy_if
    // 把[first, last)内满足一元操作 unary_pred 的元素拷贝到以 result 为起始的位置上
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename UnaryPredicate>
    OutputIter copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred) {
        for (; first != last; ++first) {
            if (unary_pred(*first)) {
                *result++ = *first;
            }
        }
        return result;
    }

    /*****************************************************************************************/
    // copy_n
    // 把 [first, first + n)区间上的元素拷贝到 [result, result + n)上
    // 返回一个 pair 分别指向拷贝结束的尾部
    /*****************************************************************************************/
    template <typename InputIter, typename Size, typename OutputIter>
    mystl::pair<InputIter, OutputIter> unchecked_copy_n(InputIter first, Size n, OutputIter result,
                                                        mystl::input_iterator_tag) {
        for (; n > 0; --n, ++first, ++result) {
            *result = *first;
        }

        return mystl::pair<InputIter, OutputIter>(first, result);
    }

    template <typename RandomIter, typename Size, typename OutputIter>
    mystl::pair<RandomIter, OutputIter> unchecked_copy_n(RandomIter first, Size n, OutputIter result,
                                                        mystl::random_access_iterator_tag) {
        auto last = first + n;
        return mystl::pair<RandomIter, OutputIter>(last, mystl::copy(first, last, result));
    }

    template <typename InputIter, typename Size, typename OutputIter>
    mystl::pair<InputIter, OutputIter> copy_n(InputIter first, Size n, OutputIter result) {
        return unchecked_copy_n(first, n, result, iterator_category(first));
    }

    /*****************************************************************************************/
    // move
    // 把 [first, last)区间内的元素移动到 [result, result + (last - first))内
    /*****************************************************************************************/
    // input_iterator_tag
    template <typename InputIter, typename OutputIter>
    OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
                                  mystl::input_iterator_tag) {
        for (; first != last; ++first, ++result) {
            *result = mystl::move(*first);
        }
        return result;
    }

    // random_access_iterator_tag
    template <typename InputIter, typename OutputIter>
    OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
                                  mystl::random_access_iterator_tag) {
        for (auto n = last - first; n > 0; --n, ++first, ++result) {
            *result = mystl::move(*first);
        }
        return result;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter unchecked_move(InputIter first, InputIter last, OutputIter result) {
        return unchecked_move_cat(first, last, result, iterator_category(first));
    }

    // 特化版本
    template <typename Tp, typename Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_move_assignable<Up>::value,
            Up*>::type
    unchecked_move(Tp *first, Tp *last, Up *result) {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0) {
            std::memmove(result, first, n * sizeof(Up));
        }
        return result + n;
    }

    template <typename InputIter, typename OutputIter>
    OutputIter move(InputIter first, InputIter last, OutputIter result) {
        return unchecked_move(first, last, result);
    }

    /*****************************************************************************************/
    // move_backward
    // 将 [first, last)区间内的元素移动到 [result - (last - first), result)内
    /*****************************************************************************************/
    // bidirectional_iterator_tag
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                                   BidirectionalIter2 result, mystl::bidirectional_iterator_tag) {
        while (first != last) {
            *--result = mystl::move(*--last);
        }
        return result;
    }

    // random_access_iterator_tag
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                                   BidirectionalIter2 result, mystl::random_access_iterator_tag) {
        for (auto n = last - first; n > 0; --n) {
            *--result = mystl::move(*--last);
        }
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                                   BidirectionalIter2 result) {
        return unchecked_move_backward_cat(first, last, result, iterator_category(first));
    }

    // 特化版本
    template <typename Tp, typename Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_move_assignable<Up>::value,
            Up*>::type
    unchecked_move_backword(Tp *first, Tp *last, Up *result) {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0) {
            result -= n;
            std::memmove(result, first, n * sizeof(Up));
        }
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    BidirectionalIter2 move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                     BidirectionalIter2 result) {
        return unchecked_move_backward(first, last, result);
    }

    /*****************************************************************************************/
    // equal
    // 比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
    // 序列二多出来的部分不予考虑，但如果序列一超出序列二，会造成不可预估的问题
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
        // 将序列一走过一遍，序列二亦步亦趋
        // 如果序列一的个数超过序列二，就会出错
        for (; first1 != last1; ++first1, ++first2) {
            if (*first1 != *first2) {
                return false;
            }
        }
        return true;
    }

    template <typename InputIter1, typename InputIter2, typename Compared>
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp) {
        for (; first1 != last1; ++first1, ++first2) {
            if (!comp(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }

    /*****************************************************************************************/
    // fill_n
    // 从 first 位置开始填充 n 个值
    // 由于每次迭代是一种覆写操作，所以如果n大于容器大小，会造成不可预期的结果，
    // 解决办法之一是利用insertiter()产生一个具有插入而非覆写的迭代器
    /*****************************************************************************************/
    template <typename OutputIter, typename Size, typename T>
    OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
        return first;
    }

    // 特化版本 通过判断数据类型的大小，如果是一个字节的调用memset，否则遍历赋值。
    template <typename Tp, typename Size, typename Up>
    typename std::enable_if<
            std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
            !std::is_same<Tp, bool>::value &&
            std::is_integral<Up>::value && sizeof(Up) == 1,
            Tp*>::type
    unchecked_fill_n(Tp *first, Size n, Up value) {
        if (n > 0) {
            std::memset(first, (unsigned char)value, (size_t)(n));
        }
        return first + n;
    }

    template <typename OutputIter, typename Size, typename T>
    OutputIter fill_n(OutputIter first, Size n, const T &value) {
        return unchecked_fill_n(first, n, value);
    }

    /*****************************************************************************************/
    // fill
    // 为 [first, last)区间内的所有元素填充新值
    /*****************************************************************************************/
    // forward_iterator_tag
    template <typename ForwardIter, typename T>
    void fill_cat(ForwardIter first, ForwardIter last, const T &value,
                  mystl::forward_iterator_tag) {
        for (; first != last; ++first) {
            *first = value;
        }
    }

    // random_access_iterator_tag
    template <typename ForwardIter, typename T>
    void fill_cat(ForwardIter first, ForwardIter last, const T &value,
                  mystl::random_access_iterator_tag) {
        mystl::fill_n(first, last - first, value);
    }

    template <typename ForwardIter, typename T>
    void fill(ForwardIter first, ForwardIter last, const T &value) {
        fill_cat(first, last, value, iterator_category(first));
    }

    /*****************************************************************************************/
    // lexicographical_compare
    // 以字典序排列对两个序列进行比较，当在某个位置发现第一组不相等元素时，有下列几种情况：
    // (1)如果第一序列的元素较小，返回 true ，否则返回 false
    // (2)如果到达 last1 而尚未到达 last2 返回 true
    // (3)如果到达 last2 而尚未到达 last1 返回 false
    // (4)如果同时到达 last1 和 last2 返回 false
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                  InputIter2 first2, InputIter2 last2) {
        // 任何一个序列到达尾端就结束，否则元素一一进行对比
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (*first1 < *first2) {
                return true;
            }
            if (*first2 < *first1) {
                return false;
            }
        }
        // 第一序列到达尾端，而第二序列尚有余额
        return first1 == last1 && first2 != last2;
    }

    template <typename InputIter1, typename InputIter2, typename Compared>
    bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                  InputIter2 first2, InputIter2 last2,
                                  Compared comp) {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (comp(first1, first2)) {
                return true;
            }

            if (comp(first2, first1)) {
                return false;
            }
        }

        return first1 == last1 && first2 != last2;
    }

    // 针对 const unsigned char *
    bool lexicographical_compare(const unsigned char* first1,
                                 const unsigned char* last1,
                                 const unsigned char* first2,
                                 const unsigned char* last2) {
        const auto len1 = last1 - first1;
        const auto len2 = last2 - first2;
        // 先比较相同长度的部分
        const auto result = std::memcmp(first1, first2, mystl::min(len1, len2));
        // 若相等，长度较长的比较大
        return result != 0 ? result < 0 : len1 < len2;
    }

    /*****************************************************************************************/
    // mismatch
    // 平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
    // 序列二多出来的部分不予考虑，但如果序列一超出序列二，会造成不可预估的问题
    /*****************************************************************************************/
    template <typename Inputiter1, typename Inputiter2>
    mystl::pair<Inputiter1, Inputiter2>
    mismatch(Inputiter1 first1, Inputiter1 last1, Inputiter2 first2) {
        // 序列一走完就结束
        // 如果len1 > len2, 结果无可预期
        while (first1 != last1 && *first1 == *first2) {
            ++first1;
            ++first2;
        }
        return mystl::pair<Inputiter1, Inputiter2>(first1, first2);
    }

    template <typename Inputiter1, typename Inputiter2, typename Compared>
    mystl::pair<Inputiter1, Inputiter2>
    mismatch(Inputiter1 first1, Inputiter1 last1, Inputiter2 first2, Compared comp) {
        while (first1 != last1 && comp(*first1, *first2)) {
            ++first1;
            ++first2;
        }
        return mystl::pair<Inputiter1, Inputiter2>(first1, first2);
    }

} // namespace mystl;

#endif //TINYSTL_ALGOBASE_H
