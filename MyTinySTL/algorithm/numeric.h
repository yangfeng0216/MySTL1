#ifndef TINYSTL_NUMERIC_H
#define TINYSTL_NUMERIC_H

// 数值算法

#include "iterator.h"
namespace mystl {

    /*****************************************************************************************/
    // accumulate
    // 版本1：以初值 init 对每个元素进行累加
    // 版本2：以初值 init 对每个元素进行二元操作
    /*****************************************************************************************/
    template <typename InputIter, typename T>
    T accumulate(InputIter first, InputIter last, T init) {
        for (; first != last; ++first) {
            init = init + *first;  // 不用 +=，避免类型T没有重载 += 操作符
        }

        return init;
    }

    template <typename InputIter, typename T, typename BinaryOp>
    T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op) {
        for (; first != last; ++first) {
            init = binary_op(init, *first);
        }

        return init;
    }

    /*****************************************************************************************/
    // adjacent_difference
    // 版本1：计算相邻元素的差值，结果保存到以 result 为起始的区间上
    // 版本2：自定义相邻元素的二元操作
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter>
    OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result) {
        if (first == last) return result;
        *result = *first;
        auto value = *first;
        while (++first != last) {
            auto tmp = *first;
            *++result = tmp - value;
            value = tmp;
        }
        return ++result;
    }

    template <typename InputIter, typename OutputIter, typename BinaryOp>
    OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result,
                                   BinaryOp binary_op) {
        if (first == last) return result;
        *result = *first;
        auto value = *first;
        while (++first != last) {
            auto tmp = *first;
            *++result = binary_op(tmp, value);
            value = tmp;
        }
        return ++result;
    }

    /*****************************************************************************************/
    // inner_product
    // 版本1：以 init 为初值，计算两个区间的内积
    // 版本2：自定义 operator+ 和 operator*
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename T>
    T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init) {
        for (; first1 != last1; ++first1, ++first2) {
            init = init + (*first1 * *first2);
        }
        return init;
    }

    template <typename InputIter1, typename InputIter2, typename T,
            typename BinaryOp1, typename BinaryOp2>
    T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init,
                    BinaryOp1 binary_op1, BinaryOp2 binary_op2) {
        for (; first1 != last1; ++first1, ++first2) {
            init = binary_op1(init, binary_op2(*first1, *first2));
        }
        return init;
    }

    /*****************************************************************************************/
    // iota
    // 填充[first, last)，以 value 为初值开始递增
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    void itoa(ForwardIter first, ForwardIter last, T value) {
        while (first != last) {
            *first++ = value++;
        }
    }

    /*****************************************************************************************/
    // partial_sum
    // 版本1：计算局部累计求和，结果保存到以 result 为起始的区间上
    // 版本2：进行局部进行自定义二元操作
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter>
    OutputIter partial_sum(InputIter first, InputIter last, OutputIter result) {
        if (first == last) return result;
        *result = *first;  // 记录第一个元素
        auto value = *first;
        while (++first != last) {
            value = value + *first;
            *++result = value;
        }
        return ++result;
    }

    template <typename InputIter, typename OutputIter, typename BinaryOp>
    OutputIter partial_sum(InputIter first, InputIter last, OutputIter result,
                           BinaryOp binary_op) {
        if (first == last) return result;
        *result = *first;
        auto value = *first;
        while (++first != last) {
            value = binary_op(value, *first);
            *++result = value;
        }

        return ++result;
    }

    /*****************************************************************************************/
    // pow
    // 版本1：幂次运算，指定运算型式为乘法
    // 版本2：幂次运算，进行自定义二元操作
    /*****************************************************************************************/
    // 版本一：乘幂
    template <typename T, typename Interger>
    inline T pow(T x, Interger n) {
        return pow(x, n, mystl::multiplies<T>());  // 调用第二版本，指定运算为乘法
    }

    // 版本二：指定二元操作
    template <typename T, typename Interger, typename BinaryOp>
    T pow(T x, Interger n, BinaryOp op) {
        if (n == 0) {
            return mystl::identity_element(op);  // 取出证同元素
        }
        while ((n & 1) == 0) {  // 判断n是否为偶数, 是偶数, n&1返回0; 否则返回1, 为奇数。
            n >>= 1;  // 右移运算并赋值符
            x = op(x, x);
        }
        T result = x;
        n >>= 1;  // 如果n是偶数此时n == 1, 右移后为0，反之进入下个while循环
        while (n != 0) {
            x = op(x, x);
            if ((n & 1) != 0) {  // n为奇数，单独乘以一个x，即result
                result = op(result, x);
            }
            n >>= 1;
        }
        return result;
    }
}  // namespace mystl;
#endif //TINYSTL_NUMERIC_H
