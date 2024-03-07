#ifndef TINYSTL_UTIL_H
#define TINYSTL_UTIL_H

// 通用工具头文件：move, forward, swap, pair...
#include <cstddef>
#include <type_traits>

namespace mystl {
    // move: 不管传入的是左值还是右值，最终转换为右值
    /*  输入参数类型为通用引用类型，既可以接收左值，也可以接收右值
     *  通用应用的成立条件: 一种是auto，一种是 T &&, 实际上 auto == T
     */
    template <typename T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }

    // forward:
    /*
     * 完美转发：通过函数转发保证参数的左值/右值，const/non-const属性不变。
     * 引用折叠：X& &，X& && 和 X&& & 折叠成X&， X&& &&折叠成X&&
     */
    template <class T>
    T&& forward(typename std::remove_reference<T>::type &arg) noexcept {
        return static_cast<T &&>(arg);
    }

    template <class T>
    T&& forward(typename std::remove_reference<T>::type &&arg) noexcept {
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T &&>(arg);
    }

    // swap: 借助 move 移动语义，对复杂的数据无需进行大量的复制操作
    template <class Tp>
    void swap(Tp &lhs, Tp &rhs) {
        auto tmp(mystl::move(lhs));
        lhs = mystl::move(rhs);
        rhs = mystl::move(tmp);
    }

    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
        for (; first1 != last1; ++first1, (void) ++first2) {
            mystl::swap(*first1, *first2);
        }
        return first2;
    }

    template <typename Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) {
        mystl::swap_range(a, a + N, b);
    }

    // pair
    /* 结构题模板: pair
     * 两个模板参数分别表示两个数据的类型
     * 用first 和 second 来分别取出第一个数据和第二个数据
     */
    template <typename Ty1, typename Ty2>
    struct pair {
        typedef Ty1 first_type;
        typedef Ty2 second_type;

        first_type first;  // 保存第一个数据
        second_type second;  // 保存第二个数据

        // default constructiable
        template<typename Other1 = Ty1, typename Other2 = Ty2,
                typename = typename std::enable_if<
                    std::is_default_constructible<Other1>::value &&
                    std::is_default_constructible<Other2>::value, void>::type>
        constexpr pair()
        : first(), second() {}

        // implicit constructiable for this type
         template<typename U1 = Ty1, typename U2 = Ty2,
                typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    std::is_convertible<const U1&, Ty1>::value &&
                    std::is_convertible<const U2&, Ty2>::vakue, int>::type = 0>
        constexpr pair(const Ty1 &a, const Ty2 &b)
        : first(a), second(b) {}

        // explicit constructiable for this type
        template<typename U1 = Ty1, typename U2 = Ty2,
                typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    (!std::is_convertible<const U1&, Ty1>::value ||
                    !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
        constexpr pair(const Ty1 &a, const Ty2 &b)
        : first(a), second(b) {}

        pair(const pair &rhs) = default;
        pair(pair &&rhs) noexcept = default;

        // implicit constructiable for other type
        template <typename Other1, typename Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    std::is_convertible<Other1 &&, Ty1>::value &&
                    std::is_convertible<Other2 &&, Ty2>::value, int>::type = 0>
        constexpr pair(Other1 &&a, Other2 &&b)
        :first(mystl::forward<Other1>(a)), second(mystl::forward<Other2>(b)) {}

        // explicit constructible for other type
        template<typename Other1, class Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    (!std::is_convertible<Other1, Ty1>::valuse ||
                    !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(Other1 &&a, Other2 &&b)
        : first(mystl::forward<Other1>(a)), second(mystl::forward<Other2>(b)) {}

        // implicit constructiable for other pair
        template <typename Other1, typename Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    std::is_convertible<const Other1 &, Ty1>::value &&
                    std::is_convertible<const Other2 &, Ty2>::value, int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2> &other)
        : first(other.first), second(other.second) {}

        // explicit constructiable for other pair
        template <class Other1, class Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    (!std::is_convertible<const Other1&, Ty1>::value ||
                    !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2>& other)
        : first(other.first), second(other.second) {}

        // implicit constructiable for other pair
        template <typename Other1, typename Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    std::is_convertible<const Other1 &, Ty1>::value &&
                    std::is_convertible<const Other2 &, Ty2>::value, int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2> &&other)
        : first(mystl::forward<Other1>(other.first)), second(mystl::forward<Other2>()) {}

        // explicit constructiable for other pair
        template <typename Other1, typename Other2,
                typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    (!std::is_convertible<const Other1&, Ty1>::value ||
                    !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2> &&other)
        : first(mystl::forward<Other1>(other.first)), second(mystl::forward<Other2>()) {}

        // copy assign for this pair
        pair &operator= (const pair &rhs) noexcept {
            if (this != &rhs) {
                first = rhs.first;
                second = rhs.second;
            }

            return *this;
        }

        // move assign for this pair
        template<typename Other1, typename Other2>
        pair &operator= (pair &&rhs) noexcept {
            if (this != &rhs) {
                first = mystl::move(rhs.first);
                second = mystl::move(rhs.second);
            }

            return *this;
        }

        // copy assign for other pair
        template<typename Other1, typename Other2>
        pair &operator= (const pair<Other1, Other2> &other) {
            first = other.first;
            second = other.second;

            return *this;
        }

        // move assign for other pair
        template <class Other1, class Other2>
        pair &operator= (pair<Other1, Other2> &&other) {
            first = mystl::forward<Other1>(other.first);
            second = mystl::forward<Other2>(other.second);

            return *this;
        }

        ~pair() = default;

        void swap(pair &other) {
            if (this != &other) {
                mystl::swap(first, other.first);
                mystl::swap(second, other.second);
            }
        }

    };  // class pair

    // 重载比较操作符
    template <typename Ty1, typename Ty2>
    bool operator== (const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <typename Ty1, typename Ty2>
    bool operator< (const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs) {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template <typename Ty1, typename Ty2>
    bool operator!= (const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs) {
        return !(lhs == rhs);
    }

    template <typename Ty1, typename Ty2>
    bool operator> (const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return rhs < lhs;
    }

    template <typename Ty1, typename Ty2>
    bool operator<= (const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs) {
        return !(rhs < lhs);
    }

    template <class Ty1, class Ty2>
    bool operator>=(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs) {
        return !(lhs < rhs);
    }

    // 重载swap
    template <typename Ty1, typename Ty2>
    void swap(pair<Ty1, Ty2>  &lhs, pair<Ty1, Ty2> &rhs) {
        lhs.swap(rhs);
    }

    // 全局函数， 让两个数据成为一个pair
    template <typename Ty1, typename Ty2>
    pair<Ty1, Ty2> make_pair(Ty1 &&first, Ty2 &&second) {
        return pair<Ty1, Ty2>(mystl::forward<Ty1>(first), mystl::forward<Ty2>(second));
    }

}  // namespace mystl

#endif //TINYSTL_UTIL_H
