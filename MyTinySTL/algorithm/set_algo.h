#ifndef TINYSTL_SET_ALGO_H
#define TINYSTL_SET_ALGO_H
// 与set有关的四种算法：union、intersection、deifference、symmetric_difference
// 所有序列要求有序
#include "algobase.h"
#include "iterator.h"
namespace mystl {
    /*****************************************************************************************/
    // set_union
    // 计算 S1∪S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_union(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result) {
        // 在两个区间都未到达底端时，执行以下操作：
        while (first1 != last1 && first2 != last2) {
            // 在两区间内分别移动迭代器，首先将元素值较小值，假设为A区，记录于目标区
            // 然后移动A区接待器使之前进；同时另一个迭代器不动，然后进行新的比较
            // 如果元素相等，取一个记录于目标区，并同时移动两个迭代器
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
            }else if (*first2 < *first1) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        // 只要两区之中有一区到达尾端，就结束上述的 while 循环
        // 以下将尚未到达尾端的区间的所有剩余元素拷贝到目的端
        // 此刻的 [firstl,last1)和[first2,last2)之中有一个是空白区间
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_union(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result, Compared comp) {
        // 前提应该是已经排序
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
            }else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }

        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    /*****************************************************************************************/
    // set_intersection
    // 计算 S1∩S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result) {
        // 在两个区间都未到达底端时，执行以下操作：
        while (first1 != last1 && first2 != last2) {
            // 在两区间内分别移动迭代器，直到遇有元素相同，暂停，将该值记录于目标区
            // 再继续移动迭代器，直至两区之中有一个到达尾端
            if (*first1 < *first2) {
                ++first1;
            }else if (*first2 < *first1) {
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }

        return result;
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2,
                                OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                ++first1;
            }else if (comp(*first2, *first1)) {
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }

        return result;
    }

    /*****************************************************************************************/
    // set_difference
    // 计算 S1-S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2,
                                OutputIter result) {
        // 在两个区间都未到达底端时，执行以下操作：
        while (first1 != last1 && first2 != last2) {
            // 在两区间内分别移动送代器。当第一区间的元素等于第二区间的元素(表示此值
            // 同时存在于两区间)，就让两区间同时前进，当第一区间的元素大于第二区间的元素
            // 就让第二区间前进:有了这两种处理，就保证当第一区间的元素小于第二区间的
            // 元素时，第一区间的元素只存在于第一区间中，不存在于第二区间，于是将它// 记录于目标区
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (*first2 < *first1) {
                ++first2;
            }else {
                ++first1;
                ++first2;
            }
        }
        // 如果区间一还有剩余，复制
        return mystl::copy(first1, last1, result);
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (comp(*first2, *first1)) {
                ++first2;
            }else {
                ++first1;
                ++first2;
            }
        }

        return mystl::copy(first1, last1, result);
    }
    /*****************************************************************************************/
    // set_symmetric_difference
    // 计算 (S1-S2)∪(S2-S1) 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    // 对称差集：
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (*first2 < *first1) {
                *result = *first2;
                ++first2;
                ++result;
            }else {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
                ++result;
            }else {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }
}  // namespace mystl;
#endif //TINYSTL_SET_ALGO_H
